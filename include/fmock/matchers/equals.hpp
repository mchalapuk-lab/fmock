// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_MATCHERS_EQUALS_HPP_
#define FMOCK_MATCHERS_EQUALS_HPP_

#include "fmock/matcher.hpp"
#include "fmock/to_str.hpp"
#include "fmock/types/is_matcher.hpp"

namespace fmock {
namespace matchers {

template <class arg_t>
class equals : public matcher<arg_t> {
 public:
  equals(arg_t const& val) : value(val) {}

  match_result operator() (arg_t const& arg) const {
    return (value == arg)? match_result::SUCCESS: match_result::FAILURE;
  }
  std::string to_str() const {
    return fmock::to_str(value);
  }
 private:
  arg_t const& value;
}; // class equals

} // namespace matchers
} // namespace fmock

#endif // include guard

