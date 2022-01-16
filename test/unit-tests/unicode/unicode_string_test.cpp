#include <gtest/gtest.h>

#include <cereal/types/vector.hpp>

#include "serialization_utils.hpp"
#include "unicode.hpp"

TEST(UnicodeString, Defaults)
{
  const cen::UnicodeString str;
  ASSERT_EQ(0u, str.size());
  ASSERT_TRUE(str.empty());

  ASSERT_EQ(0, str.at(0));  // null-terminator
}

TEST(UnicodeString, InitializerListConstructor)
{
  const cen::UnicodeString str = {'a', 'b', 'c'};
  ASSERT_EQ(3u, str.size());
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
  const cen::UnicodeString str = {'a', 'b', 'c'};

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
  cen::UnicodeString str;

  str.append('A');
  ASSERT_EQ(1u, str.size());
  ASSERT_EQ('A', str.at(0));

  str.append(0xF308);
  ASSERT_EQ(2u, str.size());
  ASSERT_EQ(0xF308, str.at(1));
}

TEST(UnicodeString, AppendVariadic)
{
  cen::UnicodeString str;

  str.append('B', 'A', 'R');
  ASSERT_EQ(3u, str.size());
  ASSERT_EQ('B', str.at(0));
  ASSERT_EQ('A', str.at(1));
  ASSERT_EQ('R', str.at(2));
}

TEST(UnicodeString, AdditionAssignmentOperator)
{
  cen::UnicodeString str;

  str += 'Z';
  ASSERT_EQ(1u, str.size());
  ASSERT_EQ('Z', str.at(0));

  str += 'Q';
  ASSERT_EQ(2u, str.size());
  ASSERT_EQ('Q', str.at(1));
}

TEST(UnicodeString, PopBack)
{
  cen::UnicodeString str;

  str += 'A';
  ASSERT_FALSE(str.empty());
  ASSERT_EQ(1u, str.size());

  str.pop_back();
  ASSERT_TRUE(str.empty());
  ASSERT_EQ(0u, str.size());  // NOLINT
  ASSERT_EQ(0, str.at(0));    // null-terminator

  ASSERT_NO_THROW(str.pop_back());
  ASSERT_NO_THROW(str.pop_back());
  ASSERT_NO_THROW(str.pop_back());

  ASSERT_TRUE(str.empty());
  ASSERT_EQ(0u, str.size());  // NOLINT
  ASSERT_EQ(0, str.at(0));    // null-terminator
}

TEST(UnicodeString, At)
{
  cen::UnicodeString str;

  ASSERT_NO_THROW(str.at(0u));  // null-terminator
  ASSERT_ANY_THROW(str.at(123u));
  ASSERT_ANY_THROW(str.at(1u));

  str += 'T';
  ASSERT_EQ('T', str.at(0u));
}

TEST(UnicodeString, Data)
{
  cen::UnicodeString str;
  const auto& cStr = str;

  ASSERT_TRUE(str.data());
  ASSERT_TRUE(cStr.data());

  ASSERT_EQ(0, *str.data());

  str += 'b';

  ASSERT_TRUE(str.data());
  ASSERT_EQ('b', *str.data());
  ASSERT_EQ(0, str.data()[1]);
}

TEST(UnicodeString, Empty)
{
  cen::UnicodeString str;
  ASSERT_TRUE(str.empty());

  str += 'A';
  ASSERT_FALSE(str.empty());
}

TEST(UnicodeString, Reserve)
{
  cen::UnicodeString str;

  str.reserve(10u);
  ASSERT_EQ(10u, str.capacity());
}

TEST(UnicodeString, EqualityOperator)
{
  {  // Reflexivity
    const cen::UnicodeString str;
    ASSERT_EQ(str, str);
  }

  {  // Two default constructed strings
    const cen::UnicodeString fst;
    const cen::UnicodeString snd;
    ASSERT_EQ(fst, snd);
    ASSERT_EQ(snd, fst);
  }

  {  // Two equal strings
    const cen::UnicodeString fst{'A', 'B', 'C'};
    const cen::UnicodeString snd{fst};  // NOLINT

    ASSERT_EQ(fst, snd);
    ASSERT_EQ(snd, fst);
  }

  {  // Two different strings
    const cen::UnicodeString fst{'F', 'O', 'O'};
    const cen::UnicodeString snd{'B', 'A', 'R'};

    ASSERT_FALSE(fst == snd);
    ASSERT_FALSE(snd == fst);
  }

  {  // Different size strings
    const cen::UnicodeString fst{'A', 'B'};
    const cen::UnicodeString snd{'A', 'B', 'C'};

    ASSERT_FALSE(fst == snd);
    ASSERT_FALSE(snd == fst);
  }
}

TEST(UnicodeString, InequalityOperator)
{
  {  // Self
    const cen::UnicodeString str;
    ASSERT_FALSE(str != str);
  }

  {  // Two default constructed strings
    const cen::UnicodeString fst;
    const cen::UnicodeString snd;
    ASSERT_FALSE(fst != snd);
    ASSERT_FALSE(snd != fst);
  }

  {  // Two equal strings
    const cen::UnicodeString fst{'A', 'B', 'C'};
    const cen::UnicodeString snd{fst};  // NOLINT

    ASSERT_FALSE(fst != snd);
    ASSERT_FALSE(snd != fst);
  }

  {  // Two different strings
    const cen::UnicodeString fst{'F', 'O', 'O'};
    const cen::UnicodeString snd{'B', 'A', 'R'};

    ASSERT_NE(fst, snd);
    ASSERT_NE(snd, fst);
  }

  {  // Different size strings
    const cen::UnicodeString fst{'A', 'B'};
    const cen::UnicodeString snd{'A', 'B', 'C'};

    ASSERT_NE(fst, snd);
    ASSERT_NE(snd, fst);
  }
}

TEST(UnicodeString, Serialize)
{
  cen::UnicodeString string{'f', 'o', 'o', 'b', 'a', 'r'};
  serialize_save("unicode_string.binary", string);

  const auto other = serialize_create<cen::UnicodeString>("unicode_string.binary");
  ASSERT_EQ(string, other);
}
