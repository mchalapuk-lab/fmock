// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_MATCHERS_EQUALS_HPP_
#define FMOCK_DETAIL_MATCHERS_EQUALS_HPP_

namespace fmock {
namespace detail {
namespace matchers {

template <class arg_t>
class equals {
 public:
  equals(arg_t const& val) : value(val) {}

  bool operator() (arg_t const& arg) const {
    return (value == arg);
  }
 private:
  arg_t const& value;
}; // class equals

} // namespace matchers
} // namespace detail
} // namespace fmock

#endif // include guard

