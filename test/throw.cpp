// licence: GPLv3
// author: Maciej Chałapuk

#include "fmock.hpp"

#include <exception>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace fmock;

TEST(throw_exception, when_expected_nullary_call_not_satisfied) {
  EXPECT_THROW({
    function().expect_call<void>();
  }, detail::expect_error);
}

