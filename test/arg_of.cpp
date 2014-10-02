// licence: GPLv3
// author: Maciej Chałapuk

#include "fmock/types/arg_of.hpp"
#include "fmock/matchers/any.hpp"
#include "fmock/matchers/equals.hpp"

using namespace fmock::types;
using namespace fmock::matchers;

namespace {

template <class expected_type, class actual_type> \
struct AssertEquals { \
  static_assert(std::is_same<expected_type, actual_type>::value,
      "matcher argument type error");
};

AssertEquals<int, typename arg_of<any<int>>::type> test0;
AssertEquals<char, typename arg_of<any<char>>::type> test1;
AssertEquals<long, typename arg_of<equals<long>>::type> test2;
AssertEquals<short, typename arg_of<equals<short>>::type> test3;

} // namespace

