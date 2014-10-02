// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_MATCHERS_ANY_HPP_
#define FMOCK_DETAIL_MATCHERS_ANY_HPP_

#include "fmock/detail/matcher.hpp"
#include "fmock/detail/types/is_matcher.hpp"

namespace fmock {
namespace detail {
namespace matchers {

template <class arg_type>
struct any {
  match_result operator() (arg_type const&) const noexcept(true) {
    return match_result::SUCCESS;
  }
}; // struct any

namespace {
  auto test = types::assert_is_matcher<any<int>>();
}

} // namespace matchers
} // namespace detail
} // namespace fmock

#endif // include guard


