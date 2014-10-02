// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_TYPES_IS_MATCHER_HPP_
#define FMOCK_TYPES_IS_MATCHER_HPP_

#include "fmock/matcher.hpp"
#include "fmock/types/has_call_operator.hpp"
#include "fmock/types/signature_of.hpp"
#include "fmock/types/is_function_or_method.hpp"

#include <type_traits>

namespace fmock {
namespace types {

template <class arg_t, bool is_functional = false>
struct is_matcher_helper : public std::false_type {
}; // struct is_matcher_helper

template <class arg_t>
struct is_matcher {
  static bool const value = is_matcher_helper<arg_t,
    is_function_or_method<arg_t>::value || has_call_operator<arg_t>::value
    >::value;
}; // struct is_matcher

template <class signature_t>
struct is_matcher_signature : public std::false_type {
}; // struct is_matcher_signature

template <class function_t>
struct is_matcher_helper<function_t, true> :
    public is_matcher_signature<typename signature_of<function_t>::type> {
};

template <class arg_t>
struct is_matcher_signature<match_result(arg_t const&)> :
    public std::true_type {
};

template <class signature_t>
struct assert_signature_is_matcher {
  static_assert(is_matcher_signature<signature_t>::value,
      "signature_t is not a matcher");
}; // struct assert_signature_is_matcher

template <class functional_t>
struct assert_is_matcher :
  public assert_signature_is_matcher<typename signature_of<functional_t>::type
  > {
}; // struct assert_is_matcher

} // namespace types
} // namespace fmock

#endif // include guard

