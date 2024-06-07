// Copyright (C) 2019-2024 Albin Johansson (MIT License)

#include "centurion/io/iostream.hpp"

#include <bit>
#include <fstream>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace cen::test {

class IOStreamTest : public testing::Test
{
 public:
  static void SetUpTestSuite()
  {
    std::ofstream file {"assets/foobar.txt", std::ios::out | std::ios::trunc};
    file << "foobar";
  }
};

// cen::iostream::from_file
// cen::iostream::read
TEST_F(IOStreamTest, FromFile)
{
  auto stream = iostream::from_file("assets/foobar.txt", "r");
  ASSERT_TRUE(stream.has_value());

  char buffer[6] {};
  EXPECT_EQ(stream->read(buffer, sizeof buffer), 6);
  EXPECT_EQ(stream->tell(), 6);
  EXPECT_EQ(stream->status(), SDL_IO_STATUS_READY);

  EXPECT_EQ(stream->read(buffer, sizeof buffer), 0);
  EXPECT_EQ(stream->tell(), 6);
  EXPECT_EQ(stream->status(), SDL_IO_STATUS_EOF);

  EXPECT_EQ(buffer[0], 'f');
  EXPECT_EQ(buffer[1], 'o');
  EXPECT_EQ(buffer[2], 'o');
  EXPECT_EQ(buffer[3], 'b');
  EXPECT_EQ(buffer[4], 'a');
  EXPECT_EQ(buffer[5], 'r');
}

// cen::iostream::from_memory
// cen::iostream::write
TEST_F(IOStreamTest, FromMemory)
{
  char backing_buffer[256] = {};

  auto stream = iostream::from_memory(backing_buffer, sizeof backing_buffer);
  ASSERT_TRUE(stream.has_value());

  const char data[] = "abc";
  EXPECT_EQ(stream->write(data, sizeof data), 4);
  EXPECT_EQ(stream->tell(), 4);

  EXPECT_EQ(backing_buffer[0], 'a');
  EXPECT_EQ(backing_buffer[1], 'b');
  EXPECT_EQ(backing_buffer[2], 'c');
  EXPECT_EQ(backing_buffer[3], '\0');
}

// cen::iostream::from_const_memory
TEST_F(IOStreamTest, FromConstMemory)
{
  const std::uint8_t data[] = {1, 2, 3, 4, 5, 6};

  auto stream = iostream::from_const_memory(data, sizeof data);
  ASSERT_TRUE(stream.has_value());

  EXPECT_EQ(stream->write_u8(0xFF), result::failure);
  EXPECT_EQ(stream->size(), 6);

  EXPECT_EQ(stream->read_u8(), 1);
  EXPECT_EQ(stream->read_u8(), 2);
  EXPECT_EQ(stream->read_u8(), 3);
  EXPECT_EQ(stream->read_u8(), 4);
  EXPECT_EQ(stream->read_u8(), 5);
  EXPECT_EQ(stream->read_u8(), 6);
}

// cen::iostream::from_dynamic_memory
TEST_F(IOStreamTest, FromDynamicMemory)
{
  auto stream = iostream::from_dynamic_memory();
  ASSERT_TRUE(stream.has_value());

  const char original_data[] = {'1', '2', '3'};
  EXPECT_EQ(stream->write(original_data, sizeof original_data), 3);
  EXPECT_EQ(stream->tell(), 3);
  EXPECT_EQ(stream->status(), SDL_IO_STATUS_READY);

  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->tell(), 0);
  EXPECT_EQ(stream->status(), SDL_IO_STATUS_READY);

  char read_data[3] = {};
  EXPECT_EQ(stream->read(read_data, sizeof read_data), 3);
  EXPECT_EQ(stream->tell(), 3);
  EXPECT_EQ(stream->status(), SDL_IO_STATUS_READY);

  EXPECT_THAT(read_data, testing::ContainerEq(original_data));
}

