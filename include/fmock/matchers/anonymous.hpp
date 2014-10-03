// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_MATCHERS_ANONYMOUS_HPP_
#define FMOCK_MATCHERS_ANONYMOUS_HPP_

#include "fmock/matcher.hpp"

#include <functional>
#include <sstream>
#include <typeinfo>

namespace fmock {
namespace matchers {

template <class arg_t>
struct anonymous : public matcher<arg_t> {
 public:
  typedef std::function<match_result(arg_t const&)> func_type;

  anonymous(func_type f) : func(f) {}

  match_result operator() (arg_t const& arg) const {
    return func(arg);
  }
  std::string to_str() const {
    std::stringstream stringbuilder;
    stringbuilder << "{ anonymous matcher of " << typeid(arg_t).name() << " }";
    return stringbuilder.str();
  }
 private:
  func_type func;
}; // struct anonymous

} // namespace matchers
} // namespace fmock

#endif // include guard

