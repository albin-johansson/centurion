#include "centurion.hpp"

#include <gtest/gtest.h>

#include "core_mocks.hpp"

class CenturionTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    // Sets up expected return values for OK initialization
    constexpr cen::config cfg;
    SDL_Init_fake.return_val = cfg.coreFlags;
    TTF_Init_fake.return_val = 0;
    IMG_Init_fake.return_val = cfg.imageFlags;
    Mix_Init_fake.return_val = cfg.mixerFlags;
    Mix_OpenAudio_fake.return_val = 0;
    SDL_GetError_fake.return_val = "foo";
  }
};

TEST_F(CenturionTest, NoFailure)
{
  try {
    const cen::library library;

    EXPECT_EQ(1, SDL_Init_fake.call_count);
    EXPECT_EQ(1, TTF_Init_fake.call_count);
    EXPECT_EQ(1, IMG_Init_fake.call_count);
    EXPECT_EQ(1, Mix_Init_fake.call_count);
  } catch (...) {
    FAIL();
  }
}

TEST_F(CenturionTest, SDLCoreInitFailure)
{
  SDL_Init_fake.return_val = -1;
  EXPECT_THROW(cen::library{}, cen::sdl_error);
}

TEST_F(CenturionTest, SDLTTFInitFailure)
{
  TTF_Init_fake.return_val = -1;
  EXPECT_THROW(cen::library{}, cen::ttf_error);
}

TEST_F(CenturionTest, SDLImageInitFailure)
{
  IMG_Init_fake.return_val = 0;
  EXPECT_THROW(cen::library{}, cen::img_error);
}

TEST_F(CenturionTest, SDLMixInitFailure)
{
  Mix_Init_fake.return_val = 0;
  EXPECT_THROW(cen::library{}, cen::mix_error);
}

TEST_F(CenturionTest, SDLMixOpenFailure)
{
  Mix_OpenAudio_fake.return_val = -1;
  EXPECT_THROW(cen::library{}, cen::mix_error);
}
