// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_MATCHER_HPP_
#define FMOCK_DETAIL_MATCHER_HPP_

#include <functional>

namespace fmock {
namespace detail {

enum class match_result {
  SUCCESS = 1,
  FAILURE = 0,
}; // enum class match_result

template <class arg_type>
using matcher = std::function<match_result (arg_type)>;

} // namespace detail
} // namespace fmock

#endif // include guard

