#include "input/haptic.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>     // array
#include <iostream>  // cout

#include "core_mocks.hpp"
#include "input/haptic_constant.hpp"

extern "C"
{
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
  FAKE_VALUE_FUNC(int, SDL_HapticPause, SDL_Haptic*)
  FAKE_VALUE_FUNC(int, SDL_HapticUnpause, SDL_Haptic*)
  FAKE_VALUE_FUNC(int, SDL_HapticNewEffect, SDL_Haptic*, SDL_HapticEffect*)
  FAKE_VALUE_FUNC(int, SDL_HapticRunEffect, SDL_Haptic*, int, Uint32)
  FAKE_VALUE_FUNC(int, SDL_HapticStopEffect, SDL_Haptic*, int)
  FAKE_VALUE_FUNC(int, SDL_HapticGetEffectStatus, SDL_Haptic*, int)
  FAKE_VALUE_FUNC(int, SDL_HapticSetGain, SDL_Haptic*, int)
  FAKE_VALUE_FUNC(int, SDL_HapticSetAutocenter, SDL_Haptic*, int)
  FAKE_VALUE_FUNC(int, SDL_HapticStopAll, SDL_Haptic*)
  FAKE_VALUE_FUNC(int, SDL_HapticEffectSupported, SDL_Haptic*, SDL_HapticEffect*)
  FAKE_VALUE_FUNC(int, SDL_HapticUpdateEffect, SDL_Haptic*, int, SDL_HapticEffect*)
}

class HapticTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_HapticClose)
    RESET_FAKE(SDL_HapticDestroyEffect)
    RESET_FAKE(SDL_HapticOpen)
    RESET_FAKE(SDL_HapticOpenFromMouse)
    RESET_FAKE(SDL_HapticOpenFromJoystick)
    RESET_FAKE(SDL_HapticRumbleInit)
    RESET_FAKE(SDL_HapticRumblePlay)
    RESET_FAKE(SDL_HapticRumbleStop)
    RESET_FAKE(SDL_HapticRumbleSupported)
    RESET_FAKE(SDL_HapticQuery)
    RESET_FAKE(SDL_NumHaptics)
    RESET_FAKE(SDL_HapticIndex)
    RESET_FAKE(SDL_MouseIsHaptic)
    RESET_FAKE(SDL_HapticName)
    RESET_FAKE(SDL_HapticOpened)
    RESET_FAKE(SDL_JoystickIsHaptic)
    RESET_FAKE(SDL_HapticNumEffects)
    RESET_FAKE(SDL_HapticNumEffectsPlaying)
    RESET_FAKE(SDL_HapticNumAxes)
    RESET_FAKE(SDL_HapticPause)
    RESET_FAKE(SDL_HapticUnpause)
    RESET_FAKE(SDL_HapticNewEffect)
    RESET_FAKE(SDL_HapticRunEffect)
    RESET_FAKE(SDL_HapticStopEffect)
    RESET_FAKE(SDL_HapticGetEffectStatus)
    RESET_FAKE(SDL_HapticSetGain)
    RESET_FAKE(SDL_HapticSetAutocenter)
    RESET_FAKE(SDL_HapticStopAll)
    RESET_FAKE(SDL_HapticEffectSupported)
    RESET_FAKE(SDL_HapticUpdateEffect)
  }

  cen::haptic_handle m_haptic{nullptr};
};

using namespace cen::literals;

TEST_F(HapticTest, IndexConstructor)
{
  ASSERT_THROW(cen::haptic{}, cen::sdl_error);
  ASSERT_EQ(1u, SDL_HapticOpen_fake.call_count);
}

TEST_F(HapticTest, PointerConstructor)
{
  static_assert(!noexcept(cen::haptic{nullptr}));
  ASSERT_THROW(cen::haptic{nullptr}, cen::exception);

  static_assert(noexcept(cen::haptic_handle{nullptr}));
  ASSERT_NO_THROW(cen::haptic_handle{nullptr});
}

TEST_F(HapticTest, FromJoystick)
{
  cen::joystick_handle handle{nullptr};
  ASSERT_THROW(cen::haptic::from_joystick(handle), cen::sdl_error);
  ASSERT_EQ(1u, SDL_HapticOpenFromJoystick_fake.call_count);
}

TEST_F(HapticTest, FromMouse)
{
  ASSERT_THROW(cen::haptic::from_mouse(), cen::sdl_error);
  ASSERT_EQ(1u, SDL_HapticOpenFromMouse_fake.call_count);
}

TEST_F(HapticTest, InitRumble)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_HapticRumbleInit, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.init_rumble());
  ASSERT_TRUE(m_haptic.init_rumble());

  ASSERT_EQ(2u, SDL_HapticRumbleInit_fake.call_count);
}

