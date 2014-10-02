// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_ANSWER_HPP_
#define FMOCK_DETAIL_ANSWER_HPP_

#include <functional>

namespace fmock {
namespace detail {

template <class signature_t>
struct answer; // struct answer

template <class return_t, class ...arg_ts>
class answer<return_t(arg_ts...)> {
 public:
  typedef std::function<return_t(arg_ts const&...)> function_t;
  answer(function_t func) : impl(func) {}

  return_t operator() (arg_ts const& ...args) const {
    return impl(args...);
  }
 private:
  function_t impl;
};

} // namespace detail
} // namespace fmock

#endif // include guard

