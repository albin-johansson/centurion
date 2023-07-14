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

#include <gtest/gtest.h>

#include <centurion/common/version.hpp>

static_assert(CEN_VERSION_NUMBER == SDL_VERSIONNUM(8, 0, 0));
static_assert(CEN_VERSION_AT_LEAST(CEN_VERSION_MAJOR, CEN_VERSION_MINOR, CEN_VERSION_PATCH));
static_assert(cen::Version::of_centurion().as_number() == CEN_VERSION_NUMBER);
static_assert(cen::Version::of_compiled_sdl().as_number() == SDL_COMPILEDVERSION);

TEST(Version, OfCenturion)
{
  const auto version = cen::Version::of_centurion();
  EXPECT_EQ(version.major, CEN_VERSION_MAJOR);
  EXPECT_EQ(version.minor, CEN_VERSION_MINOR);
  EXPECT_EQ(version.patch, CEN_VERSION_PATCH);
}

TEST(Version, OfCompiledSDL)
{
  const auto version = cen::Version::of_compiled_sdl();
  EXPECT_EQ(version.major, SDL_MAJOR_VERSION);
  EXPECT_EQ(version.minor, SDL_MINOR_VERSION);
  EXPECT_EQ(version.patch, SDL_PATCHLEVEL);
}

TEST(Version, OfLinkedSDL)
{
  SDL_version expected_version = {};
  ASSERT_EQ(SDL_GetVersion(&expected_version), 0);

  const auto version = cen::Version::of_linked_sdl();
  EXPECT_EQ(version.major, expected_version.major);
  EXPECT_EQ(version.minor, expected_version.minor);
  EXPECT_EQ(version.patch, expected_version.patch);
}

#if CEN_USE_SDL_IMAGE

TEST(Version, OfCompiledSDLImage)
{
  const auto version = cen::Version::of_compiled_sdl_image();
  EXPECT_EQ(version.major, SDL_IMAGE_MAJOR_VERSION);
  EXPECT_EQ(version.minor, SDL_IMAGE_MINOR_VERSION);
  EXPECT_EQ(version.patch, SDL_IMAGE_PATCHLEVEL);
}

TEST(Version, OfLinkedSDLImage)
{
  const auto* expected_version = IMG_Linked_Version();
  ASSERT_NE(expected_version, nullptr);

  const auto version = cen::Version::of_linked_sdl_image();
  EXPECT_EQ(version.major, expected_version->major);
  EXPECT_EQ(version.minor, expected_version->minor);
  EXPECT_EQ(version.patch, expected_version->patch);
}

#endif  // CEN_USE_SDL_IMAGE

#if CEN_USE_SDL_MIXER

TEST(Version, OfCompiledSDLMixer)
{
  const auto version = cen::Version::of_compiled_sdl_mixer();
  EXPECT_EQ(version.major, SDL_MIXER_MAJOR_VERSION);
  EXPECT_EQ(version.minor, SDL_MIXER_MINOR_VERSION);
  EXPECT_EQ(version.patch, SDL_MIXER_PATCHLEVEL);
}

TEST(Version, OfLinkedSDLMixer)
{
  const auto* expected_version = Mix_Linked_Version();
  ASSERT_NE(expected_version, nullptr);

  const auto version = cen::Version::of_linked_sdl_mixer();
  EXPECT_EQ(version.major, expected_version->major);
  EXPECT_EQ(version.minor, expected_version->minor);
  EXPECT_EQ(version.patch, expected_version->patch);
}

#endif  // CEN_USE_SDL_MIXER

#if CEN_USE_SDL_TTF

TEST(Version, OfCompiledSDLTTF)
{
  const auto version = cen::Version::of_compiled_sdl_ttf();
  EXPECT_EQ(version.major, SDL_TTF_MAJOR_VERSION);
  EXPECT_EQ(version.minor, SDL_TTF_MINOR_VERSION);
  EXPECT_EQ(version.patch, SDL_TTF_PATCHLEVEL);
}

TEST(Version, OfLinkedSDLTTF)
{
  const auto* expected_version = TTF_Linked_Version();
  ASSERT_NE(expected_version, nullptr);

  const auto version = cen::Version::of_linked_sdl_ttf();
  EXPECT_EQ(version.major, expected_version->major);
  EXPECT_EQ(version.minor, expected_version->minor);
  EXPECT_EQ(version.patch, expected_version->patch);
}

#endif  // CEN_USE_SDL_TTF