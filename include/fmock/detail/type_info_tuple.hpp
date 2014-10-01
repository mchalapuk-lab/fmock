// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_TYPE_INFO_TUPLE_HPP_
#define FMOCK_DETAIL_TYPE_INFO_TUPLE_HPP_

#include <tuple>

namespace fmock {
namespace detail {

template <size_t list_size>
struct type_info_tuple : type_info_tuple<list_size - 1> {
  template <class tuple_type>
  struct enlarge_tuple;

  typedef typename type_info_tuple<list_size - 1>::type super_tuple;
  typedef typename enlarge_tuple<super_tuple>::type type;
}; // struct type_info_tuple

template <size_t list_size>
template <class ...arg_types>
struct type_info_tuple<list_size>::enlarge_tuple<std::tuple<arg_types...>> {
  typedef std::tuple<arg_types..., std::type_info const*> type;
};

template <>
struct type_info_tuple<0> {
  typedef std::tuple<> type;
};

} // namespace detail
} // namespace fmock

#endif // include guard

