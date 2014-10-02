// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_MAKE_MATCHER_HPP_
#define FMOCK_DETAIL_MAKE_MATCHER_HPP_

#include "fmock/detail/matcher.hpp"
#include "fmock/detail/types/is_matcher.hpp"
#include "fmock/detail/types/arg_of.hpp"
#include "fmock/detail/matchers/equals.hpp"

#include <type_traits>

namespace fmock {
namespace detail {

template <class matcher_t, typename std::enable_if<
  types::is_matcher<matcher_t>::value>::type * = nullptr>
matcher<typename types::arg_of<matcher_t>::type> make_matcher(matcher_t m) {
  return m;
}

template <class arg_t, typename std::enable_if<
  !types::is_matcher<arg_t>::value>::type * = nullptr>
matcher<arg_t> make_matcher(arg_t value) {
  return matchers::equals<typename std::remove_reference<arg_t>::type>(value);
}

} // namespace detail
} // namespace fmock

#endif // include guard

