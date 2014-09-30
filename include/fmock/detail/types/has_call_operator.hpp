// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_TYPES_HAS_CALL_OPERATOR_HPP_
#define FMOCK_DETAIL_TYPES_HAS_CALL_OPERATOR_HPP_

namespace fmock {
namespace detail {
namespace types {

template <class type>
struct has_call_operator {
 private:
  typedef char yes[1];
  typedef char no[2];

  template <class U, U> struct type_check;
  template <class W>
  using SFINAE = type_check<decltype(&W::operator()), &W::operator()> *;

  template <typename X> static yes& test(SFINAE<X>);
  template <typename> static no& test(...);

 public:
  static bool const value = sizeof(test<type>(0)) == sizeof(yes);
}; // struct has_call_operator

} // namespace types
} // namespace detail
} // namespace fmock

#endif // include guard

