// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_TO_STR_HPP_
#define FMOCK_TO_STR_HPP_

#include <sstream>
#include <typeinfo>
#include <memory>

#include <cxxabi.h>

namespace fmock {

template <class arg_t>
std::string to_str(arg_t const& arg) {
  std::stringstream builder;
  builder << arg;
  return builder.str();
}

template <void* = nullptr>
std::string to_str(std::type_info const& type) {
  int status;
  std::unique_ptr<char[], void (*)(void*)> result(
    abi::__cxa_demangle(type.name(), 0, 0, &status),
    std::free
    );
  return result.get() ?
    std::string(result.get()) :
    "!!type print error!!";
}

} // namespace fmock

#endif // include guard

