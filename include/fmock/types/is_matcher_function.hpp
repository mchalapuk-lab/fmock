// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_TYPES_IS_MATCHER_FUNCTION_HPP_
#define FMOCK_TYPES_IS_MATCHER_FUNCTION_HPP_

#include "fmock/matcher.hpp"
#include "fmock/types/has_call_operator.hpp"
#include "fmock/types/signature_of.hpp"

#include <type_traits>

namespace fmock {
namespace types {

template <class arg_t, bool is_functional = false>
struct is_matcher_helper : public std::false_type {
}; // struct is_matcher_helper

template <class arg_t>
struct is_matcher_function {
  static bool const value = is_matcher_helper<arg_t,
    std::is_function<typename std::remove_pointer<arg_t>::type>::value
      || has_call_operator<arg_t>::value
    >::value;
}; // struct is_matcher_function

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

} // namespace types
} // namespace fmock

#endif // include guard

