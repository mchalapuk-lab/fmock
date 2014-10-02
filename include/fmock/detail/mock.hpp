// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_MOCK_HPP_
#define FMOCK_DETAIL_MOCK_HPP_

#include "fmock/detail/expectation.hpp"
#include "fmock/detail/call_check.hpp"
#include "fmock/detail/expect_error.hpp"

#include <exception>
#include <deque>
#include <cassert>

namespace fmock {
namespace detail {

class mock {
 public:
  mock() {}
  mock(mock const&) = delete;
  mock(mock &&) = delete;

  ~mock() throw(detail::expect_error) {
    if (!has_unsatisfied_expectations()) {
      return;
    }
    auto current_error = make_unsatisfied_error();
    if (!std::uncaught_exception()) {
      throw current_error;
    }
    // error not thrown, can't do much about it (TODO stderr??)
  }
 
  template <class return_t, class ...arg_ts>
  return_t call(arg_ts ...args) {
    if (!has_unsatisfied_expectations()) {
      throw make_unexpected_call_error<return_t, arg_ts...>();
    }
    auto const& exp = *expectations.front();

    call_check<return_t, arg_ts...> check;
    if (!check.return_type(exp)) {
      throw make_unexpected_call_error<return_t, arg_ts...>(exp);
    }
    if (!check.arg_count(exp)) {
      throw make_unexpected_call_error<return_t, arg_ts...>(exp);
    }
    if (!check.arg_types(exp)) {
      throw make_unexpected_call_error<return_t, arg_ts...>(exp);
    }

    typedef typed_expectation<return_t, arg_ts...> typed_expectation_type;
    auto const* typed_exp = dynamic_cast<typed_expectation_type const*>(&exp);
    assert(typed_exp != nullptr);

    auto args_tuple = std::forward_as_tuple(args...);
    size_t error_index = check.arg_values(*typed_exp, args_tuple);
    if (error_index != -1) {
      throw make_argument_mismatch_error(*typed_exp, args_tuple, error_index);
    }
    expectations.pop_front();
    return typed_exp->answer_function(std::forward<arg_ts>(args)...);
  }

  void add_expectation(expectation *exp) {
    expectations.emplace_back(exp);
  }
  bool has_unsatisfied_expectations() const noexcept(true) {
    return (expectations.size() != 0);
  }
 private:
  std::deque<std::unique_ptr<expectation>> expectations;

  expect_error make_unsatisfied_error() {
    return expect_error("unsatisfied expectations");
  }
  template <class return_t, class ...arg_ts>
  expect_error make_unexpected_call_error() {
    return expect_error("unexpected call");
  }
  template <class return_t, class ...arg_ts>
  expect_error make_unexpected_call_error(expectation const& exp) {
    return expect_error("unexpected call");
  }
  template <class return_t, class ...arg_ts>
  expect_error make_argument_mismatch_error(
      typed_expectation<return_t, arg_ts...> const& exp,
      std::tuple<arg_ts &...> const& current_args,
      size_t arg_index
      ) {
    return expect_error("argument not matching expectations");
  }
}; // class mock

} // namespace detail
} // namespace fmock

#endif // include guard

