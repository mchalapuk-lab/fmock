// licence: GPLv3
// author: Maciej Chałapuk

#include "fmock/fmock.hpp"

#include <exception>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace fmock;

TEST(throw_exception, when_expected_nullary_call_not_satisfied) {
  ASSERT_THROW({
    function<> tested_mock;
    tested_mock.expect_call();
  }, detail::expect_error);
}

TEST(throw_exception, on_unexpected_nullary_call) {
  ASSERT_THROW({
    function<> tested_mock;
    tested_mock();
  }, detail::expect_error);
}

TEST(throw_exception, on_unexpected_int_call) {
  ASSERT_THROW({
    function<int> tested_mock;
    auto value = tested_mock();
  }, detail::expect_error);
}

TEST(throw_exception, on_call_with_wrong_arg_count) {
  ASSERT_THROW({
    function<> tested_mock;
    tested_mock.expect_call();
    tested_mock(0);
  }, detail::expect_error);
}

