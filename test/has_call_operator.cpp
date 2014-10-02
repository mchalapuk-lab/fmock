// licence: GPLv3
// author: Maciej Chałapuk

#include "fmock/types/has_call_operator.hpp"

#include <functional>

using namespace fmock::types;

namespace {

struct empty {};
struct nullary { void operator()() {} };
struct unary { void operator() (int) {} };
struct provider { int operator() () { return 0; } };

static_assert(!has_call_operator<empty>::value,
    "empty type shouldn't have call operator detected");
static_assert(has_call_operator<nullary>::value,
    "type with void operator() should have call operator detected");
static_assert(has_call_operator<unary>::value,
    "type with void operator(int) should have call operator detected");
static_assert(has_call_operator<provider>::value,
    "type with int operator() should have call operator detected");

static_assert(has_call_operator<std::function<void()>>::value,
    "type with std::function<void()> should have call operator detected");
static_assert(has_call_operator<std::function<int()>>::value,
    "type with std::function<int()> should have call operator detected");
static_assert(has_call_operator<std::function<void(int)>>::value,
    "type with std::function<void(int)> should have call operator detected");
static_assert(has_call_operator<std::function<int(int)>>::value,
    "type with std::function<int(int)> should have call operator detected");

} // namespace

