// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_COUNT_ARGS_HPP_
#define FMOCK_DETAIL_COUNT_ARGS_HPP_

namespace fmock {
namespace detail {

template <class ...arg_types>
struct count_args {
}; // struct count_args

template <class head_type, class ...tail_types>
struct count_args<head_type, tail_types...> {
  static size_t const value = 1 + count_args<tail_types...>::value;
};

template <>
struct count_args<> {
  static size_t const value = 0;
};

} // namespace detail
} // namespace fmock

#endif // include guard

