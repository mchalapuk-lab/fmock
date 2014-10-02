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

template <class arg_type>
using matcher = std::function<match_result(arg_type const&)>;

} // namespace fmock

#endif // include guard

