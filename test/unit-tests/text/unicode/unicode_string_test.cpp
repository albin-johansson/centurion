/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "centurion/video/unicode_string.hpp"

#include <gtest/gtest.h>

#include "cereal/types/vector.hpp"
#include "serialization_utils.hpp"

TEST(UnicodeString, Defaults)
{
  const cen::unicode_string str;
  ASSERT_TRUE(str.empty());

  ASSERT_EQ(0u, str.size());
  ASSERT_EQ(0u, str.capacity());

  ASSERT_THROW(str.at(0), cen::exception);
}

TEST(UnicodeString, StringViewConstructor)
{
  using namespace std::string_view_literals;

  const cen::unicode_string str = u"foobar"sv;
  ASSERT_EQ(6u, str.size());
  ASSERT_EQ(6u, str.capacity());

  ASSERT_EQ('f', str.at(0));
  ASSERT_EQ('o', str.at(1));
  ASSERT_EQ('o', str.at(2));
  ASSERT_EQ('b', str.at(3));
  ASSERT_EQ('a', str.at(4));
  ASSERT_EQ('r', str.at(5));

  ASSERT_THROW(str.at(6), cen::exception);
}

TEST(UnicodeString, StringViewConstructorEmpty)
{
  using namespace std::string_view_literals;

  const cen::unicode_string str = u""sv;
  ASSERT_TRUE(str.empty());
  ASSERT_EQ(0u, str.size());
  ASSERT_EQ(0u, str.capacity());

  ASSERT_THROW(str.at(0), cen::exception);
}

TEST(UnicodeString, InitializerListConstructor)
{
  const cen::unicode_string str = {'a', 'b', 'c'};
  ASSERT_EQ(3u, str.size());
  ASSERT_FALSE(str.empty());

  ASSERT_EQ('a', str.at(0));
  ASSERT_EQ('b', str.at(1));
  ASSERT_EQ('c', str.at(2));
  ASSERT_THROW(str.at(3), cen::exception);

  ASSERT_EQ('a', str[0]);
  ASSERT_EQ('b', str[1]);
  ASSERT_EQ('c', str[2]);

  EXPECT_EQ(3, str.end() - str.begin());

  const auto* raw = str.data();
  while (*raw != '\0') {
    ++raw;
  }
  ASSERT_EQ(3u, raw - str.data());
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
}

TEST(UnicodeString, Append)
{
  cen::unicode_string str;

  str.append('A');
  ASSERT_EQ(1u, str.size());
  ASSERT_EQ('A', str.at(0));

  str.append(0xF308);
  ASSERT_EQ(2u, str.size());
  ASSERT_EQ(0xF308, str.at(1));
}

TEST(UnicodeString, AppendVariadic)
{
  cen::unicode_string str;

  str.append('B', 'A', 'R');
  ASSERT_EQ(3u, str.size());
  ASSERT_EQ('B', str.at(0));
  ASSERT_EQ('A', str.at(1));
  ASSERT_EQ('R', str.at(2));
}

TEST(UnicodeString, AdditionAssignmentOperator)
{
  cen::unicode_string str;

  str += 'Z';
  ASSERT_EQ(1u, str.size());
  ASSERT_EQ('Z', str.at(0));

  str += 'Q';
  ASSERT_EQ(2u, str.size());
  ASSERT_EQ('Q', str.at(1));
}

TEST(UnicodeString, PopBack)
{
  cen::unicode_string str;
  ASSERT_TRUE(str.empty());

  str += 'A';
  ASSERT_FALSE(str.empty());
  ASSERT_EQ(1u, str.size());

  str.pop_back();
  ASSERT_TRUE(str.empty());
  ASSERT_THROW(str.at(0), cen::exception);

  ASSERT_NO_THROW(str.pop_back());
  ASSERT_NO_THROW(str.pop_back());
  ASSERT_NO_THROW(str.pop_back());

  ASSERT_TRUE(str.empty());
}

TEST(UnicodeString, At)
{
  cen::unicode_string str;

  ASSERT_THROW(str.at(0u), cen::exception);

  str += 'T';

  ASSERT_EQ('T', str.at(0u));
  ASSERT_EQ('T', str[0u]);

  ASSERT_THROW(str.at(1u), cen::exception);
}

TEST(UnicodeString, SubscriptOperator)
{
  const cen::unicode_string str = {'f', 'o', 'o', 'b', 'a', 'r'};
  ASSERT_EQ('f', str[0u]);
  ASSERT_EQ('o', str[1u]);
  ASSERT_EQ('o', str[2u]);
  ASSERT_EQ('b', str[3u]);
  ASSERT_EQ('a', str[4u]);
  ASSERT_EQ('r', str[5u]);
}

TEST(UnicodeString, Data)
{
  cen::unicode_string str;
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
  cen::unicode_string str;
  ASSERT_TRUE(str.empty());

  str += 'A';
  ASSERT_FALSE(str.empty());
}

TEST(UnicodeString, Reserve)
{
  cen::unicode_string str;
  ASSERT_EQ(0u, str.capacity());

  str.reserve(5u);
  ASSERT_EQ(5u, str.capacity());

  str.append('a', 'b', 'c', 'd', 'e');
  ASSERT_EQ(5u, str.size());
  ASSERT_EQ(5u, str.capacity());

  str += 'f';
  ASSERT_EQ(6u, str.size());
  ASSERT_LT(5u, str.capacity());
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
    const cen::unicode_string fst {'A', 'B', 'C'};
    const cen::unicode_string snd {fst};  // NOLINT

    ASSERT_EQ(fst, snd);
    ASSERT_EQ(snd, fst);
  }

  {  // Two different strings
    const cen::unicode_string fst {'F', 'O', 'O'};
    const cen::unicode_string snd {'B', 'A', 'R'};

    ASSERT_FALSE(fst == snd);
    ASSERT_FALSE(snd == fst);
  }

  {  // Different size strings
    const cen::unicode_string fst {'A', 'B'};
    const cen::unicode_string snd {'A', 'B', 'C'};

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
    const cen::unicode_string fst {'A', 'B', 'C'};
    const cen::unicode_string snd {fst};  // NOLINT

    ASSERT_FALSE(fst != snd);
    ASSERT_FALSE(snd != fst);
  }

  {  // Two different strings
    const cen::unicode_string fst {'F', 'O', 'O'};
    const cen::unicode_string snd {'B', 'A', 'R'};

    ASSERT_NE(fst, snd);
    ASSERT_NE(snd, fst);
  }

  {  // Different size strings
    const cen::unicode_string fst {'A', 'B'};
    const cen::unicode_string snd {'A', 'B', 'C'};

    ASSERT_NE(fst, snd);
    ASSERT_NE(snd, fst);
  }
}

TEST(UnicodeString, Serialize)
{
  cen::unicode_string string {'f', 'o', 'o', 'b', 'a', 'r'};
  serialize_save("unicode_string.binary", string);

  const auto other = serialize_create<cen::unicode_string>("unicode_string.binary");
  ASSERT_EQ(string, other);
}
