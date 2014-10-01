// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_MAKE_MATCHER_HPP_
#define FMOCK_DETAIL_MAKE_MATCHER_HPP_

#include "fmock/detail/matcher.hpp"
#include "fmock/detail/types/is_matcher.hpp"
#include "fmock/detail/matchers/equals.hpp"

#include <type_traits>

namespace fmock {
namespace detail {

template <class arg_t>
using ensure_matcher = std::enable_if<types::is_matcher<arg_t>::value, arg_t>;

template <class arg_t>
arg_t make_matcher(typename ensure_matcher<arg_t>::type const& matcher) {
  return matcher;
}

template <class arg_t>
matcher<arg_t> make_matcher(arg_t value) {
  return matchers::equals<typename std::remove_reference<arg_t>::type>(value);
}

} // namespace detail
} // namespace fmock

#endif // include guard

