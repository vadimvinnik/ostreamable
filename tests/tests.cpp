#include "ostreamable.h"

#include <sstream>
#include <string>
#include <vector>

#include <catch.hpp>

TEST_CASE("empty wrapper")
{
  ostreamable wrapped;

  std::ostringstream s;

  s << wrapped;

  CHECK(s.str().empty());
}

TEST_CASE("int value wrapped")
{
  auto const value { 1002 };

  ostreamable wrapped { value };

  std::ostringstream s;

  s << wrapped;

  CHECK(s.str() == std::to_string(value));
}

TEST_CASE("std::string wrapped")
{
  std::string const value { "abcde" };
  
  ostreamable wrapped { value };

  std::ostringstream s;

  s << wrapped;

  CHECK(s.str() == value);
}

struct custom_streamable
{
  static constexpr auto as_string { "custom streamable object" };
};

std::ostream& operator<<(std::ostream &s, custom_streamable const&)
{
  s << custom_streamable::as_string;
  return s;
}

TEST_CASE("custom streamable object")
{
  custom_streamable const value;

  ostreamable wrapped { value };

  std::ostringstream s;

  s << wrapped;

  CHECK(s.str() == custom_streamable::as_string);
}

TEST_CASE("wrapper assignment changes type")
{
  auto const value1 { 1002 };
  std::string const value2 { "abcde" };
  custom_streamable const value3;

  ostreamable wrapped1 { value1 };
  ostreamable wrapped2 { value2 };
  ostreamable wrapped3 { value3 };

  ostreamable wrapped;
  
  std::ostringstream s;

  s << wrapped;

  wrapped = wrapped1;
  s << wrapped;

  wrapped = wrapped2;
  s << wrapped;

  wrapped = wrapped3;
  s << wrapped;

  auto const expected
    = std::to_string(value1)
    + value2
    + custom_streamable::as_string;

  CHECK(s.str() == expected);
}

TEST_CASE("value assignment changes type")
{
  auto const value1 { 1002 };
  std::string const value2 { "abcde" };
  custom_streamable const value3;

  ostreamable wrapped;
  
  std::ostringstream s;

  s << wrapped;

  wrapped = value1;
  s << wrapped;

  wrapped = value2;
  s << wrapped;

  wrapped = value3;
  s << wrapped;

  auto const expected
    = std::to_string(value1)
    + value2
    + custom_streamable::as_string;

  CHECK(s.str() == expected);
}

TEST_CASE("heterogeneous container")
{
  auto const value1 { 1002 };
  std::string const value2 { "abcde" };
  custom_streamable const value3;

  std::vector<ostreamable> v;

  v.emplace_back(value1);
  v.emplace_back(value2);
  v.emplace_back(value3);

  std::ostringstream s;

  for (auto const& x : v)
  {
    s << x;
  }

  auto const expected
    = std::to_string(value1)
    + value2
    + custom_streamable::as_string;

  CHECK(s.str() == expected);
}

