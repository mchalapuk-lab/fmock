// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_HPP_
#define FMOCK_HPP_

#include "fmock/detail/shared_mock.hpp"
#include "fmock/detail/answer_builder.hpp"
#include "fmock/detail/make_matcher.hpp"
#include "fmock/types/arg_of.hpp"

namespace fmock {

template <class return_t = void>
class function {
 public:
  template <class arg_t>
  using matcher_of = decltype(detail::make_matcher(std::declval<arg_t>()));

  template <class arg_t>
  using ensure_arg_type = types::arg_of<matcher_of<arg_t>>;

  function() = default;
  function(function const& rhs) = default;
  function(function&& rhs) : impl(std::move(rhs.impl)) {}
  ~function() throw(expect_error) {}

  template <class ...arg_ts>
  detail::answer_builder<return_t, typename ensure_arg_type<arg_ts>::type...>
  expect_call(arg_ts ...args) {
    return decltype(expect_call(args...))(impl, detail::make_matcher(args)...);
  }

  template <class ...arg_ts>
  return_t operator() (arg_ts ...args) noexcept(false) {
    return impl->call<return_t>(std::forward<arg_ts>(args)...);
  }
 private:
  detail::shared_mock impl;
}; // class function

} // namespace fmock

#endif // include guard

