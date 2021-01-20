#include "haptic.hpp"

#include <gtest/gtest.h>

using namespace cen::literals;

namespace {

template <typename Effect>
void test_common()
{
  Effect effect;

  EXPECT_EQ(0_ms, effect.delay());
  EXPECT_EQ(0_ms, effect.interval());
  EXPECT_EQ(0_ms, effect.duration());
  EXPECT_EQ(0_ms, effect.attack_duration());
  EXPECT_EQ(0_ms, effect.fade_duration());
  EXPECT_EQ(0, effect.button());
  EXPECT_EQ(0, effect.fade_level());
  EXPECT_EQ(0, effect.attack_level());

  effect.set_delay(1'337_ms);
  EXPECT_EQ(1'337_ms, effect.delay());

  effect.set_interval(42_ms);
  EXPECT_EQ(42_ms, effect.interval());

  effect.set_duration(100_ms);
  EXPECT_EQ(100_ms, effect.duration());

  effect.set_attack_duration(12_ms);
  EXPECT_EQ(12_ms, effect.attack_duration());

  effect.set_fade_duration(27_ms);
  EXPECT_EQ(27_ms, effect.fade_duration());

  effect.set_button(3u);
  EXPECT_EQ(3u, effect.button());

  effect.set_fade_level(3'000);
  EXPECT_EQ(3'000, effect.fade_level());

  effect.set_attack_level(1'000);
  EXPECT_EQ(1'000, effect.attack_level());
}

}  // namespace

TEST(HapticEffect, CommonAPI)
{
  cen::haptic_constant effect;

  effect.set_duration(100_ms);
  EXPECT_EQ(100_ms, effect.duration());

  effect.set_delay(1'337_ms);
  EXPECT_EQ(1'337_ms, effect.delay());

  effect.set_button(3u);
  EXPECT_EQ(3u, effect.button());

  effect.set_interval(42_ms);
  EXPECT_EQ(42_ms, effect.interval());

  effect.set_attack_duration(12_ms);
  EXPECT_EQ(12_ms, effect.attack_duration());

  effect.set_attack_level(1'000);
  EXPECT_EQ(1'000, effect.attack_level());

  effect.set_fade_duration(27_ms);
  EXPECT_EQ(27_ms, effect.fade_duration());

  effect.set_fade_level(3'000);
  EXPECT_EQ(3'000, effect.fade_level());
}

TEST(HapticConstant, Defaults)
{
  test_common<cen::haptic_constant>();

  const cen::haptic_constant effect;
  EXPECT_EQ(SDL_HAPTIC_CONSTANT, effect.type());
}

TEST(HapticPeriodic, Defaults)
{
  test_common<cen::haptic_periodic>();

  cen::haptic_periodic effect;
  EXPECT_EQ(SDL_HAPTIC_SINE, effect.type());
  EXPECT_EQ(cen::haptic_periodic::sine, effect.type());

  effect.set_type(cen::haptic_periodic::sine);
  EXPECT_EQ(cen::haptic_periodic::sine, effect.type());

  effect.set_type(cen::haptic_periodic::left_right);
  EXPECT_EQ(cen::haptic_periodic::left_right, effect.type());

  effect.set_type(cen::haptic_periodic::triangle);
  EXPECT_EQ(cen::haptic_periodic::triangle, effect.type());

  effect.set_type(cen::haptic_periodic::sawtooth_down);
  EXPECT_EQ(cen::haptic_periodic::sawtooth_down, effect.type());

  effect.set_type(cen::haptic_periodic::sawtooth_up);
  EXPECT_EQ(cen::haptic_periodic::sawtooth_up, effect.type());

  effect.set_period(123_ms);
  EXPECT_EQ(123_ms, effect.period());

  effect.set_magnitude(42);
  EXPECT_EQ(42, effect.magnitude());

  effect.set_offset(321);
  EXPECT_EQ(321, effect.offset());

  effect.set_phase(101u);
  EXPECT_EQ(101u, effect.phase());

  EXPECT_EQ(SDL_HAPTIC_SINE, cen::haptic_periodic::sine);
  EXPECT_EQ(SDL_HAPTIC_LEFTRIGHT, cen::haptic_periodic::left_right);
  EXPECT_EQ(SDL_HAPTIC_TRIANGLE, cen::haptic_periodic::triangle);
  EXPECT_EQ(SDL_HAPTIC_SAWTOOTHDOWN, cen::haptic_periodic::sawtooth_down);
  EXPECT_EQ(SDL_HAPTIC_SAWTOOTHUP, cen::haptic_periodic::sawtooth_up);
}

TEST(HapticRamp, Defaults)
{
  test_common<cen::haptic_ramp>();

  cen::haptic_ramp effect;
  EXPECT_EQ(SDL_HAPTIC_RAMP, effect.type());

  effect.set_start_strength(1'234);
  EXPECT_EQ(1'234, effect.start_strength());

  effect.set_end_strength(4'321);
  EXPECT_EQ(4'321, effect.end_strength());
}