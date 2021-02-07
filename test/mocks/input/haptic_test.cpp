#include "haptic.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>     // array
#include <iostream>  // cout

#include "core_mocks.hpp"

extern "C" {
// clang-format off
FAKE_VOID_FUNC(SDL_HapticClose, SDL_Haptic*)
FAKE_VOID_FUNC(SDL_HapticDestroyEffect, SDL_Haptic*, int)
FAKE_VALUE_FUNC(SDL_Haptic*, SDL_HapticOpen, int)
FAKE_VALUE_FUNC(SDL_Haptic*, SDL_HapticOpenFromMouse)
FAKE_VALUE_FUNC(SDL_Haptic*, SDL_HapticOpenFromJoystick, SDL_Joystick*)
FAKE_VALUE_FUNC(int, SDL_HapticRumbleInit, SDL_Haptic*)
FAKE_VALUE_FUNC(int, SDL_HapticRumblePlay, SDL_Haptic*, float, Uint32)
FAKE_VALUE_FUNC(int, SDL_HapticRumbleStop, SDL_Haptic*)
FAKE_VALUE_FUNC(int, SDL_HapticRumbleSupported, SDL_Haptic*)
FAKE_VALUE_FUNC(unsigned, SDL_HapticQuery, SDL_Haptic*)
FAKE_VALUE_FUNC(int, SDL_NumHaptics)
FAKE_VALUE_FUNC(int, SDL_HapticIndex, SDL_Haptic*)
FAKE_VALUE_FUNC(int, SDL_MouseIsHaptic)
FAKE_VALUE_FUNC(const char*, SDL_HapticName, int)
FAKE_VALUE_FUNC(int, SDL_HapticOpened, int)
FAKE_VALUE_FUNC(int, SDL_JoystickIsHaptic, SDL_Joystick*)
FAKE_VALUE_FUNC(int, SDL_HapticNumEffects, SDL_Haptic*)
FAKE_VALUE_FUNC(int, SDL_HapticNumEffectsPlaying, SDL_Haptic*)
FAKE_VALUE_FUNC(int, SDL_HapticNumAxes, SDL_Haptic*)
FAKE_VALUE_FUNC(int, SDL_HapticNewEffect, SDL_Haptic*, SDL_HapticEffect*)
FAKE_VALUE_FUNC(int, SDL_HapticRunEffect, SDL_Haptic*, int, Uint32)
FAKE_VALUE_FUNC(int, SDL_HapticStopEffect, SDL_Haptic*, int)
FAKE_VALUE_FUNC(int, SDL_HapticEffectSupported, SDL_Haptic*, SDL_HapticEffect*)
FAKE_VALUE_FUNC(int, SDL_HapticUpdateEffect, SDL_Haptic*, int, SDL_HapticEffect*)
// clang-format on
}

class HapticTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    mocks::reset_core();
    RESET_FAKE(SDL_HapticClose);
    RESET_FAKE(SDL_HapticDestroyEffect);
    RESET_FAKE(SDL_HapticOpen);
    RESET_FAKE(SDL_HapticOpenFromMouse);
    RESET_FAKE(SDL_HapticOpenFromJoystick);
    RESET_FAKE(SDL_HapticRumbleInit);
    RESET_FAKE(SDL_HapticRumblePlay);
    RESET_FAKE(SDL_HapticRumbleStop);
    RESET_FAKE(SDL_HapticRumbleSupported);
    RESET_FAKE(SDL_HapticQuery);
    RESET_FAKE(SDL_NumHaptics);
    RESET_FAKE(SDL_HapticIndex);
    RESET_FAKE(SDL_MouseIsHaptic);
    RESET_FAKE(SDL_HapticName);
    RESET_FAKE(SDL_HapticOpened);
    RESET_FAKE(SDL_JoystickIsHaptic);
    RESET_FAKE(SDL_HapticNumEffects);
    RESET_FAKE(SDL_HapticNumEffectsPlaying);
    RESET_FAKE(SDL_HapticNumAxes);
    RESET_FAKE(SDL_HapticNewEffect);
    RESET_FAKE(SDL_HapticRunEffect);
    RESET_FAKE(SDL_HapticStopEffect);
    RESET_FAKE(SDL_HapticEffectSupported);
    RESET_FAKE(SDL_HapticUpdateEffect);
  }

  cen::haptic_handle m_haptic{nullptr};
};

