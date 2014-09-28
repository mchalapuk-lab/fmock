// licence: GPLv3
// author: Maciej Chałapuk

#include "fmock/fmock.hpp"

#include <exception>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace fmock;

TEST(throw_exception, when_expected_nullary_call_not_satisfied) {
  ASSERT_THROW({
    function().expect_call<void>();
  }, detail::expect_error);
}

TEST(throw_exception, on_unexpected_nullary_call) {
  ASSERT_THROW({
    function tested_mock;
    tested_mock();
  }, detail::expect_error);
}

