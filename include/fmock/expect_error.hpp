// licence: GPLv3
// author: Maciej Chałapuk

#ifndef FMOCK_EXPECT_ERROR_HPP_
#define FMOCK_EXPECT_ERROR_HPP_

#include <exception>
#include <forward_list>

namespace fmock {

class expect_error : std::runtime_error {
 public:
  expect_error(std::string message) : std::runtime_error(message) {}

  template <class visitor_type>
  void visit(visitor_type visit) const {
    for (auto error : next_errors) {
      visit(error.what());
    }
    visit(this->what());
  }

  void add_error(expect_error const& error) {
    next_errors.push_front(error);
  }
 private:
  std::forward_list<expect_error> next_errors;
}; // class expect_error

} // namespace fmock

#endif // include guard

