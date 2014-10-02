// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_TYPES_IS_FUNCTION_OR_METHOD_HPP_
#define FMOCK_TYPES_IS_FUNCTION_OF_METHOD_HPP_

#include <type_traits>

namespace fmock {
namespace types {

template <class type>
struct is_function_or_method {
  static bool const value = std::is_function<type>::value
    || std::is_member_function_pointer<type>::value;
}; // struct is_function_or_method

} // namespace types
} // namespace fmock

#endif // include guard

