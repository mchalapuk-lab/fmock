// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_EXPECTATION_HPP_
#define FMOCK_DETAIL_EXPECTATION_HPP_

#include "fmock/detail/type_info_tuple.hpp"
#include "fmock/detail/count_args.hpp"
#include "fmock/detail/matcher.hpp"

namespace fmock {
namespace detail {

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

} // namespace detail
} // namespace fmock

#endif // include guard

