#include "filesystem/file.hpp"

#include <gtest/gtest.h>

#include <array>   // array
#include <vector>  // vector

#include "filesystem/paths.hpp"

using namespace cen::literals;

class FileTest : public testing::Test
{
 public:
  inline static const auto prefs = cen::preferred_path("centurion", "tests").copy();
  inline static const auto path = prefs + "file";
};

TEST_F(FileTest, PointerConstructor)
{
  ASSERT_NO_THROW(cen::file{nullptr});
}

TEST_F(FileTest, WriteAndRead)
{
  {
    // Create a file which we will write some data to
    cen::file file{path, cen::file_mode::read_write_replace_binary};
    ASSERT_TRUE(file);

    ASSERT_EQ(4, file.write("abc"));

    int buffer[] = {1, 2, 3};
    ASSERT_EQ(3, file.write(buffer));  // Implicit capture of buffer size
    ASSERT_EQ(1, file.write(buffer, 1));

    std::array array{4, 5, 6};
    ASSERT_EQ(3, file.write(array));

    std::vector vector{7, 8, 9};
    ASSERT_EQ(3, file.write(vector));

    ASSERT_TRUE(file.write_byte(42u));

    ASSERT_TRUE(file.write_as_big_endian(12_u16));
    ASSERT_TRUE(file.write_as_big_endian(34_u32));
    ASSERT_TRUE(file.write_as_big_endian(56_u64));

    ASSERT_TRUE(file.write_as_little_endian(78_u16));
    ASSERT_TRUE(file.write_as_little_endian(90_u32));
    ASSERT_TRUE(file.write_as_little_endian(27_u64));
  }

  {
    cen::file file{path, cen::file_mode::read_existing_binary};
    ASSERT_TRUE(file);

    char str[] = "___";
    ASSERT_EQ(4, file.read_to(str));

    int buffer[] = {0, 0, 0};
    ASSERT_EQ(3, file.read_to(buffer));

    const auto i = file.read<int>();

    std::array array{0, 0, 0};
    ASSERT_EQ(3, file.read_to(array));

    std::vector vector{0, 0, 0};
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
  const cen::file file{path, cen::file_mode::read_existing_binary};
  ASSERT_EQ(SDL_RWtell(file.get()), file.offset());
  ASSERT_EQ(static_cast<cen::file::size_type>(SDL_RWsize(file.get())), file.size());
  ASSERT_EQ(file.get()->type, cen::to_underlying(file.type()));
}

TEST_F(FileTest, IsPNG)
{
  cen::file file{"resources/panda.png", cen::file_mode::read_existing};
  ASSERT_TRUE(file);

  ASSERT_TRUE(file.is_png());
}
