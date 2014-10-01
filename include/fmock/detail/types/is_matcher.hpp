// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_TYPES_IS_MATCHER_HPP_
#define FMOCK_DETAIL_TYPES_IS_MATCHER_HPP_

#include "fmock/detail/matcher.hpp"
#include "fmock/detail/types/has_call_operator.hpp"
#include "fmock/detail/types/signature_of.hpp"

#include <type_traits>

namespace fmock {
namespace detail {
namespace types {

template <class type>
struct is_function_or_method; // struct is_function_or_method

template <
    class arg_t,
    bool is_function = is_function_or_method<arg_t>::value,
    bool is_functor = has_call_operator<arg_t>::value
    >
struct is_matcher {
  static bool const value = false;
}; // struct is_matcher

template <class type>
struct is_matcher<type, true, false> {
  typedef signature_of<type> signature_type;
  typedef typename signature_type::return_type return_type;
  typedef typename signature_type::arg_types arg_types;

  static bool const value = std::is_same<match_result, return_type>::value
    && 1 == std::tuple_size<arg_types>();
};

template <class arg_t>
struct is_matcher<arg_t, false, true> {
  static bool const value = is_matcher<decltype(&arg_t::operator())>::value;
};

template <class type>
struct is_function_or_method {
  static bool const value = std::is_function<type>::value
    || std::is_member_function_pointer<type>::value;
};

} // namespace types
} // namespace detail
} // namespace fmock

#endif // include guard


