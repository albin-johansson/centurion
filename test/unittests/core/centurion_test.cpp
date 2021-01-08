#include "centurion.hpp"

#include <gtest/gtest.h>

TEST(CenturionHeader, SdlVersion)
{
  constexpr auto version = cen::sdl_version();
  EXPECT_EQ(SDL_MAJOR_VERSION, version.major);
  EXPECT_EQ(SDL_MINOR_VERSION, version.minor);
  EXPECT_EQ(SDL_PATCHLEVEL, version.patch);
}

TEST(CenturionHeader, SdlImageVersion)
{
  constexpr auto version = cen::sdl_image_version();
  EXPECT_EQ(SDL_IMAGE_MAJOR_VERSION, version.major);
  EXPECT_EQ(SDL_IMAGE_MINOR_VERSION, version.minor);
  EXPECT_EQ(SDL_IMAGE_PATCHLEVEL, version.patch);
}

TEST(CenturionHeader, SdlMixerVersion)
{
  constexpr auto version = cen::sdl_mixer_version();
  EXPECT_EQ(SDL_MIXER_MAJOR_VERSION, version.major);
  EXPECT_EQ(SDL_MIXER_MINOR_VERSION, version.minor);
  EXPECT_EQ(SDL_MIXER_PATCHLEVEL, version.patch);
}

TEST(CenturionHeader, SdlTtfVersion)
{
  constexpr auto version = cen::ttf_version();
  EXPECT_EQ(SDL_TTF_MAJOR_VERSION, version.major);
  EXPECT_EQ(SDL_TTF_MINOR_VERSION, version.minor);
  EXPECT_EQ(SDL_TTF_PATCHLEVEL, version.patch);
}
