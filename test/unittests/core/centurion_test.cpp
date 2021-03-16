#include <gtest/gtest.h>

#include "library.hpp"

TEST(CenturionHeader, SDLLinkedVersion)
{
  SDL_version expected{};
  SDL_GetVersion(&expected);

  const auto version = cen::sdl_linked_version();
  EXPECT_EQ(expected.major, version.major);
  EXPECT_EQ(expected.minor, version.minor);
  EXPECT_EQ(expected.patch, version.patch);
}

TEST(CenturionHeader, SDLVersion)
{
  constexpr auto version = cen::sdl_version();
  EXPECT_EQ(SDL_MAJOR_VERSION, version.major);
  EXPECT_EQ(SDL_MINOR_VERSION, version.minor);
  EXPECT_EQ(SDL_PATCHLEVEL, version.patch);
}

TEST(CenturionHeader, SDLImageVersion)
{
  constexpr auto version = cen::sdl_image_version();
  EXPECT_EQ(SDL_IMAGE_MAJOR_VERSION, version.major);
  EXPECT_EQ(SDL_IMAGE_MINOR_VERSION, version.minor);
  EXPECT_EQ(SDL_IMAGE_PATCHLEVEL, version.patch);
}

TEST(CenturionHeader, SDLMixerVersion)
{
  constexpr auto version = cen::sdl_mixer_version();
  EXPECT_EQ(SDL_MIXER_MAJOR_VERSION, version.major);
  EXPECT_EQ(SDL_MIXER_MINOR_VERSION, version.minor);
  EXPECT_EQ(SDL_MIXER_PATCHLEVEL, version.patch);
}

TEST(CenturionHeader, SDLTTFVersion)
{
  constexpr auto version = cen::sdl_ttf_version();
  EXPECT_EQ(SDL_TTF_MAJOR_VERSION, version.major);
  EXPECT_EQ(SDL_TTF_MINOR_VERSION, version.minor);
  EXPECT_EQ(SDL_TTF_PATCHLEVEL, version.patch);
}
