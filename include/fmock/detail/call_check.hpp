// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_CALL_CHECK_HPP_
#define FMOCK_DETAIL_CALL_CHECK_HPP_

#include <tuple>

namespace fmock {
namespace detail {

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

} // namespace detail
} // namespace fmock

#endif // include guard