using namespace cen::literals;

TEST_F(HapticTest, IndexConstructor)
{
  EXPECT_THROW(cen::haptic{}, cen::sdl_error);
  EXPECT_EQ(1, SDL_HapticOpen_fake.call_count);
}

TEST_F(HapticTest, PointerConstructor)
{
  static_assert(!noexcept(cen::haptic{nullptr}));
  EXPECT_THROW(cen::haptic{nullptr}, cen::exception);

  static_assert(noexcept(cen::haptic_handle{nullptr}));
  EXPECT_NO_THROW(cen::haptic_handle{nullptr});
}

TEST_F(HapticTest, FromJoystick)
{
  cen::joystick_handle handle{nullptr};
  EXPECT_THROW(cen::haptic::from_joystick(handle), cen::sdl_error);
  EXPECT_EQ(1, SDL_HapticOpenFromJoystick_fake.call_count);
}

TEST_F(HapticTest, FromMouse)
{
  EXPECT_THROW(cen::haptic::from_mouse(), cen::sdl_error);
  EXPECT_EQ(1, SDL_HapticOpenFromMouse_fake.call_count);
}

TEST_F(HapticTest, InitRumble)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_HapticRumbleInit,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.init_rumble());
  EXPECT_TRUE(m_haptic.init_rumble());

  EXPECT_EQ(2, SDL_HapticRumbleInit_fake.call_count);
}

TEST_F(HapticTest, PlayRumble)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_HapticRumblePlay,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.play_rumble(0.5f, 100_ms));
  EXPECT_TRUE(m_haptic.play_rumble(0.5f, 100_ms));

  EXPECT_EQ(0.5f, SDL_HapticRumblePlay_fake.arg1_val);
  EXPECT_EQ(100, SDL_HapticRumblePlay_fake.arg2_val);
  EXPECT_EQ(2, SDL_HapticRumblePlay_fake.call_count);
}

TEST_F(HapticTest, StopRumble)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_HapticRumbleStop,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.stop_rumble());
  EXPECT_TRUE(m_haptic.stop_rumble());

  EXPECT_EQ(2, SDL_HapticRumbleStop_fake.call_count);
}

TEST_F(HapticTest, IsRumbleSupported)
{
  std::array values{-1, 0, 1};
  SET_RETURN_SEQ(SDL_HapticRumbleSupported,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.is_rumble_supported());
  EXPECT_FALSE(m_haptic.is_rumble_supported());
  EXPECT_TRUE(m_haptic.is_rumble_supported());
  EXPECT_EQ(3, SDL_HapticRumbleSupported_fake.call_count);
}

