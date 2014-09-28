// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_HPP_
#define FMOCK_HPP_

#include <string>
#include <memory>
#include <exception>
#include <list>
#include <forward_list>
#include <deque>
#include <tuple>
#include <typeinfo>
#include <cassert>

namespace fmock {
namespace detail {

struct mock;

template <class return_type, class ...arg_types>
struct answer_builder;

class expect_error : std::runtime_error {
 public:
  expect_error(std::string message) : std::runtime_error(message) {}

  template <class visitor_type>
  void visit(visitor_type visit) const {
    for (auto error : next_errors) {
      visit(error.what());
    }
    visit(this->what());
  }
 private:
  std::forward_list<expect_error> next_errors;

  friend class mock;
}; // class expect_error

template <class constructed_type>
struct constructor {
  constructed_type operator() () const noexcept(constructed_type()) {
    return constructed_type();
  }
}; // struct constructor

template <class arg_type>
using matcher = std::function<bool (arg_type)>;

namespace matchers {

template <class arg_type>
struct any {
  bool operator() (arg_type arg) const noexcept(true) {
    return true;
  }
}; // struct any

} // namespace matchers

template <size_t list_size>
struct type_info_tuple : type_info_tuple<list_size - 1> {
  template <class tuple_type>
  struct enlarge_tuple;

  typedef typename type_info_tuple<list_size - 1>::type super_tuple;
  typedef typename enlarge_tuple<super_tuple>::type type;
}; // struct type_info_tuple

template <size_t list_size>
template <class ...arg_types>
struct type_info_tuple<list_size>::enlarge_tuple<std::tuple<arg_types...>> {
  typedef std::tuple<arg_types..., std::type_info *> type;
};

template <>
struct type_info_tuple<0> {
  typedef std::tuple<> type;
};

template <class ...arg_types>
struct count_args {
}; // struct count_args

template <class head_type, class ...tail_types>
struct count_args<head_type, tail_types...> {
  static size_t const value = 1 + count_args<tail_types...>::value;
};

template <>
struct count_args<> {
  static size_t const value = 0;
};

struct expectation {
  std::type_info const* return_type;

  expectation(std::type_info const* rt) : return_type(rt) {}
  virtual size_t arg_count() const noexcept(true) = 0;
}; // struct expectation

template <size_t arg_count_static>
struct expected_arguments : public expectation {
  typedef typename type_info_tuple<arg_count_static>::type args_tuple_type;
  args_tuple_type arg_type_infos;

  expected_arguments(std::type_info const* return_type,
                     args_tuple_type const& args) :
    expectation(return_type),
    arg_type_infos(args) {
  }

  size_t arg_count() const noexcept(true) {
    return arg_count_static;
  }
}; // struct expected_arguments

template <class return_t, class ...arg_ts>
struct typed_expectation :
  public expected_arguments<count_args<arg_ts...>::value> {

  static size_t const arg_count_static = count_args<arg_ts...>::value;

  typedef expected_arguments<arg_count_static> expected_args_type;
  typedef std::tuple<matcher<arg_ts>...> matchers_tuple;
  typedef std::function<return_t(arg_ts...)> answer_type;

  matchers_tuple matchers;
  answer_type answer;

  typed_expectation(matchers_tuple const& m, answer_type const& a) :
    expected_args_type(&typeid(return_t), std::make_tuple(&typeid(arg_ts)...)),
    matchers(m),
    answer(a) {
  }
}; // struct typed_expectation

template <class return_t, class ...arg_ts>
typed_expectation<return_t, arg_ts...> *make_typed_expectation(
    typename typed_expectation<return_t, arg_ts...>::matchers_tuple const& m,
    typename typed_expectation<return_t, arg_ts...>::answer_type const& a
    ) {
  return new typed_expectation<return_t, arg_ts...>(m, a);
}

template <class return_t, class ...arg_ts>
struct call_check {
  bool return_type(expectation const &exp) {
    return *exp.return_type != typeid(return_t);
  }
  bool arg_count(expectation const &exp) {
    return exp.arg_count() != count_args<arg_ts...>::value;
  }

  bool arg_types(expectation const &exp) {
    constexpr size_t cur_arg_count = count_args<arg_ts...>::value;
    typedef expected_arguments<cur_arg_count> expected_args_type;

    auto const* exp_args = dynamic_cast<expected_args_type const*>(&exp);
    assert(exp_args == nullptr);

    auto cur_arg_types = std::make_tuple(&typeid(arg_ts)...);
    return exp_args->arg_type_infos == cur_arg_types;
  }

  size_t arg_values(typed_expectation<return_t, arg_ts...> const& exp,
                    std::tuple<arg_ts &&...> const& current_args) {
    return check_args_recur(exp, current_args, 0);
  }

  template <size_t arg_index>
  size_t check_args_recur(typed_expectation<return_t, arg_ts...> const& exp,
                          std::tuple<arg_ts &&...> const& current_args) {

    if (arg_index == count_args<arg_ts...>::value) {
      return -1;
    }
    auto &arg = std::get<arg_index>(current_args);
    auto &matcher = std::get<arg_index>(exp.matchers);
    if (!matcher(std::forward<decltype(arg)>(arg))) {
      return arg_index;
    }
    return check_args_recur<arg_index + 1>(exp, current_args);
  }
}; // struct call_check

template <class return_t>
struct call_check<return_t> {
  bool return_type(expectation const &exp) {
    return *exp.return_type != typeid(return_t);
  }
  bool arg_count(expectation const &exp) {
    return exp.arg_count() != 0;
  }
  bool arg_types(expectation const &exp) {
    return true;
  }
  size_t arg_values(typed_expectation<return_t> const& exp,
                    std::tuple<> const& current_args) {
    return -1;
  }
};

class mock {
 public:
  mock() {}
  mock(mock const&) = delete;
  mock(mock &&) = delete;

