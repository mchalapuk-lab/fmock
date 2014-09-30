// licence: GPLv3
// author: Maciej Chałapuk

#include "fmock/detail/types/signature_of.hpp"

#include <type_traits>

namespace {

using namespace fmock::detail::types;

#define TEST(types) \
static struct { \
  typedef signature_of<typename types::nullary_type> nullary_sig; \
  typedef signature_of<typename types::unary_type> unary_sig; \
  typedef signature_of<typename types::binary_type> binary_sig; \
  typedef signature_of<typename types::provider_type> provider_sig; \
\
  static_assert(std::is_same<void(), nullary_sig::type>::value, \
    "signature of void() " #types " function should be void()"); \
  static_assert(std::is_same<void(int), unary_sig::type>::value, \
    "signature of void(int) " #types " function should be void(int)"); \
  static_assert(std::is_same<void(int,int), binary_sig::type>::value, \
    "signature of void(int,int) " #types " function should be void(int,int)"); \
  static_assert(std::is_same<int(), provider_sig::type>::value, \
    "signature of int() " #types " function should be int()"); \
\
  static_assert(std::is_same<void, nullary_sig::return_type>::value, \
    "return type of void() " #types " function should be void"); \
  static_assert(std::is_same<void, unary_sig::return_type>::value, \
    "return type of void(int) " #types " function should be void"); \
  static_assert(std::is_same<void, binary_sig::return_type>::value, \
    "return type of void(int,int) " #types " function should be void"); \
  static_assert(std::is_same<int, provider_sig::return_type>::value, \
    "return type of int() " #types " function should be int"); \
\
  static_assert(std::is_same<std::tuple<>, nullary_sig::arg_types>::value, \
    "argument types of void() " #types " function should be ()"); \
  static_assert(std::is_same<std::tuple<int>, unary_sig::arg_types>::value, \
    "argument types of void(int) " #types " function should be (int)"); \
  static_assert(std::is_same<std::tuple<int,int>, binary_sig::arg_types>::value, \
    "argument types of void(int,int) " #types " function should be (int,int)"); \
  static_assert(std::is_same<std::tuple<>, provider_sig::arg_types>::value, \
    "argument types of int() " #types " function should be ()"); \
} const types ## test

void free_nullary();
void free_unary(int);
void free_binary(int, int);
int free_provider();

struct free_function {
  typedef decltype(&free_nullary) nullary_type;
  typedef decltype(&free_unary) unary_type;
  typedef decltype(&free_binary) binary_type;
  typedef decltype(&free_provider) provider_type;
};

struct member {
  void nullary();
  void unary(int);
  void binary(int, int);
  int provider();
};

struct member_function {
  typedef decltype(&member::nullary) nullary_type;
  typedef decltype(&member::unary) unary_type;
  typedef decltype(&member::binary) binary_type;
  typedef decltype(&member::provider) provider_type;
};

struct member_function_pointer {
  typedef member_function::nullary_type* nullary_type;
  typedef member_function::unary_type* unary_type;
  typedef member_function::binary_type* binary_type;
  typedef member_function::provider_type* provider_type;
};

struct const_member {
  void nullary() const;
  void unary(int) const;
  void binary(int, int) const;
  int provider() const;
};

struct const_member_function {
  typedef decltype(&const_member::nullary) nullary_type;
  typedef decltype(&const_member::unary) unary_type;
  typedef decltype(&const_member::binary) binary_type;
  typedef decltype(&const_member::provider) provider_type;
};

struct const_member_function_pointer {
  typedef const_member_function::nullary_type* nullary_type;
  typedef const_member_function::unary_type* unary_type;
  typedef const_member_function::binary_type* binary_type;
  typedef const_member_function::provider_type* provider_type;
};

struct volatile_member {
  void nullary() volatile;
  void unary(int) volatile;
  void binary(int, int) volatile;
  int provider() volatile;
};

struct volatile_member_function {
  typedef decltype(&volatile_member::nullary) nullary_type;
  typedef decltype(&volatile_member::unary) unary_type;
  typedef decltype(&volatile_member::binary) binary_type;
  typedef decltype(&volatile_member::provider) provider_type;
};

struct volatile_member_function_pointer {
  typedef volatile_member_function::nullary_type* nullary_type;
  typedef volatile_member_function::unary_type* unary_type;
  typedef volatile_member_function::binary_type* binary_type;
  typedef volatile_member_function::provider_type* provider_type;
};

struct const_volatile_member {
  void nullary() const volatile;
  void unary(int) const volatile;
  void binary(int, int) const volatile;
  int provider() const volatile;
};

struct const_volatile_member_function {
  typedef decltype(&const_volatile_member::nullary) nullary_type;
  typedef decltype(&const_volatile_member::unary) unary_type;
  typedef decltype(&const_volatile_member::binary) binary_type;
  typedef decltype(&const_volatile_member::provider) provider_type;
};

struct const_volatile_member_function_pointer {
  typedef const_volatile_member_function::nullary_type* nullary_type;
  typedef const_volatile_member_function::unary_type* unary_type;
  typedef const_volatile_member_function::binary_type* binary_type;
  typedef const_volatile_member_function::provider_type* provider_type;
};

TEST(free_function);
TEST(member_function);
TEST(member_function_pointer);
TEST(const_member_function);
TEST(const_member_function_pointer);
TEST(volatile_member_function);
TEST(volatile_member_function_pointer);
TEST(const_volatile_member_function);
TEST(const_volatile_member_function_pointer);

} // namespace

