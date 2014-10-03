// licence: GPLv3
// author: Maciej Chałapuk

#include "fmock/types/is_matcher.hpp"
#include "fmock/matchers/any.hpp"
#include "fmock/matchers/equals.hpp"

using namespace fmock;
using namespace fmock::types;
using namespace fmock::matchers;

namespace {

#define TEST_IS_MATCHER(type) \
static_assert(is_matcher< type >::value, \
    "type " #type " should be detected as a matcher")

#define TEST_IS_NOT_MATCHER(type) \
static_assert(!is_matcher< type >::value, \
    "type " #type " shouldn't be detected as a matcher")

TEST_IS_MATCHER(any<int>);
TEST_IS_MATCHER(any<char>);
TEST_IS_MATCHER(equals<long>);
TEST_IS_MATCHER(equals<char const*>);
TEST_IS_NOT_MATCHER(void);
TEST_IS_NOT_MATCHER(int);
TEST_IS_NOT_MATCHER(char[]);

match_result function(int const&);
TEST_IS_NOT_MATCHER(decltype(&function));

struct functor {
  match_result operator() (char const&) const;
};
TEST_IS_NOT_MATCHER(functor);

} // namespace