TEST_F(HapticTest, PlayRumble)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_HapticRumblePlay, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.play_rumble(0.5f, 100_ms));
  ASSERT_TRUE(m_haptic.play_rumble(0.5f, 100_ms));

  ASSERT_EQ(0.5f, SDL_HapticRumblePlay_fake.arg1_val);
  ASSERT_EQ(100u, SDL_HapticRumblePlay_fake.arg2_val);
  ASSERT_EQ(2u, SDL_HapticRumblePlay_fake.call_count);
}

TEST_F(HapticTest, StopRumble)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_HapticRumbleStop, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.stop_rumble());
  ASSERT_TRUE(m_haptic.stop_rumble());

  ASSERT_EQ(2u, SDL_HapticRumbleStop_fake.call_count);
}

TEST_F(HapticTest, IsRumbleSupported)
{
  std::array values{-1, 0, 1};
  SET_RETURN_SEQ(SDL_HapticRumbleSupported, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.is_rumble_supported());
  ASSERT_FALSE(m_haptic.is_rumble_supported());
  ASSERT_TRUE(m_haptic.is_rumble_supported());
  ASSERT_EQ(3u, SDL_HapticRumbleSupported_fake.call_count);
}

TEST_F(HapticTest, HasFeatureConstant)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_CONSTANT};
  SET_RETURN_SEQ(SDL_HapticQuery, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.has_feature_constant());
  ASSERT_TRUE(m_haptic.has_feature_constant());

  ASSERT_EQ(2u, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureSine)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_SINE};
  SET_RETURN_SEQ(SDL_HapticQuery, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.has_feature_sine());
  ASSERT_TRUE(m_haptic.has_feature_sine());

  ASSERT_EQ(2u, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureLeftRight)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_LEFTRIGHT};
  SET_RETURN_SEQ(SDL_HapticQuery, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.has_feature_left_right());
  ASSERT_TRUE(m_haptic.has_feature_left_right());

  ASSERT_EQ(2u, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureTriangle)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_TRIANGLE};
  SET_RETURN_SEQ(SDL_HapticQuery, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.has_feature_triangle());
  ASSERT_TRUE(m_haptic.has_feature_triangle());

  ASSERT_EQ(2u, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureSawtoothUp)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_SAWTOOTHUP};
  SET_RETURN_SEQ(SDL_HapticQuery, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.has_feature_sawtooth_up());
  ASSERT_TRUE(m_haptic.has_feature_sawtooth_up());

  ASSERT_EQ(2u, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureSawtoothDown)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_SAWTOOTHDOWN};
  SET_RETURN_SEQ(SDL_HapticQuery, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.has_feature_sawtooth_down());
  ASSERT_TRUE(m_haptic.has_feature_sawtooth_down());

  ASSERT_EQ(2u, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureRamp)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_RAMP};
  SET_RETURN_SEQ(SDL_HapticQuery, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.has_feature_ramp());
  ASSERT_TRUE(m_haptic.has_feature_ramp());

  ASSERT_EQ(2u, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureSpring)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_SPRING};
  SET_RETURN_SEQ(SDL_HapticQuery, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.has_feature_spring());
  ASSERT_TRUE(m_haptic.has_feature_spring());

  ASSERT_EQ(2u, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureDamper)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_DAMPER};
  SET_RETURN_SEQ(SDL_HapticQuery, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.has_feature_damper());
  ASSERT_TRUE(m_haptic.has_feature_damper());

  ASSERT_EQ(2u, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureInertia)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_INERTIA};
  SET_RETURN_SEQ(SDL_HapticQuery, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.has_feature_inertia());
  ASSERT_TRUE(m_haptic.has_feature_inertia());

  ASSERT_EQ(2u, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureFriction)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_FRICTION};
  SET_RETURN_SEQ(SDL_HapticQuery, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.has_feature_friction());
  ASSERT_TRUE(m_haptic.has_feature_friction());

  ASSERT_EQ(2u, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureGain)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_GAIN};
  SET_RETURN_SEQ(SDL_HapticQuery, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.has_feature_gain());
  ASSERT_TRUE(m_haptic.has_feature_gain());

  ASSERT_EQ(2u, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureAutocenter)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_AUTOCENTER};
  SET_RETURN_SEQ(SDL_HapticQuery, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.has_feature_autocenter());
  ASSERT_TRUE(m_haptic.has_feature_autocenter());

  ASSERT_EQ(2u, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureStatus)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_STATUS};
  SET_RETURN_SEQ(SDL_HapticQuery, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.has_feature_status());
  ASSERT_TRUE(m_haptic.has_feature_status());

  ASSERT_EQ(2u, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeaturePause)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_PAUSE};
  SET_RETURN_SEQ(SDL_HapticQuery, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.has_feature_pause());
  ASSERT_TRUE(m_haptic.has_feature_pause());

  ASSERT_EQ(2u, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, HasFeatureCustom)
{
  std::array<unsigned, 2> values{0, SDL_HAPTIC_CUSTOM};
  SET_RETURN_SEQ(SDL_HapticQuery, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.has_feature_custom());
  ASSERT_TRUE(m_haptic.has_feature_custom());

  ASSERT_EQ(2u, SDL_HapticQuery_fake.call_count);
}

