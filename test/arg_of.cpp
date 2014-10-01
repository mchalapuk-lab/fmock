// licence: GPLv3
// author: Maciej Chałapuk

#include "fmock/detail/types/arg_of.hpp"
#include "fmock/detail/matchers/any.hpp"
#include "fmock/detail/matchers/equals.hpp"

using namespace fmock::detail::types;
using namespace fmock::detail::matchers;

namespace {

template <class expected_type, class actual_type> \
struct AssertEquals { \
  static_assert(std::is_same<expected_type, actual_type>::value,
      "matcher argument type error");
};

AssertEquals<int const&, typename arg_of<any<int>>::type> test0;
AssertEquals<char const&, typename arg_of<any<char>>::type> test1;
AssertEquals<long const&, typename arg_of<equals<long>>::type> test2;
AssertEquals<short const&, typename arg_of<equals<short>>::type> test3;

} // namespace

