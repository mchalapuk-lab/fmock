// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_TYPES_ARG_OF_HPP_
#define FMOCK_TYPES_ARG_OF_HPP_

#include "fmock/matcher.hpp"
#include "fmock/types/signature_of.hpp"
#include "fmock/types/at.hpp"
#include "fmock/types/remove_class.hpp"

#include <type_traits>

namespace fmock {
namespace types {

template <class matcher_t>
struct arg_of_helper {
 private:
  typedef decltype(&matcher_t::operator()) operator_type;
  typedef typename signature_of<operator_type>::arg_types arg_types;
  typedef typename at<0, arg_types>::type arg_type;
 public:
  typedef typename std::remove_const<
    typename std::remove_reference<arg_type>::type>::type type;
}; // struct arg_of_helper

template <class arg_t>
struct arg_of_helper<match_result(arg_t const&)> {
  typedef arg_t type;
};

template <class matcher_t>
struct arg_of {
  typedef
    typename arg_of_helper<
    typename remove_class<
    typename std::remove_reference<
    typename std::remove_pointer<
    matcher_t>::type>::type>::type>::type type;
}; // struct arg_of

} // namespace types
} // namespace fmock

#endif // include guard