TEST_F(HapticTest, Index)
{
  std::array values{-1, 1};
  SET_RETURN_SEQ(SDL_HapticIndex, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.index());
  ASSERT_EQ(1, m_haptic.index());

  ASSERT_EQ(2u, SDL_HapticIndex_fake.call_count);
}

TEST_F(HapticTest, Name)
{
  std::array values{-1, 1};
  SET_RETURN_SEQ(SDL_HapticIndex, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.name());
  ASSERT_EQ(0u, SDL_HapticName_fake.call_count);
  ASSERT_EQ(1u, SDL_HapticIndex_fake.call_count);

  const auto name [[maybe_unused]] = m_haptic.name();
  ASSERT_EQ(1u, SDL_HapticName_fake.call_count);
  ASSERT_EQ(2u, SDL_HapticIndex_fake.call_count);
}

TEST_F(HapticTest, IsOpened)
{
  const auto opened [[maybe_unused]] = cen::haptic::is_opened(0);
  ASSERT_EQ(1u, SDL_HapticOpened_fake.call_count);
}

TEST_F(HapticTest, IsJoystickHaptic)
{
  std::array values{-1, 0, 1};
  SET_RETURN_SEQ(SDL_JoystickIsHaptic, values.data(), cen::isize(values));

  const cen::joystick_handle joystick{nullptr};

  ASSERT_FALSE(cen::haptic::is_joystick_haptic(joystick));
  ASSERT_FALSE(cen::haptic::is_joystick_haptic(joystick));
  ASSERT_TRUE(cen::haptic::is_joystick_haptic(joystick));

  ASSERT_EQ(3u, SDL_JoystickIsHaptic_fake.call_count);
}

TEST_F(HapticTest, EffectCapacity)
{
  std::array values{-1, 7};
  SET_RETURN_SEQ(SDL_HapticNumEffects, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.effect_capacity());
  ASSERT_EQ(7, m_haptic.effect_capacity());

  ASSERT_EQ(2u, SDL_HapticNumEffects_fake.call_count);
}

TEST_F(HapticTest, ConcurrentCapacity)
{
  std::array values{-1, 4};
  SET_RETURN_SEQ(SDL_HapticNumEffectsPlaying, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.concurrent_capacity());
  ASSERT_EQ(4, m_haptic.concurrent_capacity());

  ASSERT_EQ(2u, SDL_HapticNumEffectsPlaying_fake.call_count);
}

TEST_F(HapticTest, AxisCount)
{
  const auto count [[maybe_unused]] = m_haptic.axis_count();
  ASSERT_EQ(1u, SDL_HapticNumAxes_fake.call_count);
}

TEST_F(HapticTest, Count)
{
  const auto count [[maybe_unused]] = cen::haptic::count();
  ASSERT_EQ(1u, SDL_NumHaptics_fake.call_count);
}

TEST_F(HapticTest, IsMouseHaptic)
{
  const auto isHaptic [[maybe_unused]] = cen::haptic::is_mouse_haptic();
  ASSERT_EQ(1u, SDL_MouseIsHaptic_fake.call_count);
}

TEST_F(HapticTest, Pause)
{
  // Must feature pause support
  std::array features{SDL_HAPTIC_PAUSE};
  SET_RETURN_SEQ(SDL_HapticQuery, features.data(), cen::isize(features));

  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_HapticPause, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.pause());
  ASSERT_TRUE(m_haptic.pause());
  ASSERT_EQ(2u, SDL_HapticPause_fake.call_count);
}

TEST_F(HapticTest, Unpause)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_HapticUnpause, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.unpause());
  ASSERT_TRUE(m_haptic.unpause());
  ASSERT_EQ(2u, SDL_HapticUnpause_fake.call_count);
}

