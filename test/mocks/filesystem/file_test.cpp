#include "filesystem/file.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core_mocks.hpp"

extern "C"
{
  FAKE_VALUE_FUNC(int, SDL_RWclose, SDL_RWops*)
  FAKE_VALUE_FUNC(int, IMG_isPNG, SDL_RWops*)
  FAKE_VALUE_FUNC(int, IMG_isICO, SDL_RWops*)
  FAKE_VALUE_FUNC(int, IMG_isJPG, SDL_RWops*)
  FAKE_VALUE_FUNC(int, IMG_isBMP, SDL_RWops*)
  FAKE_VALUE_FUNC(int, IMG_isGIF, SDL_RWops*)
  FAKE_VALUE_FUNC(int, IMG_isSVG, SDL_RWops*)
  FAKE_VALUE_FUNC(int, IMG_isWEBP, SDL_RWops*)
  FAKE_VALUE_FUNC(int, IMG_isTIF, SDL_RWops*)
  FAKE_VALUE_FUNC(int, IMG_isPNM, SDL_RWops*)
  FAKE_VALUE_FUNC(int, IMG_isPCX, SDL_RWops*)
  FAKE_VALUE_FUNC(int, IMG_isLBM, SDL_RWops*)
  FAKE_VALUE_FUNC(int, IMG_isCUR, SDL_RWops*)
  FAKE_VALUE_FUNC(int, IMG_isXCF, SDL_RWops*)
  FAKE_VALUE_FUNC(int, IMG_isXPM, SDL_RWops*)
  FAKE_VALUE_FUNC(int, IMG_isXV, SDL_RWops*)
}

class FileTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_RWclose)
    RESET_FAKE(IMG_isPNG)
    RESET_FAKE(IMG_isICO)
    RESET_FAKE(IMG_isJPG)
    RESET_FAKE(IMG_isBMP)
    RESET_FAKE(IMG_isGIF)
    RESET_FAKE(IMG_isSVG)
    RESET_FAKE(IMG_isWEBP)
    RESET_FAKE(IMG_isTIF)
    RESET_FAKE(IMG_isPNM)
    RESET_FAKE(IMG_isPCX)
    RESET_FAKE(IMG_isLBM)
    RESET_FAKE(IMG_isCUR)
    RESET_FAKE(IMG_isXCF)
    RESET_FAKE(IMG_isXPM)
    RESET_FAKE(IMG_isXV)
  }

  cen::File file{nullptr};
};

TEST_F(FileTest, IsPNG)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(IMG_isPNG, values.data(), cen::isize(values));

  ASSERT_FALSE(file.IsPNG());
  ASSERT_TRUE(file.IsPNG());
  ASSERT_EQ(2u, IMG_isPNG_fake.call_count);
}

TEST_F(FileTest, IsICO)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(IMG_isICO, values.data(), cen::isize(values));

  ASSERT_FALSE(file.IsICO());
  ASSERT_TRUE(file.IsICO());
  ASSERT_EQ(2u, IMG_isICO_fake.call_count);
}

TEST_F(FileTest, IsJPG)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(IMG_isJPG, values.data(), cen::isize(values));

  ASSERT_FALSE(file.IsJPG());
  ASSERT_TRUE(file.IsJPG());
  ASSERT_EQ(2u, IMG_isJPG_fake.call_count);
}

TEST_F(FileTest, IsBMP)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(IMG_isBMP, values.data(), cen::isize(values));

  ASSERT_FALSE(file.IsBMP());
  ASSERT_TRUE(file.IsBMP());
  ASSERT_EQ(2u, IMG_isBMP_fake.call_count);
}

TEST_F(FileTest, IsGIF)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(IMG_isGIF, values.data(), cen::isize(values));

  ASSERT_FALSE(file.IsGIF());
  ASSERT_TRUE(file.IsGIF());
  ASSERT_EQ(2u, IMG_isGIF_fake.call_count);
}

TEST_F(FileTest, IsSVG)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(IMG_isSVG, values.data(), cen::isize(values));

  ASSERT_FALSE(file.IsSVG());
  ASSERT_TRUE(file.IsSVG());
  ASSERT_EQ(2u, IMG_isSVG_fake.call_count);
}

TEST_F(FileTest, IsWEBP)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(IMG_isWEBP, values.data(), cen::isize(values));

  ASSERT_FALSE(file.IsWEBP());
  ASSERT_TRUE(file.IsWEBP());
  ASSERT_EQ(2u, IMG_isWEBP_fake.call_count);
}

TEST_F(FileTest, IsTIF)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(IMG_isTIF, values.data(), cen::isize(values));

  ASSERT_FALSE(file.IsTIF());
  ASSERT_TRUE(file.IsTIF());
  ASSERT_EQ(2u, IMG_isTIF_fake.call_count);
}

TEST_F(FileTest, IsPNM)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(IMG_isPNM, values.data(), cen::isize(values));

  ASSERT_FALSE(file.IsPNM());
  ASSERT_TRUE(file.IsPNM());
  ASSERT_EQ(2u, IMG_isPNM_fake.call_count);
}

TEST_F(FileTest, IsPCX)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(IMG_isPCX, values.data(), cen::isize(values));

  ASSERT_FALSE(file.IsPCX());
  ASSERT_TRUE(file.IsPCX());
  ASSERT_EQ(2u, IMG_isPCX_fake.call_count);
}

TEST_F(FileTest, IsLBM)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(IMG_isLBM, values.data(), cen::isize(values));

  ASSERT_FALSE(file.IsLBM());
  ASSERT_TRUE(file.IsLBM());
  ASSERT_EQ(2u, IMG_isLBM_fake.call_count);
}

TEST_F(FileTest, IsCUR)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(IMG_isCUR, values.data(), cen::isize(values));

  ASSERT_FALSE(file.IsCUR());
  ASSERT_TRUE(file.IsCUR());
  ASSERT_EQ(2u, IMG_isCUR_fake.call_count);
}

TEST_F(FileTest, IsXCF)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(IMG_isXCF, values.data(), cen::isize(values));

  ASSERT_FALSE(file.IsXCF());
  ASSERT_TRUE(file.IsXCF());
  ASSERT_EQ(2u, IMG_isXCF_fake.call_count);
}

TEST_F(FileTest, IsXPM)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(IMG_isXPM, values.data(), cen::isize(values));

  ASSERT_FALSE(file.IsXPM());
  ASSERT_TRUE(file.IsXPM());
  ASSERT_EQ(2u, IMG_isXPM_fake.call_count);
}

TEST_F(FileTest, IsXV)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(IMG_isXV, values.data(), cen::isize(values));

  ASSERT_FALSE(file.IsXV());
  ASSERT_TRUE(file.IsXV());
  ASSERT_EQ(2u, IMG_isXV_fake.call_count);
}
