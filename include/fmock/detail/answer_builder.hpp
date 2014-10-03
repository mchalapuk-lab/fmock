// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_ANSWER_BUILDER_HPP_
#define FMOCK_DETAIL_ANSWER_BUILDER_HPP_

#include "fmock/matcher.hpp"
#include "fmock/detail/mock.hpp"
#include "fmock/detail/constructor.hpp"
#include "fmock/detail/answer.hpp"

#include <memory>

namespace fmock {
namespace detail {

template <class return_t, class ...arg_ts>
class answer_builder {
 public:
  answer_builder(detail::shared_mock mock, matcher<arg_ts> *... matchers) :
    mock_impl(mock),
    arg_matchers(std::shared_ptr<matcher<arg_ts>>(matchers)...),
    answer_function(
        [] (arg_ts...) { return detail::constructor<return_t>(); }
        ) {

    assert(mock_impl.get());
  }
  answer_builder(answer_builder &&rhs) :
    mock_impl(std::move(rhs.mock_impl)),
    arg_matchers(std::move(rhs.arg_matchers)),
    answer_function(std::move(rhs.answer_function)) {
  }
  ~answer_builder() {
    if (!mock_impl) {
      return;
    }
    auto exp = detail::make_typed_expectation(arg_matchers, answer_function);
    mock_impl->add_expectation(exp);
  }
 private:
  detail::shared_mock mock_impl;

  std::tuple<std::shared_ptr<matcher<arg_ts>>...> arg_matchers;
  answer<return_t(arg_ts...)> answer_function;
}; // class answer_builder

} // namespace detail
} // namespace fmock

#endif // include guard

