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
      visit(error);
    }
    visit(*this);
  }
 private:
  std::forward_list<expect_error> next_errors;

  friend class mock;
}; // class expect_error

template <class constructed_type>
struct constructor {
  constructed_type operator() () const {
    return constructed_type();
  }
}; // struct constructor

template <class arg_type>
using matcher = std::function<bool (arg_type)>;

template <class arg_type>
struct any {
  bool operator() (arg_type arg) const {
    return true;
  }
}; // struct any

template <class return_type, class ...arg_types>
struct expectation {
  std::tuple<matcher<arg_types>...> matchers;
  std::function<return_type(arg_types...)> answer;
}; // struct expectation

template <class ...arg_types>
struct typeinfo_list_creator {
}; // struct typeinfo_list_creator

template <>
struct typeinfo_list_creator<> {
  std::list<std::type_info const*>
  operator() (std::list<std::type_info const*> list) const {
    return list;
  }
};

template <class head_type, class ...tail_types>
struct typeinfo_list_creator<head_type, tail_types...> {
  std::list<std::type_info const*>
  operator() (std::list<std::type_info const*> list) const {
    list.push_back(&typeid(head_type));
    return typeinfo_list_creator<tail_types...>()(list);
  }
};

template <class ...types>
std::list<std::type_info const*> make_typeinfo_list() {
  return typeinfo_list_creator<types...>()(std::list<std::type_info const*>());
}

class mock {
 public:
  typedef std::list<std::type_info const*> typeinfo_list;
  typedef std::tuple<typeinfo_list, std::shared_ptr<void>> exp_tuple;

  mock() {}
  mock(mock const&) = delete;
  mock(mock &&) = delete;

  ~mock() {
    if (!has_unsatisfied_expectations()) {
      return;
    }
    auto current_error = make_unsatisfied_error();
    if (!std::uncaught_exception()) {
      throw current_error;
    }
    // error not thrown, can't do much about it (TODO stderr??)
  }
 
  template <class return_type, class ...arg_types>
  return_type call(arg_types ...args) {
    auto current_arg_types = make_typeinfo_list<return_type, arg_types...>();
    if (!has_unsatisfied_expectations()) {
      throw make_unexpected_call_error(current_arg_types);
    }

    auto front = expectations.front();
    expectations.pop_front();
    typeinfo_list expected_arg_types;
    std::shared_ptr<void> exp_ptr;
    std::tie(expected_arg_types, exp_ptr) = front;

    if (expected_arg_types != current_arg_types) {
      throw make_unexpected_call_error(current_arg_types, expected_arg_types);
    }

    typedef expectation<return_type, arg_types...> expectations_type;
    auto *typed_exp = static_cast<expectations_type *>(exp_ptr.get());
    check_arguments(expected_arg_types,
                    *typed_exp,
                    std::forward<arg_types>(args)...,
                    0);
    return typed_exp->answer(std::forward<arg_types>(args)...);
  }

  void add_expectation(exp_tuple const& exp) {
    expectations.push_back(exp);
  }

  bool has_unsatisfied_expectations() const {
    return (expectations.size() != 0);
  }
 private:
  std::deque<exp_tuple> expectations;

  template <class return_type, class ...arg_types>
  void check_arguments(typeinfo_list expected_arg_types,
                       expectation<return_type, arg_types...> const& exp,
                       arg_types... args,
                       size_t arg_index) {

    constexpr auto arg_count = std::tuple_size<decltype(exp.matchers)>::value;
    if (arg_index == arg_count) {
      return;
    }

    auto &arg = std::get<arg_index>(std::forward_as_tuple(args...));
    auto &matcher = std::get<arg_index>(exp.matchers);
    if (!matcher(std::forward<decltype(arg)>(arg))) {
      throw make_argument_mismatch_error(expected_arg_types, arg_index);
    }

    check_arguments(expected_arg_types,
                    exp,
                    std::forward<arg_types>(args)...,
                    arg_index + 1);
  }

  expect_error make_unsatisfied_error() {
    return expect_error("unsatisfied expectations");
  }
  static expect_error
  make_unexpected_call_error(typeinfo_list current_arg_types) {
    return expect_error("unexpected call");
  }
  static expect_error
  make_unexpected_call_error(typeinfo_list current_arg_types,
                             typeinfo_list expected_arg_types) {
    return expect_error("unexpected call to different signature");
  }
  static expect_error
  make_argument_mismatch_error(typeinfo_list expected_arg_types,
                               size_t arg_index) {
    return expect_error("argument not matching expectations");
  }
}; // class mock

template <class return_type, class ...arg_types>
class answer_builder {
 public:
  answer_builder(std::shared_ptr<detail::mock> mock)
    : impl(mock),
    matchers(detail::any<arg_types>()...),
    answer([] (arg_types...) { return detail::constructor<return_type>(); }) {
  }
  ~answer_builder() {
    typedef detail::expectation<return_type, arg_types...> expectation_type;
    std::shared_ptr<void> exp(new expectation_type { matchers, answer});
    auto typeinfo = detail::make_typeinfo_list<return_type, arg_types...>();
    impl->add_expectation(std::make_tuple(typeinfo, exp));
  }
 private:
  std::shared_ptr<detail::mock> impl;
  std::tuple<detail::matcher<arg_types>...> matchers;
  std::function<return_type(arg_types...)> answer;
}; // class answer_builder

}; // namespace detail

class function {
 public:
  template <class return_type, class ...arg_types>
  detail::answer_builder<return_type, arg_types...>
  expect_call(detail::matcher<arg_types> const& ...matchers) {
    return detail::answer_builder<return_type, arg_types...>(impl);
  }
  template <class return_type, class ...arg_types>
  return_type operator() (arg_types ...args) {
    return impl->call<return_type>(std::forward<arg_types>(args)...);
  }
 private:
  std::shared_ptr<detail::mock> impl;
}; // class function

} // namespace fmock

#endif // include guard

