// licence: GPLv3
// author: Maciej Chałapuk

#include "fmock/detail/types/is_matcher.hpp"
#include "fmock/detail/matchers/any.hpp"
#include "fmock/detail/matchers/equals.hpp"

using namespace fmock::detail::types;
using namespace fmock::detail::matchers;

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

} // namespace