TEST_F(HapticTest, Upload)
{
  std::array values{-1, 7};
  SET_RETURN_SEQ(SDL_HapticNewEffect, values.data(), cen::isize(values));

  cen::haptic_constant effect;
  ASSERT_FALSE(m_haptic.upload(effect));
  ASSERT_EQ(7, m_haptic.upload(effect));

  ASSERT_EQ(2u, SDL_HapticNewEffect_fake.call_count);
}

TEST_F(HapticTest, Update)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_HapticUpdateEffect, values.data(), cen::isize(values));

  cen::haptic_constant effect;
  ASSERT_FALSE(m_haptic.update(42, effect));
  ASSERT_TRUE(m_haptic.update(42, effect));

  ASSERT_EQ(2u, SDL_HapticUpdateEffect_fake.call_count);
}

TEST_F(HapticTest, Run)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_HapticRunEffect, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.run(42));
  ASSERT_EQ(1u, SDL_HapticRunEffect_fake.arg2_val);

  ASSERT_TRUE(m_haptic.run(42, 7));
  ASSERT_EQ(7u, SDL_HapticRunEffect_fake.arg2_val);

  ASSERT_EQ(2u, SDL_HapticRunEffect_fake.call_count);
}

TEST_F(HapticTest, Stop)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_HapticStopEffect, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.stop(42));
  ASSERT_TRUE(m_haptic.stop(42));

  ASSERT_EQ(2u, SDL_HapticStopEffect_fake.call_count);
}

TEST_F(HapticTest, StopAll)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_HapticStopAll, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.stop_all());
  ASSERT_TRUE(m_haptic.stop_all());

  ASSERT_EQ(2u, SDL_HapticStopAll_fake.call_count);
}

TEST_F(HapticTest, Destroy)
{
  m_haptic.destroy(12);
  ASSERT_EQ(1u, SDL_HapticDestroyEffect_fake.call_count);
  ASSERT_EQ(12, SDL_HapticDestroyEffect_fake.arg1_val);
}

TEST_F(HapticTest, SetGain)
{
  // Must feature gain support
  std::array features{SDL_HAPTIC_GAIN};
  SET_RETURN_SEQ(SDL_HapticQuery, features.data(), cen::isize(features));

  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_HapticSetGain, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.set_gain(3));
  ASSERT_TRUE(m_haptic.set_gain(24));
  ASSERT_EQ(24, SDL_HapticSetGain_fake.arg1_val);

  ASSERT_NO_FATAL_FAILURE(m_haptic.set_gain(0));
  ASSERT_NO_FATAL_FAILURE(m_haptic.set_gain(100));

  ASSERT_EQ(4u, SDL_HapticSetGain_fake.call_count);
}

TEST_F(HapticTest, SetAutocenter)
{
  // Must feature autocenter support
  std::array features{SDL_HAPTIC_AUTOCENTER};
  SET_RETURN_SEQ(SDL_HapticQuery, features.data(), cen::isize(features));

  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_HapticSetAutocenter, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.set_autocenter(3));
  ASSERT_TRUE(m_haptic.set_autocenter(24));
  ASSERT_EQ(24, SDL_HapticSetAutocenter_fake.arg1_val);

  ASSERT_NO_FATAL_FAILURE(m_haptic.set_autocenter(0));
  ASSERT_NO_FATAL_FAILURE(m_haptic.set_autocenter(100));

  ASSERT_EQ(4u, SDL_HapticSetAutocenter_fake.call_count);
}

TEST_F(HapticTest, IsSupported)
{
  std::array values{-1, 0, 1};
  SET_RETURN_SEQ(SDL_HapticEffectSupported, values.data(), cen::isize(values));

  cen::haptic_constant effect;
  ASSERT_FALSE(m_haptic.is_supported(effect));
  ASSERT_FALSE(m_haptic.is_supported(effect));
  ASSERT_TRUE(m_haptic.is_supported(effect));

  ASSERT_EQ(3u, SDL_HapticEffectSupported_fake.call_count);
}

TEST_F(HapticTest, IsPlaying)
{
  // Must feature status support
  std::array features{SDL_HAPTIC_STATUS};
  SET_RETURN_SEQ(SDL_HapticQuery, features.data(), cen::isize(features));

  std::array values{-1, 0, 1};
  SET_RETURN_SEQ(SDL_HapticGetEffectStatus, values.data(), cen::isize(values));

  ASSERT_FALSE(m_haptic.is_playing(0));  // Error
  ASSERT_FALSE(m_haptic.is_playing(0));
  ASSERT_TRUE(m_haptic.is_playing(0));

  ASSERT_EQ(3u, SDL_HapticGetEffectStatus_fake.call_count);
}

TEST_F(HapticTest, StreamOperator)
{
  SDL_HapticName_fake.return_val = "foo";
  std::clog << m_haptic << '\n';
}
