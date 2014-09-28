// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_ANSWER_BUILDER_HPP_
#define FMOCK_DETAIL_ANSWER_BUILDER_HPP_

#include "fmock/detail/mock.hpp"
#include "fmock/detail/expect_error.hpp"
#include "fmock/detail/matchers/any.hpp"
#include "fmock/detail/constructor.hpp"

namespace fmock {
namespace detail {

template <class return_type, class ...arg_types>
class answer_builder {
 public:
  answer_builder(detail::shared_mock mock) :
    impl(mock),
    matchers({ detail::matchers::any<arg_types>()... }),
    answer([] (arg_types...) { return detail::constructor<return_type>(); }) {

    assert(impl.get());
  }
  ~answer_builder() {
    auto exp = detail::make_typed_expectation<return_type>(matchers, answer);
    impl->add_expectation(exp);
  }
 private:
  detail::shared_mock impl;

  std::tuple<detail::matcher<arg_types>...> matchers;
  std::function<return_type(arg_types...)> answer;
}; // class answer_builder

} // namespace detail
} // namespace fmock

#endif // include guard

