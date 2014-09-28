// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_DETAIL_MATCHER_HPP_
#define FMOCK_DETAIL_MATCHER_HPP_

#include <functional>

namespace fmock {
namespace detail {

template <class arg_type>
using matcher = std::function<bool (arg_type)>;

} // namespace detail
} // namespace fmock

#endif // include guard

