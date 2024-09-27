#include "test.h"
#include "gtest/gtest.h"
#include <sys/types.h>

namespace test_zero_copy_byte_types {

using namespace std::literals;
using namespace zpp::bits::literals;

TEST(test_zero_copy_byte_types, span_const_byte) {
  auto [data, in, out] = zpp::bits::data_in_out();
  out("hello"sv).or_throw();

  std::span<const std::byte> s;
  in(s).or_throw();

  EXPECT_EQ(s.size(), "hello"sv.size());
  EXPECT_EQ(std::memcmp("hello"sv.data(), s.data(), "hello"sv.size()), 0);
}

TEST(test_zero_copy_byte_types, unsized_span_const_byte) {
  auto [data, in, out] = zpp::bits::data_in_out();
  out(zpp::bits::unsized("hello"sv)).or_throw();

  std::span<const std::byte> s;
  in(zpp::bits::unsized(s)).or_throw();

  EXPECT_EQ(s.size(), "hello"sv.size());
  EXPECT_EQ(std::memcmp("hello"sv.data(), s.data(), "hello"sv.size()), 0);
}

TEST(test_zero_copy_byte_types, span_const_char) {
  auto [data, in, out] = zpp::bits::data_in_out<char>();
  out("hello"sv).or_throw();

  std::span<const char> s;
  in(s).or_throw();

  EXPECT_EQ(s.size(), "hello"sv.size());
  EXPECT_EQ(std::memcmp("hello"sv.data(), s.data(), "hello"sv.size()), 0);
}

TEST(test_zero_copy_byte_types, unsized_span_const_char) {
  auto [data, in, out] = zpp::bits::data_in_out<char>();
  out(zpp::bits::unsized("hello"sv)).or_throw();

  std::span<const char> s;
  in(zpp::bits::unsized(s)).or_throw();

  EXPECT_EQ(s.size(), "hello"sv.size());
  EXPECT_EQ(std::memcmp("hello"sv.data(), s.data(), "hello"sv.size()), 0);
}

TEST(test_zero_copy_byte_types, span_const_unsigned_char) {
  auto [data, in, out] = zpp::bits::data_in_out<unsigned char>();
  out("hello"sv).or_throw();

  std::span<const unsigned char> s;
  in(s).or_throw();

  EXPECT_EQ(s.size(), "hello"sv.size());
  EXPECT_EQ(std::memcmp("hello"sv.data(), s.data(), "hello"sv.size()), 0);
}

TEST(test_zero_copy_byte_types, unsized_span_const_unsigned_char) {
  auto [data, in, out] = zpp::bits::data_in_out<unsigned char>();
  out(zpp::bits::unsized("hello"sv)).or_throw();

  std::span<const unsigned char> s;
  in(zpp::bits::unsized(s)).or_throw();

  EXPECT_EQ(s.size(), "hello"sv.size());
  EXPECT_EQ(std::memcmp("hello"sv.data(), s.data(), "hello"sv.size()), 0);
}

TEST(test_zero_copy_byte_types, string_view) {
  auto [data, in, out] = zpp::bits::data_in_out<char>();
  out("hello"sv).or_throw();

  std::string_view s;
  in(s).or_throw();

  EXPECT_EQ(s.size(), "hello"sv.size());
  EXPECT_EQ(std::memcmp("hello"sv.data(), s.data(), "hello"sv.size()), 0);
}

TEST(test_zero_copy_byte_types, plain_string_view) {
  auto [data, out] = zpp::bits::data_out();
  auto [dataIn, in] = zpp::bits::data_in();

  // Data to transfer
  std::string_view s1{"This is a string view"};

  // Encode data
  auto result = out(s1);
  EXPECT_FALSE(failure(result));

  // Emulate data transfer
  dataIn = data;

  // Decode data
  std::string_view s2;
  result = in(s2);
  EXPECT_TRUE(!failure(result));

  // Check data
  EXPECT_EQ(s1, s2);

  // Check data location is different (it was truly transferred)
  EXPECT_NE(s1.data(), s2.data());

  // Check data location is within the "in" buffer
  EXPECT_TRUE(s2.data() >= reinterpret_cast<const char *>(dataIn.data()));
  EXPECT_TRUE(s2.data() <
              reinterpret_cast<const char *>(dataIn.data() + dataIn.size()));
}

TEST(test_zero_copy_byte_types, combination_views) {
  auto [data, out] = zpp::bits::data_out();
  auto [dataIn, in] = zpp::bits::data_in();

  struct data_view {
    std::string_view s;
    std::span<const std::byte> v;
  };

  // Data to transfer
  std::string s1{"hello"};
  std::vector<std::byte> v1 = {std::byte{'w'}, std::byte{'o'}, std::byte{'r'},
                               std::byte{'l'}, std::byte{'d'}};
  data_view d1{s1, v1};

  // Encode data
  auto result = out(d1);

  // Emulate data transfer
  dataIn = data;

  // Decode data
  data_view d2;
  result = in(d2);

  // Check data
  EXPECT_EQ(d1.s, d2.s);
  EXPECT_NE(d1.v.data(), d2.v.data());
  EXPECT_EQ(d1.v.size(), d2.v.size());
  EXPECT_EQ(std::memcmp(d1.v.data(), d2.v.data(), d1.v.size()), 0);
}

TEST(test_zero_copy_byte_types, unsized_string_view) {
  auto [data, in, out] = zpp::bits::data_in_out<char>();
  out(zpp::bits::unsized("hello"sv)).or_throw();

  std::string_view s;
  in(zpp::bits::unsized(s)).or_throw();

  EXPECT_EQ(s.size(), "hello"sv.size());
  EXPECT_EQ(std::memcmp("hello"sv.data(), s.data(), "hello"sv.size()), 0);
}

} // namespace test_zero_copy_byte_types
