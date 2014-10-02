// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_TYPES_ARG_OF_HPP_
#define FMOCK_DETAIL_TYPES_ARG_OF_HPP_

#include "fmock/detail/matcher.hpp"
#include "fmock/detail/types/signature_of.hpp"
#include "fmock/detail/types/at.hpp"

#include <type_traits>

namespace fmock {
namespace detail {
namespace types {

template <class matcher_t>
struct arg_of {
 private:
  typedef decltype(&matcher_t::operator()) operator_type;
  typedef typename signature_of<operator_type>::arg_types arg_types;
  typedef typename at<0, arg_types>::type arg_type;
 public:
  typedef typename std::remove_const<
    typename std::remove_reference<arg_type>::type>::type type;
}; // struct arg_of


} // namespace types
} // namespace detail
} // namespace fmock

#endif // include guard