// cen::iostream_base::seek
// cen::iostream_base::tell
TEST_F(IOStreamTest, Seek)
{
  auto stream = iostream::from_dynamic_memory();
  ASSERT_TRUE(stream.has_value());

  EXPECT_EQ(stream->tell(), 0);
  EXPECT_EQ(stream->write_u8(1), result::success);
  EXPECT_EQ(stream->write_u8(2), result::success);
  EXPECT_EQ(stream->write_u8(3), result::success);
  EXPECT_EQ(stream->tell(), 3);

  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->tell(), 0);
  EXPECT_EQ(stream->read_u8(), 1);

  EXPECT_EQ(stream->seek(seek_mode::start, 1), 1);
  EXPECT_EQ(stream->tell(), 1);
  EXPECT_EQ(stream->read_u8(), 2);

  EXPECT_EQ(stream->seek(seek_mode::end), 3);
  EXPECT_EQ(stream->tell(), 3);
  EXPECT_EQ(stream->read_u8(), std::nullopt);

  EXPECT_EQ(stream->seek(seek_mode::end, -1), 2);
  EXPECT_EQ(stream->tell(), 2);
  EXPECT_EQ(stream->read_u8(), 3);

  EXPECT_EQ(stream->seek(seek_mode::current, -2), 1);
  EXPECT_EQ(stream->tell(), 1);
  EXPECT_EQ(stream->read_u8(), 2);
}

// cen::iostream_base::write
TEST_F(IOStreamTest, Write)
{
  auto stream = iostream::from_file("assets/iostream_write.txt", "w+");
  ASSERT_TRUE(stream.has_value());

  const char data[] = "This is a test of the write function";
  EXPECT_EQ(stream->write(data, sizeof data), sizeof data);
  EXPECT_EQ(stream->status(), SDL_IO_STATUS_READY);
}

// cen::iostream_base::write_u8
// cen::iostream_base::read_u8
TEST_F(IOStreamTest, WriteReadU8)
{
  auto stream = iostream::from_dynamic_memory();
  ASSERT_TRUE(stream.has_value());

  EXPECT_EQ(stream->write_u8(0xF1), result::success);
  EXPECT_EQ(stream->status(), SDL_IO_STATUS_READY);
  EXPECT_EQ(stream->size(), 1);

  EXPECT_EQ(stream->seek(seek_mode::start), 0);

  EXPECT_EQ(stream->read_u8(), 0xF1);
  EXPECT_EQ(stream->status(), SDL_IO_STATUS_READY);
  EXPECT_EQ(stream->size(), 1);
}

// cen::iostream_base::write_u16_le
// cen::iostream_base::read_u16_le
TEST_F(IOStreamTest, WriteReadU16LE)
{
  auto stream = iostream::from_dynamic_memory();
  ASSERT_TRUE(stream.has_value());

  EXPECT_EQ(stream->write_u16_le(0xDEAD), result::success);
  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->read_u16_le(), 0xDEAD);

  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->read_u8(), 0xAD);
  EXPECT_EQ(stream->read_u8(), 0xDE);
}

// cen::iostream_base::write_u16_be
// cen::iostream_base::read_u16_be
TEST_F(IOStreamTest, WriteReadU16BE)
{
  auto stream = iostream::from_dynamic_memory();
  ASSERT_TRUE(stream.has_value());

  EXPECT_EQ(stream->write_u16_be(0xDEAD), result::success);
  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->read_u16_be(), 0xDEAD);

  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->read_u8(), 0xDE);
  EXPECT_EQ(stream->read_u8(), 0xAD);
}

// cen::iostream_base::write_s16_le
// cen::iostream_base::read_s16_le
TEST_F(IOStreamTest, WriteReadS16LE)
{
  auto stream = iostream::from_dynamic_memory();
  ASSERT_TRUE(stream.has_value());

  EXPECT_EQ(stream->write_s16_le(0x1234), result::success);
  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->read_s16_le(), 0x1234);

  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->read_u8(), 0x34);
  EXPECT_EQ(stream->read_u8(), 0x12);
}

