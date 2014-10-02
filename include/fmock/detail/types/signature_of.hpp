// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_TYPES_SIGNATURE_OF_HPP_
#define FMOCK_DETAIL_TYPES_SIGNATURE_OF_HPP_

#include "fmock/detail/types/remove_class.hpp"
#include "fmock/detail/types/has_call_operator.hpp"

#include <tuple>
#include <type_traits>
#include <functional>

namespace fmock {
namespace detail {
namespace types {

template <class func_t>
struct signature_helper {
}; // struct signature_helper

template <class functional_t, bool is_functor = false>
struct strip_qualifiers {
  typedef typename remove_class<
    typename std::remove_reference<
    typename std::remove_pointer<functional_t>::type
    >::type>::type type;
}; // struct strip_qualifiers

template <class functional_t>
struct signature_of {
 private:
  typedef signature_helper<typename strip_qualifiers<
    functional_t,
    has_call_operator<functional_t>::value
    >::type> helper_t;
 public:
  typedef typename helper_t::return_type return_type;
  typedef typename helper_t::arg_types arg_types;
  using type = typename helper_t::type;
}; // struct signature_of

template <class functional_t>
struct strip_qualifiers<functional_t, true> :
    public strip_qualifiers<decltype(&functional_t::operator())> {
};

template <class return_t, class ...arg_ts>
struct signature_helper<return_t(arg_ts...)> {
  typedef return_t return_type;
  typedef std::tuple<arg_ts...> arg_types;
  using type = return_t(arg_ts...);
};

} // namespace types
} // namespace detail
} // namespace fmock

#endif // include guard

