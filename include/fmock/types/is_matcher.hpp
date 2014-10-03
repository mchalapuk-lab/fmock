// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_TYPES_IS_MATCHER_HPP_
#define FMOCK_TYPES_IS_MATCHER_HPP_

#include "fmock/matcher.hpp"

namespace fmock {
namespace types {

template <class maybe_matcher_t>
struct is_matcher {
 private:
  typedef char yes[1];
  typedef char no[2];

  template <class arg_t> static yes& test(matcher<arg_t> const*);
  static no& test(void const*);
 public:
  static bool const value =
    sizeof(test(static_cast<maybe_matcher_t const*>(nullptr))) == sizeof(yes);
}; // struct is_matcher

template <class matcher_t>
struct assert_is_matcher {
  static_assert(is_matcher<matcher_t>::value, "matcher_t is not a matcher");
}; // struct assert_is_matcher

} // namespace types
} // namespace fmock

#endif // include guard

