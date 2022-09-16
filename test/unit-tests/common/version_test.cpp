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

#include "centurion/version.hpp"

#include <gtest/gtest.h>

TEST(Version, CurrentVersion)
{
  ASSERT_EQ(7, CENTURION_VERSION_MAJOR);
  ASSERT_EQ(3, CENTURION_VERSION_MINOR);
  ASSERT_EQ(0, CENTURION_VERSION_PATCH);

  const auto version = cen::current_version();
  ASSERT_EQ(7, version.major);
  ASSERT_EQ(3, version.minor);
  ASSERT_EQ(0, version.patch);
}

TEST(Version, VersionAtLeast)
{
  ASSERT_FALSE(cen::version_at_least(CENTURION_VERSION_MAJOR, CENTURION_VERSION_MINOR + 1, 0));
  ASSERT_FALSE(cen::version_at_least(CENTURION_VERSION_MAJOR,
                                     CENTURION_VERSION_MINOR,
                                     CENTURION_VERSION_PATCH + 1));

  ASSERT_TRUE(cen::version_at_least(CENTURION_VERSION_MAJOR,
                                    CENTURION_VERSION_MINOR,
                                    CENTURION_VERSION_PATCH));
  ASSERT_TRUE(cen::version_at_least(7, 2, 0));
  ASSERT_TRUE(cen::version_at_least(7, 1, 0));
  ASSERT_TRUE(cen::version_at_least(7, 0, 0));
  ASSERT_TRUE(cen::version_at_least(6, 3, 1));
  ASSERT_TRUE(cen::version_at_least(6, 3, 0));
  ASSERT_TRUE(cen::version_at_least(6, 2, 0));
  ASSERT_TRUE(cen::version_at_least(6, 1, 0));
  ASSERT_TRUE(cen::version_at_least(6, 0, 1));
  ASSERT_TRUE(cen::version_at_least(6, 0, 0));
  ASSERT_TRUE(cen::version_at_least(5, 3, 0));
  ASSERT_TRUE(cen::version_at_least(5, 2, 0));
  ASSERT_TRUE(cen::version_at_least(5, 1, 0));
  ASSERT_TRUE(cen::version_at_least(5, 0, 0));
  ASSERT_TRUE(cen::version_at_least(4, 0, 0));
}

TEST(Version, Defaults)
{
  const cen::version version;
  ASSERT_EQ(0, version.major);
  ASSERT_EQ(0, version.minor);
  ASSERT_EQ(0, version.patch);
}

TEST(Version, SDLLinkedVersion)
{
  SDL_version expected{};
  SDL_GetVersion(&expected);

  const auto version = cen::sdl_linked_version();
  ASSERT_EQ(expected.major, version.major);
  ASSERT_EQ(expected.minor, version.minor);
  ASSERT_EQ(expected.patch, version.patch);
}

TEST(Version, SDLImageLinkedVersion)
{
  const auto expected = *IMG_Linked_Version();
  const auto version = cen::sdl_image_linked_version();
  ASSERT_EQ(expected.major, version.major);
  ASSERT_EQ(expected.minor, version.minor);
  ASSERT_EQ(expected.patch, version.patch);
}

TEST(Version, SDLMixerLinkedVersion)
{
  const auto expected = *Mix_Linked_Version();
  const auto version = cen::sdl_mixer_linked_version();
  ASSERT_EQ(expected.major, version.major);
  ASSERT_EQ(expected.minor, version.minor);
  ASSERT_EQ(expected.patch, version.patch);
}

TEST(Version, SDLTTFLinkedVersion)
{
  const auto expected = *TTF_Linked_Version();
  const auto version = cen::sdl_ttf_linked_version();
  ASSERT_EQ(expected.major, version.major);
  ASSERT_EQ(expected.minor, version.minor);
  ASSERT_EQ(expected.patch, version.patch);
}

TEST(Version, SDLVersion)
{
  const auto version = cen::sdl_version();
  ASSERT_EQ(SDL_MAJOR_VERSION, version.major);
  ASSERT_EQ(SDL_MINOR_VERSION, version.minor);
  ASSERT_EQ(SDL_PATCHLEVEL, version.patch);
}

TEST(Version, SDLImageVersion)
{
  const auto version = cen::sdl_image_version();
  ASSERT_EQ(SDL_IMAGE_MAJOR_VERSION, version.major);
  ASSERT_EQ(SDL_IMAGE_MINOR_VERSION, version.minor);
  ASSERT_EQ(SDL_IMAGE_PATCHLEVEL, version.patch);
}

TEST(Version, SDLMixerVersion)
{
  const auto version = cen::sdl_mixer_version();
  ASSERT_EQ(SDL_MIXER_MAJOR_VERSION, version.major);
  ASSERT_EQ(SDL_MIXER_MINOR_VERSION, version.minor);
  ASSERT_EQ(SDL_MIXER_PATCHLEVEL, version.patch);
}

TEST(Version, SDLTTFVersion)
{
  const auto version = cen::sdl_ttf_version();
  ASSERT_EQ(SDL_TTF_MAJOR_VERSION, version.major);
  ASSERT_EQ(SDL_TTF_MINOR_VERSION, version.minor);
  ASSERT_EQ(SDL_TTF_PATCHLEVEL, version.patch);
}
