// licence: GPLv3
// author: Maciej Chałapuk

#include "fmock/fmock.hpp"
#include "fmock/matchers/any.hpp"

#include <exception>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace fmock;

TEST(throw_exception, when_expected_nullary_call_not_satisfied) {
  ASSERT_THROW({
    function<> tested_mock;
    tested_mock.expect_call();
  }, expect_error);
}

TEST(throw_exception, on_unexpected_nullary_call) {
  ASSERT_THROW({
    function<> tested_mock;
    tested_mock();
  }, expect_error);
}

TEST(throw_exception, on_unexpected_int_call) {
  ASSERT_THROW({
    function<int> tested_mock;
    auto value = tested_mock();
  }, expect_error);
}

TEST(throw_exception, on_call_with_lesser_arg_count) {
  ASSERT_THROW({
    function<> tested_mock;
    tested_mock.expect_call(0);
    tested_mock();
  }, expect_error);
}

TEST(throw_exception, on_call_with_greater_arg_count) {
  ASSERT_THROW({
    function<> tested_mock;
    tested_mock.expect_call();
    tested_mock(0);
  }, expect_error);
}

TEST(throw_exception, on_call_with_arg_of_wrong_type) {
  ASSERT_THROW({
    function<> tested_mock;
    tested_mock.expect_call(matchers::any<int>());
    tested_mock(0.0);
  }, expect_error);
}

