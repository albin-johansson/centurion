// Copyright (C) 2019-2024 Albin Johansson (MIT License)

#include "centurion/core/version.hpp"

#include <gtest/gtest.h>

namespace cen::test {

static_assert(CENTURION_VERSION_MAJOR == 8);
static_assert(CENTURION_VERSION_MINOR == 0);
static_assert(CENTURION_VERSION_PATCH == 0);

static_assert(CENTURION_VERSION_NUMBER == 8'000);

TEST(Version, MakeVersionNumberMacro)
{
  EXPECT_EQ(CENTURION_MAKE_VERSION_NUMBER(1, 2, 3), 1'203);
}

TEST(Version, SdlVersionIsMacro)
{
  const auto ver = sdl_header_version();
  EXPECT_TRUE(CENTURION_SDL_VERSION_IS(ver.major, ver.minor, ver.patch));

  EXPECT_FALSE(CENTURION_SDL_VERSION_IS(ver.major, ver.minor, ver.patch + 1));
  EXPECT_FALSE(CENTURION_SDL_VERSION_IS(ver.major, ver.minor, ver.patch - 1));

  EXPECT_FALSE(CENTURION_SDL_VERSION_IS(ver.major, ver.minor + 1, ver.patch));
  EXPECT_FALSE(CENTURION_SDL_VERSION_IS(ver.major, ver.minor - 1, ver.patch));

  EXPECT_FALSE(CENTURION_SDL_VERSION_IS(ver.major + 1, ver.minor, ver.patch));
  EXPECT_FALSE(CENTURION_SDL_VERSION_IS(ver.major - 1, ver.minor, ver.patch));
}

// cen::version::current
TEST(Version, Current)
{
  const auto curr_version = version::current();
  EXPECT_EQ(curr_version.major, CENTURION_VERSION_MAJOR);
  EXPECT_EQ(curr_version.minor, CENTURION_VERSION_MINOR);
  EXPECT_EQ(curr_version.patch, CENTURION_VERSION_PATCH);
}

// cen::version::at_least
TEST(Version, AtLeast)
{
  EXPECT_TRUE(version::at_least(1, 0, 0));
  EXPECT_TRUE(version::at_least(1, 2, 3));
  EXPECT_TRUE(version::at_least(7, 9, 9));
  EXPECT_TRUE(version::at_least(CENTURION_VERSION_MAJOR,
                                CENTURION_VERSION_MINOR,
                                CENTURION_VERSION_PATCH));

  EXPECT_FALSE(version::at_least(CENTURION_VERSION_MAJOR + 1,
                                 CENTURION_VERSION_MINOR,
                                 CENTURION_VERSION_PATCH));
  EXPECT_FALSE(version::at_least(CENTURION_VERSION_MAJOR,
                                 CENTURION_VERSION_MINOR + 1,
                                 CENTURION_VERSION_PATCH));
  EXPECT_FALSE(version::at_least(CENTURION_VERSION_MAJOR,
                                 CENTURION_VERSION_MINOR,
                                 CENTURION_VERSION_PATCH + 1));
}

// cen::sdl_header_version
TEST(Version, SDLHeaderVersion)
{
  const auto sdl_ver = sdl_header_version();
  EXPECT_EQ(sdl_ver.major, SDL_MAJOR_VERSION);
  EXPECT_EQ(sdl_ver.minor, SDL_MINOR_VERSION);
  EXPECT_EQ(sdl_ver.patch, SDL_MICRO_VERSION);
}

// cen::sdl_linked_version
TEST(Version, SDLLinkedVersion)
{
  const auto sdl_ver = sdl_linked_version();
  EXPECT_EQ(sdl_ver.major, SDL_VERSIONNUM_MAJOR(SDL_GetVersion()));
  EXPECT_EQ(sdl_ver.minor, SDL_VERSIONNUM_MINOR(SDL_GetVersion()));
  EXPECT_EQ(sdl_ver.patch, SDL_VERSIONNUM_MICRO(SDL_GetVersion()));
}

#ifndef CENTURION_NO_SDL_IMAGE

// cen::img_header_version
TEST(Version, IMGHeaderVersion)
{
  const auto img_ver = img_header_version();
  EXPECT_EQ(img_ver.major, SDL_IMAGE_MAJOR_VERSION);
  EXPECT_EQ(img_ver.minor, SDL_IMAGE_MINOR_VERSION);
  EXPECT_EQ(img_ver.patch, SDL_IMAGE_MICRO_VERSION);
}

// cen::img_linked_version
TEST(Version, IMGLinkedVersion)
{
  const auto img_ver = img_linked_version();
  EXPECT_EQ(img_ver.major, SDL_VERSIONNUM_MAJOR(IMG_Version()));
  EXPECT_EQ(img_ver.minor, SDL_VERSIONNUM_MINOR(IMG_Version()));
  EXPECT_EQ(img_ver.patch, SDL_VERSIONNUM_MICRO(IMG_Version()));
}

#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER

// cen::mix_header_version
TEST(Version, MIXHeaderVersion)
{
  const auto mix_ver = img_header_version();
  EXPECT_EQ(mix_ver.major, SDL_MIXER_MAJOR_VERSION);
  EXPECT_EQ(mix_ver.minor, SDL_MIXER_MINOR_VERSION);
  EXPECT_EQ(mix_ver.patch, SDL_MIXER_MICRO_VERSION);
}

// cen::mix_linked_version
TEST(Version, MIXLinkedVersion)
{
  const auto mix_ver = img_linked_version();
  EXPECT_EQ(mix_ver.major, SDL_VERSIONNUM_MAJOR(Mix_Version()));
  EXPECT_EQ(mix_ver.minor, SDL_VERSIONNUM_MINOR(Mix_Version()));
  EXPECT_EQ(mix_ver.patch, SDL_VERSIONNUM_MICRO(Mix_Version()));
}

#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF

// cen::ttf_header_version
TEST(Version, TTFHeaderVersion)
{
  const auto ttf_ver = ttf_header_version();
  EXPECT_EQ(ttf_ver.major, SDL_TTF_MAJOR_VERSION);
  EXPECT_EQ(ttf_ver.minor, SDL_TTF_MINOR_VERSION);
  EXPECT_EQ(ttf_ver.patch, SDL_TTF_MICRO_VERSION);
}

// cen::ttf_linked_version
TEST(Version, TTFLinkedVersion)
{
  const auto ttf_ver = ttf_linked_version();
  EXPECT_EQ(ttf_ver.major, SDL_VERSIONNUM_MAJOR(TTF_Version()));
  EXPECT_EQ(ttf_ver.minor, SDL_VERSIONNUM_MINOR(TTF_Version()));
  EXPECT_EQ(ttf_ver.patch, SDL_VERSIONNUM_MICRO(TTF_Version()));
}

#endif  // CENTURION_NO_SDL_TTF

}  // namespace cen::test
