// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_EXPECT_ERROR_HPP_
#define FMOCK_EXPECT_ERROR_HPP_

#include <exception>
#include <forward_list>

namespace fmock {

struct expect_error : std::runtime_error {
  expect_error(std::string message) : std::runtime_error(message) {}
}; // struct expect_error

} // namespace fmock

#endif // include guard

