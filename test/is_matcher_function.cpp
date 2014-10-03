// licence: GPLv3
// author: Maciej Chałapuk

#include "fmock/types/is_matcher_function.hpp"
#include "fmock/matchers/any.hpp"
#include "fmock/matchers/equals.hpp"

using namespace fmock;
using namespace fmock::types;
using namespace fmock::matchers;

namespace {

#define TEST_IS_MATCHER_FUNCTION(type) \
static_assert(is_matcher_function< type >::value, \
    "type " #type " should be detected as a matcher function")

#define TEST_IS_NOT_MATCHER_FUNCTION(type) \
static_assert(!is_matcher_function< type >::value, \
    "type " #type " shouldn't be detected as a matcher function")

TEST_IS_MATCHER_FUNCTION(any<int>);
TEST_IS_MATCHER_FUNCTION(any<char>);
TEST_IS_MATCHER_FUNCTION(equals<long>);
TEST_IS_MATCHER_FUNCTION(equals<char const*>);

match_result matcher_function(int const&);
TEST_IS_MATCHER_FUNCTION(decltype(&matcher_function));

struct matcher_functor {
  match_result operator() (char const&) const;
};
TEST_IS_MATCHER_FUNCTION(matcher_functor);

TEST_IS_NOT_MATCHER_FUNCTION(void);
TEST_IS_NOT_MATCHER_FUNCTION(int);
TEST_IS_NOT_MATCHER_FUNCTION(char[]);

match_result no_cref_function(int);
TEST_IS_NOT_MATCHER_FUNCTION(decltype(&no_cref_function));

match_result binary_function(int const&, int const&);
TEST_IS_NOT_MATCHER_FUNCTION(decltype(&binary_function));

int int_function(int const&);
TEST_IS_NOT_MATCHER_FUNCTION(decltype(&int_function));

struct no_cref_functor {
  match_result operator() (char) const;
};
TEST_IS_NOT_MATCHER_FUNCTION(no_cref_functor);

struct binary_functor {
  match_result operator() (char const&, char const&) const;
};
TEST_IS_NOT_MATCHER_FUNCTION(binary_functor);

struct char_functor {
  char operator() (char const&) const;
};
TEST_IS_NOT_MATCHER_FUNCTION(char_functor);

} // namespace

