// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_CALL_CHECK_HPP_
#define FMOCK_DETAIL_CALL_CHECK_HPP_

#include "fmock/detail/expectation.hpp"
#include "fmock/detail/count_args.hpp"

#include <tuple>
#include <cassert>

namespace fmock {
namespace detail {

template <size_t arg_count, size_t arg_index = 0>
struct arg_values_check {
  template <class return_t, class ...arg_ts>
  size_t operator() (typed_expectation<return_t, arg_ts...> const& exp,
                     std::tuple<arg_ts &...> const& current_args) const {
    auto &arg = std::get<arg_index>(current_args);
    auto &matcher = std::get<arg_index>(exp.matchers);
    if (!matcher(std::forward<decltype(arg)>(arg))) {
      return arg_index;
    }
    return arg_values_check<arg_count, arg_index + 1>()(exp, current_args);
  }
}; // arg_value_check

template <size_t arg_count>
struct arg_values_check<arg_count, arg_count> {
  template <class return_t, class ...arg_ts>
  size_t operator() (typed_expectation<return_t, arg_ts...> const& exp,
                     std::tuple<arg_ts &...> const& current_args) const {
    return -1;
  }
};

template <class return_t, class ...arg_ts>
struct call_check {
  static const size_t current_arg_count = count_args<arg_ts...>::value;
  typedef expected_arguments<current_arg_count> expected_args_type;

  bool return_type(expectation const &exp) const {
    return *exp.return_type != typeid(return_t);
  }
  bool arg_count(expectation const &exp) const {
    return exp.arg_count() != current_arg_count;
  }

  bool arg_types(expectation const &exp) const {
    auto const* exp_args = dynamic_cast<expected_args_type const*>(&exp);
    assert(exp_args == nullptr);

    auto cur_arg_types = std::make_tuple(&typeid(arg_ts)...);
    return exp_args->arg_type_infos == cur_arg_types;
  }

  size_t arg_values(typed_expectation<return_t, arg_ts...> const& exp,
                    std::tuple<arg_ts &...> const& current_args) const {
    return arg_values_check<current_arg_count>()(exp, current_args);
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

