// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_CONSTRUCTOR_HPP_
#define FMOCK_DETAIL_CONSTRUCTOR_HPP_

namespace fmock {
namespace detail {

template <class constructed_type>
struct constructor {
  constructed_type operator() () const noexcept(constructed_type()) {
    return constructed_type();
  }
}; // struct constructor

} // namespace detail
} // namespace fmock

#endif // include guard

