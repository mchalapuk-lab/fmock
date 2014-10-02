// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_TYPES_REMOVE_CLASS_HPP_
#define FMOCK_TYPES_REMOVE_CLASS_HPP_

namespace fmock {
namespace types {

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

} // namespace types
} // namespace fmock

#endif // include guard