// cen::iostream_base::write_s16_be
// cen::iostream_base::read_s16_be
TEST_F(IOStreamTest, WriteReadS16BE)
{
  auto stream = iostream::from_dynamic_memory();
  ASSERT_TRUE(stream.has_value());

  EXPECT_EQ(stream->write_s16_be(0x1234), result::success);
  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->read_s16_be(), 0x1234);

  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->read_u8(), 0x12);
  EXPECT_EQ(stream->read_u8(), 0x34);
}

// cen::iostream_base::write_u32_le
// cen::iostream_base::read_u32_le
TEST_F(IOStreamTest, WriteReadU32LE)
{
  auto stream = iostream::from_dynamic_memory();
  ASSERT_TRUE(stream.has_value());

  EXPECT_EQ(stream->write_u32_le(0xDEADBEEF), result::success);
  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->read_u32_le(), 0xDEADBEEF);

  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->read_u8(), 0xEF);
  EXPECT_EQ(stream->read_u8(), 0xBE);
  EXPECT_EQ(stream->read_u8(), 0xAD);
  EXPECT_EQ(stream->read_u8(), 0xDE);
}

// cen::iostream_base::write_u32_be
// cen::iostream_base::read_u32_be
TEST_F(IOStreamTest, WriteReadU32BE)
{
  auto stream = iostream::from_dynamic_memory();
  ASSERT_TRUE(stream.has_value());

  EXPECT_EQ(stream->write_u32_be(0xDEADBEEF), result::success);
  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->read_u32_be(), 0xDEADBEEF);

  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->read_u8(), 0xDE);
  EXPECT_EQ(stream->read_u8(), 0xAD);
  EXPECT_EQ(stream->read_u8(), 0xBE);
  EXPECT_EQ(stream->read_u8(), 0xEF);
}

// cen::iostream_base::write_s32_le
// cen::iostream_base::read_s32_le
TEST_F(IOStreamTest, WriteReadS32LE)
{
  auto stream = iostream::from_dynamic_memory();
  ASSERT_TRUE(stream.has_value());

  EXPECT_EQ(stream->write_s32_le(0x11223344), result::success);
  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->read_s32_le(), 0x11223344);

  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->read_u8(), 0x44);
  EXPECT_EQ(stream->read_u8(), 0x33);
  EXPECT_EQ(stream->read_u8(), 0x22);
  EXPECT_EQ(stream->read_u8(), 0x11);
}

// cen::iostream_base::write_s32_be
// cen::iostream_base::read_s32_be
TEST_F(IOStreamTest, WriteReadS32BE)
{
  auto stream = iostream::from_dynamic_memory();
  ASSERT_TRUE(stream.has_value());

  EXPECT_EQ(stream->write_s32_be(0x11223344), result::success);
  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->read_s32_be(), 0x11223344);

  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->read_u8(), 0x11);
  EXPECT_EQ(stream->read_u8(), 0x22);
  EXPECT_EQ(stream->read_u8(), 0x33);
  EXPECT_EQ(stream->read_u8(), 0x44);
}

// cen::iostream_base::write_u64_le
// cen::iostream_base::read_u64_le
TEST_F(IOStreamTest, WriteReadU64LE)
{
  auto stream = iostream::from_dynamic_memory();
  ASSERT_TRUE(stream.has_value());

  EXPECT_EQ(stream->write_u64_le(0x1122334455667788), result::success);
  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->read_u64_le(), 0x1122334455667788);

  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->read_u8(), 0x88);
  EXPECT_EQ(stream->read_u8(), 0x77);
  EXPECT_EQ(stream->read_u8(), 0x66);
  EXPECT_EQ(stream->read_u8(), 0x55);
  EXPECT_EQ(stream->read_u8(), 0x44);
  EXPECT_EQ(stream->read_u8(), 0x33);
  EXPECT_EQ(stream->read_u8(), 0x22);
  EXPECT_EQ(stream->read_u8(), 0x11);
}

