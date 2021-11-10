#include "core/version.hpp"

#include <gtest/gtest.h>

TEST(Version, CurrentVersion)
{
  ASSERT_EQ(6, CENTURION_VERSION_MAJOR);
  ASSERT_EQ(4, CENTURION_VERSION_MINOR);
  ASSERT_EQ(0, CENTURION_VERSION_PATCH);
}

TEST(Version, VersionAtLeast)
{
  ASSERT_FALSE(cen::version_at_least(6, CENTURION_VERSION_MINOR + 1, 0));
  ASSERT_FALSE(cen::version_at_least(6, CENTURION_VERSION_MINOR, CENTURION_VERSION_PATCH + 1));

  ASSERT_TRUE(cen::version_at_least(CENTURION_VERSION_MAJOR,
                                    CENTURION_VERSION_MINOR,
                                    CENTURION_VERSION_PATCH));
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

TEST(Version, DefaultConstructedVersion)
{
  const cen::version version;
  ASSERT_EQ(CENTURION_VERSION_MAJOR, version.major);
  ASSERT_EQ(CENTURION_VERSION_MINOR, version.minor);
  ASSERT_EQ(CENTURION_VERSION_PATCH, version.patch);
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
  constexpr auto version = cen::sdl_version();
  ASSERT_EQ(SDL_MAJOR_VERSION, version.major);
  ASSERT_EQ(SDL_MINOR_VERSION, version.minor);
  ASSERT_EQ(SDL_PATCHLEVEL, version.patch);
}

TEST(Version, SDLImageVersion)
{
  constexpr auto version = cen::sdl_image_version();
  ASSERT_EQ(SDL_IMAGE_MAJOR_VERSION, version.major);
  ASSERT_EQ(SDL_IMAGE_MINOR_VERSION, version.minor);
  ASSERT_EQ(SDL_IMAGE_PATCHLEVEL, version.patch);
}

TEST(Version, SDLMixerVersion)
{
  constexpr auto version = cen::sdl_mixer_version();
  ASSERT_EQ(SDL_MIXER_MAJOR_VERSION, version.major);
  ASSERT_EQ(SDL_MIXER_MINOR_VERSION, version.minor);
  ASSERT_EQ(SDL_MIXER_PATCHLEVEL, version.patch);
}

TEST(Version, SDLTTFVersion)
{
  constexpr auto version = cen::sdl_ttf_version();
  ASSERT_EQ(SDL_TTF_MAJOR_VERSION, version.major);
  ASSERT_EQ(SDL_TTF_MINOR_VERSION, version.minor);
  ASSERT_EQ(SDL_TTF_PATCHLEVEL, version.patch);
}
