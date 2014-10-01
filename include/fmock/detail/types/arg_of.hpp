// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_TYPES_ARG_OF_HPP_
#define FMOCK_DETAIL_TYPES_ARG_OF_HPP_

#include "fmock/detail/types/signature_of.hpp"

#include <tuple>

namespace fmock {
namespace detail {
namespace types {

template <class tuple_t>
struct first_type; // struct first_type

template <class matcher_t>
struct arg_of {
 private:
  typedef decltype(&matcher_t::operator()) operator_type;
  typedef typename signature_of<operator_type>::arg_types arg_types;
 public:
  typedef typename first_type<arg_types>::type type;
}; // struct arg_of

template<class head_t, class ...tail_ts>
struct first_type<std::tuple<head_t, tail_ts...>> {
  typedef head_t type;
};

} // namespace types
} // namespace detail
} // namespace fmock

#endif // include guard