// cen::iostream_base::write_u64_be
// cen::iostream_base::read_u64_be
TEST_F(IOStreamTest, WriteReadU64BE)
{
  auto stream = iostream::from_dynamic_memory();
  ASSERT_TRUE(stream.has_value());

  EXPECT_EQ(stream->write_u64_be(0x1122334455667788), result::success);
  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->read_u64_be(), 0x1122334455667788);

  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->read_u8(), 0x11);
  EXPECT_EQ(stream->read_u8(), 0x22);
  EXPECT_EQ(stream->read_u8(), 0x33);
  EXPECT_EQ(stream->read_u8(), 0x44);
  EXPECT_EQ(stream->read_u8(), 0x55);
  EXPECT_EQ(stream->read_u8(), 0x66);
  EXPECT_EQ(stream->read_u8(), 0x77);
  EXPECT_EQ(stream->read_u8(), 0x88);
}

// cen::iostream_base::write_s64_le
// cen::iostream_base::read_s64_le
TEST_F(IOStreamTest, WriteReadS64LE)
{
  auto stream = iostream::from_dynamic_memory();
  ASSERT_TRUE(stream.has_value());

  EXPECT_EQ(stream->write_s64_le(0x1122334455667788), result::success);
  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->read_s64_le(), 0x1122334455667788);

  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->read_u8(), 0x88);
  EXPECT_EQ(stream->read_u8(), 0x77);
  EXPECT_EQ(stream->read_u8(), 0x66);
  EXPECT_EQ(stream->read_u8(), 0x55);
  EXPECT_EQ(stream->read_u8(), 0x44);
  EXPECT_EQ(stream->read_u8(), 0x33);
  EXPECT_EQ(stream->read_u8(), 0x22);
  EXPECT_EQ(stream->read_u8(), 0x11);
}

// cen::iostream_base::write_s64_be
// cen::iostream_base::read_s64_be
TEST_F(IOStreamTest, WriteReadS64BE)
{
  auto stream = iostream::from_dynamic_memory();
  ASSERT_TRUE(stream.has_value());

  EXPECT_EQ(stream->write_s64_be(0x1122334455667788), result::success);
  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->read_s64_be(), 0x1122334455667788);

  EXPECT_EQ(stream->seek(seek_mode::start), 0);
  EXPECT_EQ(stream->read_u8(), 0x11);
  EXPECT_EQ(stream->read_u8(), 0x22);
  EXPECT_EQ(stream->read_u8(), 0x33);
  EXPECT_EQ(stream->read_u8(), 0x44);
  EXPECT_EQ(stream->read_u8(), 0x55);
  EXPECT_EQ(stream->read_u8(), 0x66);
  EXPECT_EQ(stream->read_u8(), 0x77);
  EXPECT_EQ(stream->read_u8(), 0x88);
}

// cen::iostream_base::get_properties
TEST_F(IOStreamTest, GetProperties)
{
  auto stream = iostream::from_dynamic_memory();
  ASSERT_TRUE(stream.has_value());

  const auto id = stream->get_properties();
  EXPECT_TRUE(id.has_value());
}

// cen::load_file(const char*)
TEST_F(IOStreamTest, LoadFile)
{
  const auto content = load_file("assets/foobar.txt");
  ASSERT_TRUE(content.has_value());

  EXPECT_NE(content->data, nullptr);
  EXPECT_EQ(content->size, 6);
}

// cen::load_file(iostream_ref)
TEST_F(IOStreamTest, LoadFileFromIOStream)
{
  auto stream = iostream::from_file("assets/foobar.txt", "r");
  ASSERT_TRUE(stream.has_value());

  const auto content = load_file(*stream);
  ASSERT_TRUE(content.has_value());

  EXPECT_NE(content->data, nullptr);
  EXPECT_EQ(content->size, 6);
}

}  // namespace cen::test
