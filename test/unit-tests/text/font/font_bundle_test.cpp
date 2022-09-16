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

#include <gtest/gtest.h>

#include "centurion/font.hpp"

TEST(FontBundle, Usage)
{
  cen::experimental::font_bundle bundle;

  ASSERT_THROW(bundle.load_font("foo", 12), cen::ttf_error);

  const auto a = bundle.load_font("resources/daniel.ttf", 12);
  ASSERT_EQ(1, bundle.font_count());
  ASSERT_EQ(1, bundle.pool_count());

  const auto b = bundle.load_font("resources/daniel.ttf", 16);
  ASSERT_EQ(2, bundle.font_count());
  ASSERT_EQ(1, bundle.pool_count());

  ASSERT_EQ(a, b);
  ASSERT_TRUE(bundle.contains("resources/daniel.ttf"));
  ASSERT_TRUE(bundle.contains(a));

  ASSERT_FALSE(bundle.contains(a, 11));
  ASSERT_TRUE(bundle.contains(a, 12));
  ASSERT_FALSE(bundle.contains(a, 13));

  ASSERT_FALSE(bundle.contains(a, 15));
  ASSERT_TRUE(bundle.contains(a, 16));
  ASSERT_FALSE(bundle.contains(a, 17));

  const auto c = bundle.load_font("resources/type_writer.ttf", 9);
  ASSERT_EQ(3, bundle.font_count());
  ASSERT_EQ(2, bundle.pool_count());

  ASSERT_NE(a, c);
  ASSERT_TRUE(bundle.contains(c));
  ASSERT_TRUE(bundle.contains("resources/type_writer.ttf"));

  ASSERT_STREQ("Daniel", bundle.get_font(a, 12).family_name());
  ASSERT_THROW(bundle.at(a, 11), cen::exception);
  ASSERT_THROW(bundle.at(a, 13), cen::exception);
  ASSERT_THROW(bundle.at(c + 1, 9), cen::exception);

  ASSERT_STREQ("Type Writer", bundle.get_font(c, 9).family_name());
  ASSERT_THROW(bundle.at(c, 8), cen::exception);
  ASSERT_THROW(bundle.at(c, 10), cen::exception);
}

TEST(FontBundle, ToString)
{
  cen::experimental::font_bundle bundle;
  bundle.load_font("resources/daniel.ttf", 12);
  bundle.load_font("resources/daniel.ttf", 16);
  ASSERT_EQ("font_bundle(#pools: 1, #fonts: 2)", to_string(bundle));
}