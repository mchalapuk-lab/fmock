// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_SHARED_MOCK_HPP_
#define FMOCK_DETAIL_SHARED_MOCK_HPP_

#include "fmock/detail/mock.hpp"
#include "fmock/detail/expect_error.hpp"

namespace fmock {
namespace detail {

class shared_mock {
 public:
  shared_mock() = default;
  shared_mock(shared_mock const& rhs) : ptr(rhs.ptr) {
    ptr->count += 1;
  }
  shared_mock(shared_mock && rhs) : ptr(rhs.ptr) {
    rhs.ptr = nullptr;
  }
  ~shared_mock() throw(expect_error) {
    if (ptr && 0 == (ptr->count -= 1)) {
      delete ptr;
    }
  }

  mock* operator->() const noexcept(true) {
    return get();
  }
  mock* get() const noexcept(true) {
    return &ptr->impl;
  }
 private:
  struct pointer {
    size_t count = 1;
    mock impl;

    pointer() = default;
    pointer(pointer const&) = delete;
    pointer(pointer &&) = delete;
  }; // struct pointer

  pointer *ptr = new pointer;
}; // class shared_mock

} // namespace detail
} // namespace fmock

#endif // include guard

