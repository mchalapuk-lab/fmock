// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_MATCHERS_ANY_HPP_
#define FMOCK_MATCHERS_ANY_HPP_

#include "fmock/matcher.hpp"
#include "fmock/to_str.hpp"
#include "fmock/types/is_matcher.hpp"

#include <sstream>

namespace fmock {
namespace matchers {

template <class arg_t>
struct any : public matcher<arg_t> {
  match_result operator() (arg_t const&) const {
    return match_result::SUCCESS;
  }
  std::string to_str() const {
    std::stringstream stringbuilder;
    stringbuilder << "{ any " << fmock::to_str(typeid(arg_t)) << " }";
    return stringbuilder.str();
  }
}; // struct any

} // namespace matchers
} // namespace fmock

#endif // include guard

