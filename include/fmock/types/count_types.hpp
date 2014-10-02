// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_TYPES_COUNT_TYPES_HPP_
#define FMOCK_TYPES_COUNT_TYPES_HPP_

namespace fmock {
namespace types {

template <class ...arg_types>
struct count_types {
}; // struct count_type

template <class head_type, class ...tail_types>
struct count_types<head_type, tail_types...> {
  static size_t const value = 1 + count_types<tail_types...>::value;
};

template <>
struct count_types<> {
  static size_t const value = 0;
};

} // namespace types
} // namespace fmock

#endif // include guard

