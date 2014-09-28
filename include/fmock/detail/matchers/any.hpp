// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_MATCHERS_ANY_HPP_
#define FMOCK_DETAIL_MATCHERS_ANY_HPP_

namespace fmock {
namespace detail {
namespace matchers {

template <class arg_type>
struct any {
  bool operator() (arg_type arg) const noexcept(true) {
    return true;
  }
}; // struct any

} // namespace matchers
} // namespace detail
} // namespace fmock

#endif // include guard


