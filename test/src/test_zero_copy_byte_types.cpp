#include "test.h"
#include "gtest/gtest.h"

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
  std::string_view s{"This is a string view"};

  // Encode data
  auto result = out(s);
  EXPECT_TRUE(!failure(result));

  // Emulate data transfer
  dataIn = data;

  // Decode data (I would like to use string_view as type here, not
  // std::span<const std::byte>)
  std::string_view s2;
  result = in(s2);
  EXPECT_TRUE(!failure(result));

  // Check data
  EXPECT_TRUE(s == s2);

  // Check data location is different (it was truly transferred)
  EXPECT_TRUE(s.data() != s2.data());

  EXPECT_TRUE(s2.data() >= reinterpret_cast<const char *>(dataIn.data()));
  EXPECT_TRUE(s2.data() <
              reinterpret_cast<const char *>(dataIn.data() + dataIn.size()));
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
