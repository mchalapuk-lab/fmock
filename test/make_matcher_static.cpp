// licence: GPLv3
// author: Maciej Chałapuk

#include "fmock/detail/make_matcher.hpp"
#include "fmock/matchers/anonymous.hpp"
#include "fmock/matchers/any.hpp"
#include "fmock/matchers/equals.hpp"

using namespace fmock;
using namespace fmock::detail;
using namespace fmock::matchers;

namespace {

template <class expected_type, class actual_type>
struct AssertEquals {
  static_assert(std::is_same<expected_type, actual_type>::value,
      "matcher argument type error");
};

AssertEquals<any<int> *, decltype(make_matcher(std::declval<any<int>>()))> test0;
AssertEquals<any<char> *, decltype(make_matcher(std::declval<any<char>>()))> test1;
AssertEquals<equals<int> *, decltype(make_matcher(std::declval<equals<int>>()))> test2;
AssertEquals<equals<char> *, decltype(make_matcher(std::declval<equals<char>>()))> test3;

AssertEquals<equals<int> *, decltype(make_matcher(std::declval<int>()))> test4;
AssertEquals<equals<char> *, decltype(make_matcher(std::declval<char>()))> test5;

match_result function(int const&);
AssertEquals<anonymous<int> *, decltype(make_matcher(&function))> test6;

struct functor {
  match_result operator() (char const&) const;
};
AssertEquals<anonymous<char> *, decltype(make_matcher(std::declval<functor>()))> test7;

} // namespace

