// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_MATCHERS_ANY_HPP_
#define FMOCK_DETAIL_MATCHERS_ANY_HPP_

#include "fmock/detail/matcher.hpp"

namespace fmock {
namespace detail {
namespace matchers {

template <class arg_type>
struct any {
  match_result operator() (arg_type const& arg) const noexcept(true) {
    return match_result::SUCCESS;
  }
}; // struct any

} // namespace matchers
} // namespace detail
} // namespace fmock

#endif // include guard


