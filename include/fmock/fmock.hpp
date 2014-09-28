// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_HPP_
#define FMOCK_HPP_

#include "fmock/detail/shared_mock.hpp"
#include "fmock/detail/answer_builder.hpp"

namespace fmock {

class function {
 public:
  function() = default;
  function(function const& rhs) = default;
  function(function&& rhs) : impl(std::move(rhs.impl)) {}
  ~function() throw(detail::expect_error) {}

  template <class return_type, class ...arg_types>
  detail::answer_builder<return_type, arg_types...>
  expect_call(detail::matcher<arg_types> const& ...matchers) noexcept(true) {
    return detail::answer_builder<return_type, arg_types...>(impl);
  }

  template <class ...arg_types>
  void operator() (arg_types ...args) noexcept(false) {
    return impl->call<void>(std::forward<arg_types>(args)...);
  }
 private:
  detail::shared_mock impl;
}; // class function

} // namespace fmock

#endif // include guard

