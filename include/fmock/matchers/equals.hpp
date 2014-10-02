// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_MATCHERS_EQUALS_HPP_
#define FMOCK_MATCHERS_EQUALS_HPP_

#include "fmock/matcher.hpp"
#include "fmock/types/is_matcher.hpp"

#include <type_traits>

namespace fmock {
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

namespace {
  types::assert_is_matcher<equals<int>> equals_matcher_test;
}

} // namespace matchers
} // namespace fmock

#endif // include guard

