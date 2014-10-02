// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_TYPES_AT_HPP_
#define FMOCK_TYPES_AT_HPP_

#include <tuple>

namespace fmock {
namespace types {

template <size_t type_index, class tuple_type>
struct at {
  typedef decltype(std::get<type_index>(std::declval<tuple_type>())) type;
}; // struct at

} // namespace types
} // namespace fmock

#endif // include guard

