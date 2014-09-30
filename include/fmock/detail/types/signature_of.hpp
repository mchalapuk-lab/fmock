// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_TYPES_SIGNATURE_OF_HPP_
#define FMOCK_DETAIL_TYPES_SIGNATURE_OF_HPP_

#include <tuple>
#include <type_traits>
#include <functional>

namespace fmock {
namespace detail {
namespace types {

template <class func_t>
struct signature_helper {
}; // struct signature_helper

template <class return_t, class ...arg_ts>
struct signature_helper<return_t(arg_ts...)> {
  typedef return_t return_type;
  typedef std::tuple<arg_ts...> arg_types;
  using type = return_t(arg_ts...);
};

template <class type>
struct remove_class {
}; // struct remove_class

template <class owner, class return_t, class ...arg_ts>
struct remove_class<return_t(owner::*)(arg_ts...)> {
  using type = return_t(arg_ts...);
};
template <class owner, class return_t, class ...arg_ts>
struct remove_class<return_t(owner::*)(arg_ts...)const> {
  using type = return_t(arg_ts...);
};
template <class owner, class return_t, class ...arg_ts>
struct remove_class<return_t(owner::*)(arg_ts...)volatile> {
  using type = return_t(arg_ts...);
};
template <class owner, class return_t, class ...arg_ts>
struct remove_class<return_t(owner::*)(arg_ts...)const volatile> {
  using type = return_t(arg_ts...);
};
template <class return_t, class ...arg_ts>
struct remove_class<return_t(arg_ts...)> {
  using type = return_t(arg_ts...);
};

template <class free_or_member>
struct signature_of {
 private:
  typedef signature_helper<typename remove_class<
    typename std::remove_pointer<free_or_member>::type>::type> helper_t;
 public:
  typedef typename helper_t::return_type return_type;
  typedef typename helper_t::arg_types arg_types;
  using type = typename helper_t::type;
}; // struct signature_of

} // namespace types
} // namespace detail
} // namespace fmock

#endif // include guard

