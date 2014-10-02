// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_TYPES_IS_FUNCTION_OR_METHOD_HPP_
#define FMOCK_DETAIL_TYPES_IS_FUNCTION_OF_METHOD_HPP_

#include <tuple>

namespace fmock {
namespace detail {
namespace types {

template <class type>
struct is_function_or_method {
  static bool const value = std::is_function<type>::value
    || std::is_member_function_pointer<type>::value;
}; // struct is_function_or_method

} // namespace types
} // namespace detail
} // namespace fmock

#endif // include guard

