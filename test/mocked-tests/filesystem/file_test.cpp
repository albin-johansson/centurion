/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
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

#include <fff.h>
#include <gtest/gtest.h>

#include "core_mocks.hpp"

extern "C" {
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

#if SDL_IMAGE_VERSION_ATLEAST(2, 6, 0)
FAKE_VALUE_FUNC(int, IMG_isAVIF, SDL_RWops*)
FAKE_VALUE_FUNC(int, IMG_isJXL, SDL_RWops*)
FAKE_VALUE_FUNC(int, IMG_isQOI, SDL_RWops*)
#endif  // SDL_IMAGE_VERSION_ATLEAST(2, 6, 0)
}

class FileTest : public testing::Test {
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

#if SDL_IMAGE_VERSION_ATLEAST(2, 6, 0)
    RESET_FAKE(IMG_isAVIF)
    RESET_FAKE(IMG_isJXL)
    RESET_FAKE(IMG_isQOI)
#endif  // SDL_IMAGE_VERSION_ATLEAST(2, 6, 0)
  }

  cen::file mFile {nullptr};
};

TEST_F(FileTest, IsPNG)
{
  CEN_PREPARE_MOCK_TEST(IMG_isPNG, 0, 1)

  ASSERT_FALSE(mFile.is_png());
  ASSERT_TRUE(mFile.is_png());
  ASSERT_EQ(2u, IMG_isPNG_fake.call_count);
}

TEST_F(FileTest, IsICO)
{
  CEN_PREPARE_MOCK_TEST(IMG_isICO, 0, 1)

  ASSERT_FALSE(mFile.is_ico());
  ASSERT_TRUE(mFile.is_ico());
  ASSERT_EQ(2u, IMG_isICO_fake.call_count);
}

TEST_F(FileTest, IsJPG)
{
  CEN_PREPARE_MOCK_TEST(IMG_isJPG, 0, 1)

  ASSERT_FALSE(mFile.is_jpg());
  ASSERT_TRUE(mFile.is_jpg());
  ASSERT_EQ(2u, IMG_isJPG_fake.call_count);
}

TEST_F(FileTest, IsBMP)
{
  CEN_PREPARE_MOCK_TEST(IMG_isBMP, 0, 1)

  ASSERT_FALSE(mFile.is_bmp());
  ASSERT_TRUE(mFile.is_bmp());
  ASSERT_EQ(2u, IMG_isBMP_fake.call_count);
}

TEST_F(FileTest, IsGIF)
{
  CEN_PREPARE_MOCK_TEST(IMG_isGIF, 0, 1)

  ASSERT_FALSE(mFile.is_gif());
  ASSERT_TRUE(mFile.is_gif());
  ASSERT_EQ(2u, IMG_isGIF_fake.call_count);
}

TEST_F(FileTest, IsSVG)
{
  CEN_PREPARE_MOCK_TEST(IMG_isSVG, 0, 1)

  ASSERT_FALSE(mFile.is_svg());
  ASSERT_TRUE(mFile.is_svg());
  ASSERT_EQ(2u, IMG_isSVG_fake.call_count);
}

TEST_F(FileTest, IsWEBP)
{
  CEN_PREPARE_MOCK_TEST(IMG_isWEBP, 0, 1)

  ASSERT_FALSE(mFile.is_webp());
  ASSERT_TRUE(mFile.is_webp());
  ASSERT_EQ(2u, IMG_isWEBP_fake.call_count);
}

TEST_F(FileTest, IsTIF)
{
  CEN_PREPARE_MOCK_TEST(IMG_isTIF, 0, 1)

  ASSERT_FALSE(mFile.is_tif());
  ASSERT_TRUE(mFile.is_tif());
  ASSERT_EQ(2u, IMG_isTIF_fake.call_count);
}

TEST_F(FileTest, IsPNM)
{
  CEN_PREPARE_MOCK_TEST(IMG_isPNM, 0, 1)

  ASSERT_FALSE(mFile.is_pnm());
  ASSERT_TRUE(mFile.is_pnm());
  ASSERT_EQ(2u, IMG_isPNM_fake.call_count);
}

TEST_F(FileTest, IsPCX)
{
  CEN_PREPARE_MOCK_TEST(IMG_isPCX, 0, 1)

  ASSERT_FALSE(mFile.is_pcx());
  ASSERT_TRUE(mFile.is_pcx());
  ASSERT_EQ(2u, IMG_isPCX_fake.call_count);
}

TEST_F(FileTest, IsLBM)
{
  CEN_PREPARE_MOCK_TEST(IMG_isLBM, 0, 1)

  ASSERT_FALSE(mFile.is_lbm());
  ASSERT_TRUE(mFile.is_lbm());
  ASSERT_EQ(2u, IMG_isLBM_fake.call_count);
}

TEST_F(FileTest, IsCUR)
{
  CEN_PREPARE_MOCK_TEST(IMG_isCUR, 0, 1)

  ASSERT_FALSE(mFile.is_cur());
  ASSERT_TRUE(mFile.is_cur());
  ASSERT_EQ(2u, IMG_isCUR_fake.call_count);
}

TEST_F(FileTest, IsXCF)
{
  CEN_PREPARE_MOCK_TEST(IMG_isXCF, 0, 1)

  ASSERT_FALSE(mFile.is_xcf());
  ASSERT_TRUE(mFile.is_xcf());
  ASSERT_EQ(2u, IMG_isXCF_fake.call_count);
}

TEST_F(FileTest, IsXPM)
{
  CEN_PREPARE_MOCK_TEST(IMG_isXPM, 0, 1)

  ASSERT_FALSE(mFile.is_xpm());
  ASSERT_TRUE(mFile.is_xpm());
  ASSERT_EQ(2u, IMG_isXPM_fake.call_count);
}

TEST_F(FileTest, IsXV)
{
  CEN_PREPARE_MOCK_TEST(IMG_isXV, 0, 1)

  ASSERT_FALSE(mFile.is_xv());
  ASSERT_TRUE(mFile.is_xv());
  ASSERT_EQ(2u, IMG_isXV_fake.call_count);
}

#if SDL_IMAGE_VERSION_ATLEAST(2, 6, 0)

TEST_F(FileTest, IsAVIF)
{
  CEN_PREPARE_MOCK_TEST(IMG_isAVIF, 0, 1)

  ASSERT_FALSE(mFile.is_avif());
  ASSERT_TRUE(mFile.is_avif());

  ASSERT_EQ(2u, IMG_isAVIF_fake.call_count);
}

TEST_F(FileTest, IsJXL)
{
  CEN_PREPARE_MOCK_TEST(IMG_isJXL, 0, 1)

  ASSERT_FALSE(mFile.is_jxl());
  ASSERT_TRUE(mFile.is_jxl());

  ASSERT_EQ(2u, IMG_isJXL_fake.call_count);
}

TEST_F(FileTest, IsQOI)
{
  CEN_PREPARE_MOCK_TEST(IMG_isQOI, 0, 1)

  ASSERT_FALSE(mFile.is_qoi());
  ASSERT_TRUE(mFile.is_qoi());

  ASSERT_EQ(2u, IMG_isQOI_fake.call_count);
}

#endif  // SDL_IMAGE_VERSION_ATLEAST(2, 6, 0)