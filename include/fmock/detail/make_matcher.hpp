// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_MAKE_MATCHER_HPP_
#define FMOCK_DETAIL_MAKE_MATCHER_HPP_

#include "fmock/matcher.hpp"
#include "fmock/types/is_matcher.hpp"
#include "fmock/types/is_matcher_function.hpp"
#include "fmock/types/arg_of.hpp"
#include "fmock/matchers/equals.hpp"
#include "fmock/matchers/anonymous.hpp"

#include <type_traits>

namespace fmock {
namespace detail {

template <
    class matcher_t,
    typename std::enable_if<types::is_matcher<matcher_t>::value>::type* = nullptr
    >
matcher_t * make_matcher(matcher_t const& matcher) {
  return new matcher_t(matcher);
}

template <
    class func_t,
    typename std::enable_if<types::is_matcher_function<func_t>::value>::type* = nullptr,
    typename std::enable_if<!types::is_matcher<func_t>::value>::type* = nullptr
    >
matchers::anonymous<typename types::arg_of<func_t>::type> *
make_matcher(func_t const& function) {
  return new matchers::anonymous<typename types::arg_of<func_t>::type>(function);
}

template <
    class arg_t,
    typename std::enable_if<!types::is_matcher_function<arg_t>::value>::type* = nullptr,
    typename std::enable_if<!types::is_matcher<arg_t>::value>::type* = nullptr
    >
matchers::equals<arg_t> * make_matcher(arg_t const& value) {
  return new matchers::equals<arg_t>(value);
}

} // namespace detail
} // namespace fmock

#endif // include guard

