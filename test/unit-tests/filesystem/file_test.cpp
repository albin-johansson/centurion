#include "filesystem/file.hpp"

#include <gtest/gtest.h>

#include <array>    // array
#include <cstddef>  // size_t
#include <vector>   // vector

#include "filesystem/paths.hpp"

using namespace cen::literals;

class FileTest : public testing::Test {
 public:
  inline static const auto prefs = cen::preferred_path("centurion", "tests").copy();
  inline static const auto path = prefs + "file";
};

TEST_F(FileTest, PointerConstructor)
{
  ASSERT_NO_THROW(cen::File{nullptr});
}

TEST_F(FileTest, WriteAndRead)
{
  {
    // Create a file which we will write some data to
    cen::File file{path, cen::FileMode::ReadWriteReplaceBinary};
    ASSERT_TRUE(file);

    ASSERT_EQ(4, file.Write("abc"));

    int buffer[] = {1, 2, 3};
    ASSERT_EQ(3, file.Write(buffer));  // Implicit capture of buffer size
    ASSERT_EQ(1, file.Write(buffer, 1));

    std::array array{4, 5, 6};
    ASSERT_EQ(3, file.Write(array));

    std::vector vector{7, 8, 9};
    ASSERT_EQ(3, file.Write(vector));

    ASSERT_TRUE(file.WriteByte(42u));

    ASSERT_TRUE(file.WriteNativeAsBigEndian(12_u16));
    ASSERT_TRUE(file.WriteNativeAsBigEndian(34_u32));
    ASSERT_TRUE(file.WriteNativeAsBigEndian(56_u64));

    ASSERT_TRUE(file.WriteNativeAsLittleEndian(78_u16));
    ASSERT_TRUE(file.WriteNativeAsLittleEndian(90_u32));
    ASSERT_TRUE(file.WriteNativeAsLittleEndian(27_u64));
  }

  {
    cen::File file{path, cen::FileMode::ReadExistingBinary};
    ASSERT_TRUE(file);

    char str[] = "___";
    ASSERT_EQ(4, file.ReadTo(str));

    int buffer[] = {0, 0, 0};
    ASSERT_EQ(3, file.ReadTo(buffer));

    const auto i = file.Read<int>();

    std::array array{0, 0, 0};
    ASSERT_EQ(3, file.ReadTo(array));

    std::vector vector{0, 0, 0};
    ASSERT_EQ(3, file.ReadTo(vector));

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

    ASSERT_EQ(42u, file.ReadByte());

    ASSERT_EQ(12u, file.ReadBigEndianU16());
    ASSERT_EQ(34u, file.ReadBigEndianU32());
    ASSERT_EQ(56u, file.ReadBigEndianU64());

    ASSERT_EQ(78u, file.ReadLittleEndianU16());
    ASSERT_EQ(90u, file.ReadLittleEndianU32());
    ASSERT_EQ(27u, file.ReadLittleEndianU64());
  }
}

TEST_F(FileTest, Queries)
{
  const cen::File file{path, cen::FileMode::ReadExistingBinary};
  ASSERT_EQ(SDL_RWtell(file.get()), file.GetOffset());
  ASSERT_EQ(static_cast<std::size_t>(SDL_RWsize(file.get())), file.GetSize());
  ASSERT_EQ(file.get()->type, cen::ToUnderlying(file.GetType()));
}

TEST_F(FileTest, IsPNG)
{
  cen::File file{"resources/panda.png", cen::FileMode::ReadExisting};
  ASSERT_TRUE(file);

  ASSERT_TRUE(file.IsPNG());
}
