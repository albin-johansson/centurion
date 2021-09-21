#include "video/unicode_string.hpp"

#include <gtest/gtest.h>

#include <cereal/types/vector.hpp>

#include "serialization_utils.hpp"

using namespace cen::literals;

TEST(UnicodeString, Defaults)
{
  const cen::unicode_string str;
  ASSERT_EQ(0, str.size());
  ASSERT_TRUE(str.empty());

  ASSERT_EQ(0, str.at(0));  // null-terminator
}

TEST(UnicodeString, InitializerListConstructor)
{
  const cen::unicode_string str = {'a', 'b', 'c'};
  ASSERT_EQ(3, str.size());
  ASSERT_FALSE(str.empty());

  ASSERT_EQ('a', str.at(0));
  ASSERT_EQ('b', str.at(1));
  ASSERT_EQ('c', str.at(2));
  ASSERT_EQ(0, str.at(3));  // null-terminator

  ASSERT_EQ('a', str[0]);
  ASSERT_EQ('b', str[1]);
  ASSERT_EQ('c', str[2]);
}

TEST(UnicodeString, Iteration)
{
  const cen::unicode_string str = {'a', 'b', 'c'};

  ASSERT_EQ(3, str.end() - str.begin());

  int count = 0;
  for (const auto ch : str) {
    ASSERT_NE(0, ch);
    ++count;
  }

  ASSERT_EQ(3, count);
  ASSERT_EQ(0, str.at(3));  // null-terminator
}

TEST(UnicodeString, Append)
{
  cen::unicode_string str;

  str.append('A'_uni);
  ASSERT_EQ(1, str.size());
  ASSERT_EQ('A'_uni, str.at(0));

  str.append(0x1F308_uni);
  ASSERT_EQ(2, str.size());
  ASSERT_EQ(0x1F308_uni, str.at(1));
}

TEST(UnicodeString, AppendVariadic)
{
  cen::unicode_string str;

  str.append('B'_uni, 'A'_uni, 'R'_uni);
  ASSERT_EQ(3, str.size());
  ASSERT_EQ('B'_uni, str.at(0));
  ASSERT_EQ('A'_uni, str.at(1));
  ASSERT_EQ('R'_uni, str.at(2));
}

TEST(UnicodeString, AdditionAssignmentOperator)
{
  cen::unicode_string str;

  str += 'Z'_uni;
  ASSERT_EQ(1, str.size());
  ASSERT_EQ('Z'_uni, str.at(0));

  str += 'Q'_uni;
  ASSERT_EQ(2, str.size());
  ASSERT_EQ('Q'_uni, str.at(1));
}

TEST(UnicodeString, PopBack)
{
  cen::unicode_string str;

  str += 'A'_uni;
  ASSERT_FALSE(str.empty());
  ASSERT_EQ(1, str.size());

  str.pop_back();
  ASSERT_TRUE(str.empty());
  ASSERT_EQ(0, str.size());  // NOLINT
  ASSERT_EQ(0, str.at(0));   // null-terminator

  ASSERT_NO_THROW(str.pop_back());
  ASSERT_NO_THROW(str.pop_back());
  ASSERT_NO_THROW(str.pop_back());

  ASSERT_TRUE(str.empty());
  ASSERT_EQ(0, str.size());  // NOLINT
  ASSERT_EQ(0, str.at(0));   // null-terminator
}

TEST(UnicodeString, At)
{
  cen::unicode_string str;

  ASSERT_NO_THROW(str.at(0u));  // null-terminator
  ASSERT_ANY_THROW(str.at(123u));
  ASSERT_ANY_THROW(str.at(1u));

  str += 'T'_uni;
  ASSERT_EQ('T'_uni, str.at(0u));
}

TEST(UnicodeString, Data)
{
  cen::unicode_string str;
  const auto& cStr = str;

  ASSERT_TRUE(str.data());
  ASSERT_TRUE(cStr.data());

  ASSERT_EQ(0, *str.data());

  str += 'b'_uni;

  ASSERT_TRUE(str.data());
  ASSERT_EQ('b'_uni, *str.data());
  ASSERT_EQ(0, str.data()[1]);
}

TEST(UnicodeString, Empty)
{
  cen::unicode_string str;
  ASSERT_TRUE(str.empty());

  str += 'A'_uni;
  ASSERT_FALSE(str.empty());
}

TEST(UnicodeString, Reserve)
{
  cen::unicode_string str;

  str.reserve(10u);
  ASSERT_EQ(10u, str.capacity());
}

TEST(UnicodeString, EqualityOperator)
{
  {  // Reflexivity
    const cen::unicode_string str;
    ASSERT_EQ(str, str);
  }

  {  // Two default constructed strings
    const cen::unicode_string fst;
    const cen::unicode_string snd;
    ASSERT_EQ(fst, snd);
    ASSERT_EQ(snd, fst);
  }

  {  // Two equal strings
    const cen::unicode_string fst{'A'_uni, 'B'_uni, 'C'_uni};
    const cen::unicode_string snd{fst};  // NOLINT

    ASSERT_EQ(fst, snd);
    ASSERT_EQ(snd, fst);
  }

  {  // Two different strings
    const cen::unicode_string fst{'F'_uni, 'O'_uni, 'O'_uni};
    const cen::unicode_string snd{'B'_uni, 'A'_uni, 'R'_uni};

    ASSERT_FALSE(fst == snd);
    ASSERT_FALSE(snd == fst);
  }

  {  // Different size strings
    const cen::unicode_string fst{'A'_uni, 'B'_uni};
    const cen::unicode_string snd{'A'_uni, 'B'_uni, 'C'_uni};

    ASSERT_FALSE(fst == snd);
    ASSERT_FALSE(snd == fst);
  }
}

TEST(UnicodeString, InequalityOperator)
{
  {  // Self
    const cen::unicode_string str;
    ASSERT_FALSE(str != str);
  }

  {  // Two default constructed strings
    const cen::unicode_string fst;
    const cen::unicode_string snd;
    ASSERT_FALSE(fst != snd);
    ASSERT_FALSE(snd != fst);
  }

  {  // Two equal strings
    const cen::unicode_string fst{'A'_uni, 'B'_uni, 'C'_uni};
    const cen::unicode_string snd{fst};  // NOLINT

    ASSERT_FALSE(fst != snd);
    ASSERT_FALSE(snd != fst);
  }

  {  // Two different strings
    const cen::unicode_string fst{'F'_uni, 'O'_uni, 'O'_uni};
    const cen::unicode_string snd{'B'_uni, 'A'_uni, 'R'_uni};

    ASSERT_NE(fst, snd);
    ASSERT_NE(snd, fst);
  }

  {  // Different size strings
    const cen::unicode_string fst{'A'_uni, 'B'_uni};
    const cen::unicode_string snd{'A'_uni, 'B'_uni, 'C'_uni};

    ASSERT_NE(fst, snd);
    ASSERT_NE(snd, fst);
  }
}

TEST(UnicodeString, Serialize)
{
  cen::unicode_string string{'f', 'o', 'o', 'b', 'a', 'r'};
  serialize_save("unicode_string.binary", string);

  const auto other = serialize_create<cen::unicode_string>("unicode_string.binary");
  ASSERT_EQ(string, other);
}