TEST_F(HapticTest, HasFeatureConstant)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_CONSTANT};
  SET_RETURN_SEQ(SDL_HapticQuery,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.has_feature_constant());
  EXPECT_TRUE(m_haptic.has_feature_constant());

  EXPECT_EQ(2, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureSine)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_SINE};
  SET_RETURN_SEQ(SDL_HapticQuery,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.has_feature_sine());
  EXPECT_TRUE(m_haptic.has_feature_sine());

  EXPECT_EQ(2, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureLeftRight)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_LEFTRIGHT};
  SET_RETURN_SEQ(SDL_HapticQuery,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.has_feature_left_right());
  EXPECT_TRUE(m_haptic.has_feature_left_right());

  EXPECT_EQ(2, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureTriangle)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_TRIANGLE};
  SET_RETURN_SEQ(SDL_HapticQuery,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.has_feature_triangle());
  EXPECT_TRUE(m_haptic.has_feature_triangle());

  EXPECT_EQ(2, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureSawtoothUp)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_SAWTOOTHUP};
  SET_RETURN_SEQ(SDL_HapticQuery,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.has_feature_sawtooth_up());
  EXPECT_TRUE(m_haptic.has_feature_sawtooth_up());

  EXPECT_EQ(2, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureSawtoothDown)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_SAWTOOTHDOWN};
  SET_RETURN_SEQ(SDL_HapticQuery,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.has_feature_sawtooth_down());
  EXPECT_TRUE(m_haptic.has_feature_sawtooth_down());

  EXPECT_EQ(2, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureRamp)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_RAMP};
  SET_RETURN_SEQ(SDL_HapticQuery,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.has_feature_ramp());
  EXPECT_TRUE(m_haptic.has_feature_ramp());

  EXPECT_EQ(2, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureSpring)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_SPRING};
  SET_RETURN_SEQ(SDL_HapticQuery,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.has_feature_spring());
  EXPECT_TRUE(m_haptic.has_feature_spring());

  EXPECT_EQ(2, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureDamper)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_DAMPER};
  SET_RETURN_SEQ(SDL_HapticQuery,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.has_feature_damper());
  EXPECT_TRUE(m_haptic.has_feature_damper());

  EXPECT_EQ(2, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureInertia)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_INERTIA};
  SET_RETURN_SEQ(SDL_HapticQuery,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.has_feature_inertia());
  EXPECT_TRUE(m_haptic.has_feature_inertia());

  EXPECT_EQ(2, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureFriction)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_FRICTION};
  SET_RETURN_SEQ(SDL_HapticQuery,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.has_feature_friction());
  EXPECT_TRUE(m_haptic.has_feature_friction());

  EXPECT_EQ(2, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureGain)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_GAIN};
  SET_RETURN_SEQ(SDL_HapticQuery,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.has_feature_gain());
  EXPECT_TRUE(m_haptic.has_feature_gain());

  EXPECT_EQ(2, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureAutocenter)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_AUTOCENTER};
  SET_RETURN_SEQ(SDL_HapticQuery,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.has_feature_autocenter());
  EXPECT_TRUE(m_haptic.has_feature_autocenter());

  EXPECT_EQ(2, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureStatus)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_STATUS};
  SET_RETURN_SEQ(SDL_HapticQuery,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.has_feature_status());
  EXPECT_TRUE(m_haptic.has_feature_status());

  EXPECT_EQ(2, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeaturePause)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_PAUSE};
  SET_RETURN_SEQ(SDL_HapticQuery,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.has_feature_pause());
  EXPECT_TRUE(m_haptic.has_feature_pause());

  EXPECT_EQ(2, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureCustom)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_CUSTOM};
  SET_RETURN_SEQ(SDL_HapticQuery,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.has_feature_custom());
  EXPECT_TRUE(m_haptic.has_feature_custom());

  EXPECT_EQ(2, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, Index)
{
  std::array values{-1, 1};
  SET_RETURN_SEQ(SDL_HapticIndex,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.index());
  EXPECT_EQ(1, m_haptic.index());

  EXPECT_EQ(2, SDL_HapticIndex_fake.call_count);
}

TEST_F(HapticTest, Name)
{
  std::array values{-1, 1};
  SET_RETURN_SEQ(SDL_HapticIndex,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.name());
  EXPECT_EQ(0, SDL_HapticName_fake.call_count);
  EXPECT_EQ(1, SDL_HapticIndex_fake.call_count);

  const auto name [[maybe_unused]] = m_haptic.name();
  EXPECT_EQ(1, SDL_HapticName_fake.call_count);
  EXPECT_EQ(2, SDL_HapticIndex_fake.call_count);
}

TEST_F(HapticTest, IsOpened)
{
  const auto opened [[maybe_unused]] = cen::haptic::is_opened(0);
  EXPECT_EQ(1, SDL_HapticOpened_fake.call_count);
}

TEST_F(HapticTest, IsJoystickHaptic)
{
  std::array values{-1, 0, 1};
  SET_RETURN_SEQ(SDL_JoystickIsHaptic,
                 values.data(),
                 static_cast<int>(values.size()));

  const cen::joystick_handle joystick{nullptr};

  EXPECT_FALSE(cen::haptic::is_joystick_haptic(joystick));
  EXPECT_FALSE(cen::haptic::is_joystick_haptic(joystick));
  EXPECT_TRUE(cen::haptic::is_joystick_haptic(joystick));

  EXPECT_EQ(3, SDL_JoystickIsHaptic_fake.call_count);
}

