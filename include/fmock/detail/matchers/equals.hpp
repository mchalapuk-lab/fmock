// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_MATCHERS_EQUALS_HPP_
#define FMOCK_DETAIL_MATCHERS_EQUALS_HPP_

#include "fmock/detail/matcher.hpp"

#include <type_traits>

namespace fmock {
namespace detail {
namespace matchers {

template <class arg_t>
class equals {
 public:
  equals(arg_t const& val) : value(val) {}

  match_result operator() (arg_t const& arg) const
  noexcept(noexcept(arg == arg)) {
    return (value == arg)? match_result::SUCCESS: match_result::FAILURE;
  }
 private:
  arg_t const& value;
}; // class equals

} // namespace matchers
} // namespace detail
} // namespace fmock

#endif // include guard

