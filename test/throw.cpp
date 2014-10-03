// licence: GPLv3
// author: Maciej Chałapuk

#include "fmock/fmock.hpp"
#include "fmock/matchers/any.hpp"

#include <exception>
#include <memory>
#include <string>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace fmock;

TEST(throw_exception, when_expected_nullary_call_not_satisfied) {
  function<> tested_mock;
  tested_mock.expect_call();
  try {
    tested_mock.verify();
  } catch (expect_error const& e) {
    ASSERT_EQ(std::string("unsatisfied expectations:\n"
        "  void()\n"), e.what());
  }
}

TEST(throw_exception, on_unexpected_nullary_call) {
  function<> tested_mock;
  try {
    tested_mock();
  } catch (expect_error const& e) {
    ASSERT_EQ(std::string("unexpected call to void();\n"
        "  expected no call\n"), e.what());
  }
}

TEST(throw_exception, on_unexpected_int_call) {
  function<int> tested_mock;
  try {
    auto value = tested_mock();
  } catch (expect_error const& e) {
    ASSERT_EQ(std::string("unexpected call to int();\n"
        "  expected no call\n"), e.what());
  }
}

TEST(throw_exception, on_call_with_lesser_arg_count) {
  function<> tested_mock;
  tested_mock.expect_call(0);
  try {
    tested_mock();
  } catch (expect_error const& e) {
    ASSERT_EQ(std::string("unexpected call to void();\n"
        "  expected void(int)\n"), e.what());
  }
}

TEST(throw_exception, on_call_with_greater_arg_count) {
  function<> tested_mock;
  tested_mock.expect_call();
  try {
    tested_mock(0);
  } catch (expect_error const& e) {
    ASSERT_EQ(std::string("unexpected call to void(int);\n"
        "  expected void()\n"), e.what());
  }
}

TEST(throw_exception, on_call_with_arg_of_wrong_type) {
  function<> tested_mock;
  tested_mock.expect_call(matchers::any<int>());
  try {
    tested_mock(0.0);
  } catch (expect_error const& e) {
    ASSERT_EQ(std::string("unexpected call to void(double);\n"
        "  expected void({ match any int })\n"), e.what());
  }
}