TEST_F(HapticTest, EffectCapacity)
{
  std::array values{-1, 7};
  SET_RETURN_SEQ(SDL_HapticNumEffects,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.effect_capacity());
  EXPECT_EQ(7, m_haptic.effect_capacity());

  EXPECT_EQ(2, SDL_HapticNumEffects_fake.call_count);
}

TEST_F(HapticTest, ConcurrentCapacity)
{
  std::array values{-1, 4};
  SET_RETURN_SEQ(SDL_HapticNumEffectsPlaying,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.concurrent_capacity());
  EXPECT_EQ(4, m_haptic.concurrent_capacity());

  EXPECT_EQ(2, SDL_HapticNumEffectsPlaying_fake.call_count);
}

TEST_F(HapticTest, AxisCount)
{
  const auto count [[maybe_unused]] = m_haptic.axis_count();
  EXPECT_EQ(1, SDL_HapticNumAxes_fake.call_count);
}

TEST_F(HapticTest, Count)
{
  const auto count [[maybe_unused]] = cen::haptic::count();
  EXPECT_EQ(1, SDL_NumHaptics_fake.call_count);
}

TEST_F(HapticTest, IsMouseHaptic)
{
  const auto isHaptic [[maybe_unused]] = cen::haptic::is_mouse_haptic();
  EXPECT_EQ(1, SDL_MouseIsHaptic_fake.call_count);
}

TEST_F(HapticTest, Add)
{
  std::array values{-1, 7};
  SET_RETURN_SEQ(SDL_HapticNewEffect,
                 values.data(),
                 static_cast<int>(values.size()));

  cen::haptic_constant effect;
  EXPECT_FALSE(m_haptic.add(effect));
  EXPECT_EQ(7, m_haptic.add(effect));

  EXPECT_EQ(2, SDL_HapticNewEffect_fake.call_count);
}

TEST_F(HapticTest, Update)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_HapticUpdateEffect,
                 values.data(),
                 static_cast<int>(values.size()));

  cen::haptic_constant effect;
  EXPECT_FALSE(m_haptic.update(42, effect));
  EXPECT_TRUE(m_haptic.update(42, effect));

  EXPECT_EQ(2, SDL_HapticUpdateEffect_fake.call_count);
}

TEST_F(HapticTest, Run)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_HapticRunEffect,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.run(42));
  EXPECT_EQ(1, SDL_HapticRunEffect_fake.arg2_val);

  EXPECT_TRUE(m_haptic.run(42, 7));
  EXPECT_EQ(7, SDL_HapticRunEffect_fake.arg2_val);

  EXPECT_EQ(2, SDL_HapticRunEffect_fake.call_count);
}

TEST_F(HapticTest, Stop)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_HapticStopEffect,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_haptic.stop(42));
  EXPECT_TRUE(m_haptic.stop(42));

  EXPECT_EQ(2, SDL_HapticStopEffect_fake.call_count);
}

TEST_F(HapticTest, Destroy)
{
  m_haptic.destroy(12);
  EXPECT_EQ(1, SDL_HapticDestroyEffect_fake.call_count);
  EXPECT_EQ(12, SDL_HapticDestroyEffect_fake.arg1_val);
}

TEST_F(HapticTest, IsSupported)
{
  std::array values{-1, 0, 1};
  SET_RETURN_SEQ(SDL_HapticEffectSupported,
                 values.data(),
                 static_cast<int>(values.size()));

  cen::haptic_constant effect;
  EXPECT_FALSE(m_haptic.is_supported(effect));
  EXPECT_FALSE(m_haptic.is_supported(effect));
  EXPECT_TRUE(m_haptic.is_supported(effect));

  EXPECT_EQ(3, SDL_HapticEffectSupported_fake.call_count);
}

TEST_F(HapticTest, StreamOperator)
{
  SDL_HapticName_fake.return_val = "foo";
  std::cout << "COUT: " << m_haptic << '\n';
}