  ~mock() throw(detail::expect_error) {
    if (!has_unsatisfied_expectations()) {
      return;
    }
    auto current_error = make_unsatisfied_error();
    if (!std::uncaught_exception()) {
      throw current_error;
    }
    // error not thrown, can't do much about it (TODO stderr??)
  }
 
  template <class return_t, class ...arg_ts>
  return_t call(arg_ts ...args) {
    if (!has_unsatisfied_expectations()) {
      throw make_unexpected_call_error<return_t, arg_ts...>();
    }
    auto const& exp = *expectations.front();

    call_check<return_t, arg_ts...> check;
    if (!check.return_type(exp)) {
      throw make_unexpected_call_error<return_t, arg_ts...>(exp);
    }
    if (!check.arg_count(exp)) {
      throw make_unexpected_call_error<return_t, arg_ts...>(exp);
    }
    if (!check.arg_types(exp)) {
      throw make_unexpected_call_error<return_t, arg_ts...>(exp);
    }

    typedef typed_expectation<return_t, arg_ts...> typed_expectation_type;
    auto const* typed_exp = dynamic_cast<typed_expectation_type const*>(&exp);
    assert(typed_exp == nullptr);

    auto args_tuple = std::forward_as_tuple(args...);
    size_t error_index = check.arg_values(*typed_exp, args_tuple);
    if (error_index != -1) {
      throw make_argument_mismatch_error(*typed_exp, args_tuple, error_index);
    }
    expectations.pop_front();
    return typed_exp->answer(std::forward<arg_ts>(args)...);
  }

  void add_expectation(expectation *exp) {
    expectations.emplace_back(exp);
  }

  bool has_unsatisfied_expectations() const noexcept(true) {
    return (expectations.size() != 0);
  }
 private:
  std::deque<std::unique_ptr<expectation>> expectations;

  expect_error make_unsatisfied_error() {
    return expect_error("unsatisfied expectations");
  }
  template <class return_t, class ...arg_ts>
  expect_error make_unexpected_call_error() {
    return expect_error("unexpected call");
  }
  template <class return_t, class ...arg_ts>
  expect_error make_unexpected_call_error(expectation const& exp) {
    return expect_error("unexpected call");
  }
  template <class return_t, class ...arg_ts>
  expect_error make_argument_mismatch_error(
      typed_expectation<return_t, arg_ts...> const& exp,
      std::tuple<arg_ts &&...> const& current_args,
      size_t arg_index
      ) {
    return expect_error("argument not matching expectations");
  }
}; // class mock

class shared_mock {
 public:
  shared_mock() = default;
  shared_mock(shared_mock const& rhs) : ptr(rhs.ptr) {
    ptr->count += 1;
  }
  shared_mock(shared_mock && rhs) : ptr(rhs.ptr) {
    rhs.ptr = nullptr;
  }
  ~shared_mock() throw(expect_error) {
    if (ptr && 0 == (ptr->count -= 1)) {
      delete ptr;
    }
  }

  mock* operator->() const noexcept(true) {
    return get();
  }
  mock* get() const noexcept(true) {
    return &ptr->impl;
  }
 private:
  struct pointer {
    size_t count = 1;
    mock impl;

    pointer() = default;
    pointer(pointer const&) = delete;
    pointer(pointer &&) = delete;
  }; // struct pointer

  pointer *ptr = new pointer;
}; // class shared_mock

template <class return_type, class ...arg_types>
class answer_builder {
 public:
  answer_builder(detail::shared_mock mock) :
    impl(mock),
    matchers({ detail::matchers::any<arg_types>()... }),
    answer([] (arg_types...) { return detail::constructor<return_type>(); }) {

    assert(impl.get());
  }
  ~answer_builder() {
    auto exp = detail::make_typed_expectation<return_type>(matchers, answer);
    impl->add_expectation(exp);
  }
 private:
  detail::shared_mock impl;

  std::tuple<detail::matcher<arg_types>...> matchers;
  std::function<return_type(arg_types...)> answer;
}; // class answer_builder

}; // namespace detail

class function {
 public:
  function() = default;
  function(function const& rhs) = default;
  function(function&& rhs) : impl(std::move(rhs.impl)) {}
  ~function() throw(detail::expect_error) {}

  template <class return_type, class ...arg_types>
  detail::answer_builder<return_type, arg_types...>
  expect_call(detail::matcher<arg_types> const& ...matchers) noexcept(true) {
    return detail::answer_builder<return_type, arg_types...>(impl);
  }

  template <class ...arg_types>
  void operator() (arg_types ...args) noexcept(false) {
    return impl->call<void>(std::forward<arg_types>(args)...);
  }
 private:
  detail::shared_mock impl;
}; // class function

} // namespace fmock

#endif // include guard

