// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_ANSWER_BUILDER_HPP_
#define FMOCK_DETAIL_ANSWER_BUILDER_HPP_

#include "fmock/detail/mock.hpp"
#include "fmock/detail/expect_error.hpp"
#include "fmock/detail/constructor.hpp"

namespace fmock {
namespace detail {

template <class return_type, class ...arg_types>
class answer_builder {
 public:
  answer_builder(detail::shared_mock mock,
                 detail::matcher<arg_types>... matchers) :
    mock_impl(mock),
    arg_matchers(std::make_tuple(matchers...)),
    answer([] (arg_types...) { return detail::constructor<return_type>(); }) {

    assert(mock_impl.get());
  }
  ~answer_builder() {
    auto exp = detail::make_typed_expectation(arg_matchers, answer);
    mock_impl->add_expectation(exp);
  }
 private:
  detail::shared_mock mock_impl;

  std::tuple<detail::matcher<arg_types>...> arg_matchers;
  std::function<return_type(arg_types...)> answer;
}; // class answer_builder

} // namespace detail
} // namespace fmock

#endif // include guard

