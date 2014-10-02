// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_TYPES_AT_HPP_
#define FMOCK_DETAIL_TYPES_AT_HPP_

#include <tuple>

namespace fmock {
namespace detail {
namespace types {

template <size_t type_index, class tuple_type>
struct at {
  typedef decltype(std::get<type_index>(std::declval<tuple_type>())) type;
};

} // namespace types
} // namespace detail
} // namespace fmock

#endif // include guard

