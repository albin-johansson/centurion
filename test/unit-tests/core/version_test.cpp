#include "version.hpp"

#include <gtest/gtest.h>

TEST(Version, CurrentVersion)
{
  ASSERT_EQ(7, CENTURION_VERSION_MAJOR);
  ASSERT_EQ(0, CENTURION_VERSION_MINOR);
  ASSERT_EQ(0, CENTURION_VERSION_PATCH);
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
  ASSERT_TRUE(cen::version_at_least(6, 4, 0));
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
  const cen::Version version;
  ASSERT_EQ(CENTURION_VERSION_MAJOR, version.major);
  ASSERT_EQ(CENTURION_VERSION_MINOR, version.minor);
  ASSERT_EQ(CENTURION_VERSION_PATCH, version.patch);
}

TEST(Version, GetLinkedSDLVersion)
{
  SDL_version expected{};
  SDL_GetVersion(&expected);

  const auto version = cen::GetLinkedSDLVersion();
  ASSERT_EQ(expected.major, version.major);
  ASSERT_EQ(expected.minor, version.minor);
  ASSERT_EQ(expected.patch, version.patch);
}

TEST(Version, GetLinkedIMGVersion)
{
  const auto expected = *IMG_Linked_Version();
  const auto version = cen::GetLinkedIMGVersion();
  ASSERT_EQ(expected.major, version.major);
  ASSERT_EQ(expected.minor, version.minor);
  ASSERT_EQ(expected.patch, version.patch);
}

TEST(Version, GetLinkedMixVersion)
{
  const auto expected = *Mix_Linked_Version();
  const auto version = cen::GetLinkedMixVersion();
  ASSERT_EQ(expected.major, version.major);
  ASSERT_EQ(expected.minor, version.minor);
  ASSERT_EQ(expected.patch, version.patch);
}

TEST(Version, GetLinkedTTFVersion)
{
  const auto expected = *TTF_Linked_Version();
  const auto version = cen::GetLinkedTTFVersion();
  ASSERT_EQ(expected.major, version.major);
  ASSERT_EQ(expected.minor, version.minor);
  ASSERT_EQ(expected.patch, version.patch);
}

TEST(Version, GetCurrentSDLVersion)
{
  constexpr auto version = cen::GetCurrentSDLVersion();
  ASSERT_EQ(SDL_MAJOR_VERSION, version.major);
  ASSERT_EQ(SDL_MINOR_VERSION, version.minor);
  ASSERT_EQ(SDL_PATCHLEVEL, version.patch);
}

TEST(Version, GetCurrentIMGVersion)
{
  constexpr auto version = cen::GetCurrentIMGVersion();
  ASSERT_EQ(SDL_IMAGE_MAJOR_VERSION, version.major);
  ASSERT_EQ(SDL_IMAGE_MINOR_VERSION, version.minor);
  ASSERT_EQ(SDL_IMAGE_PATCHLEVEL, version.patch);
}

TEST(Version, GetCurrentMixVersion)
{
  constexpr auto version = cen::GetCurrentMixVersion();
  ASSERT_EQ(SDL_MIXER_MAJOR_VERSION, version.major);
  ASSERT_EQ(SDL_MIXER_MINOR_VERSION, version.minor);
  ASSERT_EQ(SDL_MIXER_PATCHLEVEL, version.patch);
}

TEST(Version, GetCurrentTTFVersion)
{
  constexpr auto version = cen::GetCurrentTTFVersion();
  ASSERT_EQ(SDL_TTF_MAJOR_VERSION, version.major);
  ASSERT_EQ(SDL_TTF_MINOR_VERSION, version.minor);
  ASSERT_EQ(SDL_TTF_PATCHLEVEL, version.patch);
}
