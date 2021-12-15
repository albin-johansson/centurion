#include <fff.h>
#include <gtest/gtest.h>

#include "core_mocks.hpp"
#include "video.hpp"

extern "C"
{
  FAKE_VALUE_FUNC(SDL_BlendMode,
                  SDL_ComposeCustomBlendMode,
                  SDL_BlendFactor,
                  SDL_BlendFactor,
                  SDL_BlendOperation,
                  SDL_BlendFactor,
                  SDL_BlendFactor,
                  SDL_BlendOperation);
}

class BlendModeTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_ComposeCustomBlendMode)
  }
};

TEST_F(BlendModeTest, ComposeBlendMode)
{
  const cen::BlendTask color = {cen::BlendFactor::SrcColor,
                                 cen::BlendFactor::DstColor,
                                 cen::BlendOp::Add};
  const cen::BlendTask alpha = {cen::BlendFactor::SrcAlpha,
                                 cen::BlendFactor::OneMinusDstAlpha,
                                 cen::BlendOp::Sub};
  const auto mode = cen::compose_blend_mode(color, alpha);

  ASSERT_EQ(1u, SDL_ComposeCustomBlendMode_fake.call_count);

  ASSERT_EQ(SDL_BLENDFACTOR_SRC_COLOR, SDL_ComposeCustomBlendMode_fake.arg0_val);
  ASSERT_EQ(SDL_BLENDFACTOR_DST_COLOR, SDL_ComposeCustomBlendMode_fake.arg1_val);
  ASSERT_EQ(SDL_BLENDOPERATION_ADD, SDL_ComposeCustomBlendMode_fake.arg2_val);

  ASSERT_EQ(SDL_BLENDFACTOR_SRC_ALPHA, SDL_ComposeCustomBlendMode_fake.arg3_val);
  ASSERT_EQ(SDL_BLENDFACTOR_ONE_MINUS_DST_ALPHA, SDL_ComposeCustomBlendMode_fake.arg4_val);
  ASSERT_EQ(SDL_BLENDOPERATION_SUBTRACT, SDL_ComposeCustomBlendMode_fake.arg5_val);
}
