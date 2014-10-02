// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_MATCHERS_ANY_HPP_
#define FMOCK_MATCHERS_ANY_HPP_

#include "fmock/matcher.hpp"
#include "fmock/types/is_matcher.hpp"

namespace fmock {
namespace matchers {

template <class arg_type>
struct any {
  match_result operator() (arg_type const&) const noexcept(true) {
    return match_result::SUCCESS;
  }
}; // struct any

namespace {
  types::assert_is_matcher<any<int>> any_is_matcher;
}

} // namespace matchers
} // namespace fmock

#endif // include guard

