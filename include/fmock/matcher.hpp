// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_MATCHER_HPP_
#define FMOCK_MATCHER_HPP_

#include <functional>

namespace fmock {

enum class match_result {
  SUCCESS = 1,
  FAILURE = 0,
}; // enum class match_result

template <class arg_t>
struct matcher {
  virtual match_result operator() (arg_t const&) const = 0;
  virtual std::string to_str() const = 0;
}; // struct matcher 

} // namespace fmock

#endif // include guard

