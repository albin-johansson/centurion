#include "filesystem/file.hpp"

#include <gtest/gtest.h>

#include <array>   // array
#include <vector>  // vector

#include "filesystem/pref_path.hpp"

using namespace cen::literals;

class FileTest : public testing::Test
{
 public:
  inline static const auto prefs =
      cen::get_pref_path("centurion", "tests").copy();
  inline static const auto path = prefs + "file";
};

TEST_F(FileTest, PointerConstructor)
{
  EXPECT_NO_THROW(cen::file{nullptr});
}

TEST_F(FileTest, WriteAndRead)
{
  {
    // Create a file which we will write some data to
    cen::file file{path, cen::file_mode::read_write_replace_binary};
    ASSERT_TRUE(file);

    EXPECT_EQ(4, file.write("abc"));

    int buffer[] = {1, 2, 3};
    EXPECT_EQ(3, file.write(buffer));  // Implicit capture of buffer size
    EXPECT_EQ(1, file.write(buffer, 1));

    std::array array{4, 5, 6};
    EXPECT_EQ(3, file.write(array));

    std::vector vector{7, 8, 9};
    EXPECT_EQ(3, file.write(vector));

    EXPECT_TRUE(file.write_byte(42u));

    EXPECT_TRUE(file.write_as_big_endian(12_u16));
    EXPECT_TRUE(file.write_as_big_endian(34_u32));
    EXPECT_TRUE(file.write_as_big_endian(56_u64));

    EXPECT_TRUE(file.write_as_little_endian(78_u16));
    EXPECT_TRUE(file.write_as_little_endian(90_u32));
    EXPECT_TRUE(file.write_as_little_endian(27_u64));
  }

  {
    cen::file file{path, cen::file_mode::read_existing_binary};
    ASSERT_TRUE(file);

    char str[] = "___";
    EXPECT_EQ(4, file.read_to(str));

    int buffer[] = {0, 0, 0};
    EXPECT_EQ(3, file.read_to(buffer));

    const auto i = file.read<int>();

    std::array array{0, 0, 0};
    EXPECT_EQ(3, file.read_to(array));

    std::vector vector{0, 0, 0};
    EXPECT_EQ(3, file.read_to(vector));

    EXPECT_STREQ("abc", str);

    EXPECT_EQ(1, buffer[0]);
    EXPECT_EQ(2, buffer[1]);
    EXPECT_EQ(3, buffer[2]);

    EXPECT_EQ(1, i);

    EXPECT_EQ(4, array.at(0));
    EXPECT_EQ(5, array.at(1));
    EXPECT_EQ(6, array.at(2));

    EXPECT_EQ(7, vector.at(0));
    EXPECT_EQ(8, vector.at(1));
    EXPECT_EQ(9, vector.at(2));

    EXPECT_EQ(42u, file.read_byte());

    EXPECT_EQ(12u, file.read_big_endian_u16());
    EXPECT_EQ(34u, file.read_big_endian_u32());
    EXPECT_EQ(56u, file.read_big_endian_u64());

    EXPECT_EQ(78u, file.read_little_endian_u16());
    EXPECT_EQ(90u, file.read_little_endian_u32());
    EXPECT_EQ(27u, file.read_little_endian_u64());
  }
}

TEST_F(FileTest, Queries)
{
  const cen::file file{path, cen::file_mode::read_existing_binary};
  EXPECT_EQ(SDL_RWtell(file.get()), file.offset());
  EXPECT_EQ(SDL_RWsize(file.get()), file.size());
  EXPECT_EQ(file.get()->type, static_cast<cen::u32>(file.type()));
}

TEST_F(FileTest, SeekModeEnum)
{
  EXPECT_EQ(RW_SEEK_SET, static_cast<int>(cen::seek_mode::from_beginning));
  EXPECT_EQ(RW_SEEK_CUR, static_cast<int>(cen::seek_mode::relative_to_current));
  EXPECT_EQ(RW_SEEK_END, static_cast<int>(cen::seek_mode::relative_to_end));
}

TEST_F(FileTest, FileTypeEnum)
{
  EXPECT_EQ(SDL_RWOPS_UNKNOWN, static_cast<int>(cen::file_type::unknown));
  EXPECT_EQ(SDL_RWOPS_WINFILE, static_cast<int>(cen::file_type::win32));
  EXPECT_EQ(SDL_RWOPS_STDFILE, static_cast<int>(cen::file_type::stdio));
  EXPECT_EQ(SDL_RWOPS_JNIFILE, static_cast<int>(cen::file_type::jni));
  EXPECT_EQ(SDL_RWOPS_MEMORY, static_cast<int>(cen::file_type::memory));
  EXPECT_EQ(SDL_RWOPS_MEMORY_RO, static_cast<int>(cen::file_type::memory_ro));
}