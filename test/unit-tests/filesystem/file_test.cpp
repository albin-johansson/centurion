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

#include "centurion/io/file.hpp"

#include <gtest/gtest.h>

#include <array>    // array
#include <cstddef>  // size_t
#include <vector>   // vector

#include "centurion/io/paths.hpp"

class FileTest : public testing::Test {
 public:
  inline static const auto prefs = cen::preferred_path("centurion", "tests").copy();
  inline static const auto path = prefs + "file";
};

TEST_F(FileTest, PointerConstructor)
{
  ASSERT_NO_THROW(cen::file {nullptr});
}

TEST_F(FileTest, WriteAndRead)
{
  {
    // Create a file which we will write some data to
    cen::file file {path, cen::file_mode::wbx};
    ASSERT_TRUE(file);

    ASSERT_EQ(4, file.write("abc"));

    int buffer[] = {1, 2, 3};
    ASSERT_EQ(3, file.write(buffer));  // Implicit capture of buffer size
    ASSERT_EQ(1, file.write(buffer, 1));

    std::array array {4, 5, 6};
    ASSERT_EQ(3, file.write(array));

    std::vector vector {7, 8, 9};
    ASSERT_EQ(3, file.write(vector));

    ASSERT_TRUE(file.write_byte(42u));

    ASSERT_TRUE(file.write_native_as_big_endian(Uint16 {12}));
    ASSERT_TRUE(file.write_native_as_big_endian(Uint32 {34}));
    ASSERT_TRUE(file.write_native_as_big_endian(Uint64 {56}));

    ASSERT_TRUE(file.write_native_as_little_endian(Uint16 {78}));
    ASSERT_TRUE(file.write_native_as_little_endian(Uint32 {90}));
    ASSERT_TRUE(file.write_native_as_little_endian(Uint64 {27}));
  }

  {
    cen::file file {path, cen::file_mode::rb};
    ASSERT_TRUE(file);

    char str[] = "___";
    ASSERT_EQ(4, file.read_to(str));

    int buffer[] = {0, 0, 0};
    ASSERT_EQ(3, file.read_to(buffer));

    const auto i = file.read<int>();

    std::array array {0, 0, 0};
    ASSERT_EQ(3, file.read_to(array));

    std::vector vector {0, 0, 0};
    ASSERT_EQ(3, file.read_to(vector));

    ASSERT_STREQ("abc", str);

    ASSERT_EQ(1, buffer[0]);
    ASSERT_EQ(2, buffer[1]);
    ASSERT_EQ(3, buffer[2]);

    ASSERT_EQ(1, i);

    ASSERT_EQ(4, array.at(0));
    ASSERT_EQ(5, array.at(1));
    ASSERT_EQ(6, array.at(2));

    ASSERT_EQ(7, vector.at(0));
    ASSERT_EQ(8, vector.at(1));
    ASSERT_EQ(9, vector.at(2));

    ASSERT_EQ(42u, file.read_byte());

    ASSERT_EQ(12u, file.read_big_endian_u16());
    ASSERT_EQ(34u, file.read_big_endian_u32());
    ASSERT_EQ(56u, file.read_big_endian_u64());

    ASSERT_EQ(78u, file.read_little_endian_u16());
    ASSERT_EQ(90u, file.read_little_endian_u32());
    ASSERT_EQ(27u, file.read_little_endian_u64());
  }
}

TEST_F(FileTest, Queries)
{
  const cen::file file {path, cen::file_mode::rb};
  ASSERT_EQ(SDL_RWtell(file.data()), file.offset());
  ASSERT_EQ(static_cast<std::size_t>(SDL_RWsize(file.data())), file.size());
  ASSERT_EQ(file.data()->type, cen::to_underlying(file.type()));
}

TEST_F(FileTest, IsPNG)
{
  cen::file file {"resources/panda.png", cen::file_mode::r};
  ASSERT_TRUE(file);

  ASSERT_TRUE(file.is_png());
}
