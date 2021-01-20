#include "haptic.hpp"

#include <gtest/gtest.h>

using namespace cen::literals;

template <typename Effect>
void test()
{
  Effect effect;

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
  test<cen::haptic_constant>();
  const cen::haptic_constant effect;

  EXPECT_EQ(SDL_HAPTIC_CONSTANT, effect.type());
  EXPECT_EQ(0_ms, effect.delay());
  EXPECT_EQ(0_ms, effect.interval());
  EXPECT_EQ(0_ms, effect.duration());
  EXPECT_EQ(0_ms, effect.attack_duration());
  EXPECT_EQ(0_ms, effect.fade_duration());
  EXPECT_EQ(0, effect.attack_level());
  EXPECT_EQ(0, effect.fade_level());
  EXPECT_EQ(0, effect.button());
}

TEST(HapticPeriodic, Defaults)
{
  test<cen::haptic_periodic>();
  cen::haptic_periodic effect;

  EXPECT_EQ(SDL_HAPTIC_SINE, effect.type());
  EXPECT_EQ(cen::haptic_periodic::sine, effect.type());

  EXPECT_EQ(0_ms, effect.delay());
  EXPECT_EQ(0_ms, effect.interval());
  EXPECT_EQ(0_ms, effect.duration());
  EXPECT_EQ(0_ms, effect.attack_duration());
  EXPECT_EQ(0_ms, effect.fade_duration());
  EXPECT_EQ(0, effect.attack_level());
  EXPECT_EQ(0, effect.fade_level());
  EXPECT_EQ(0, effect.button());

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

  EXPECT_EQ(SDL_HAPTIC_SINE, cen::haptic_periodic::sine);
  EXPECT_EQ(SDL_HAPTIC_LEFTRIGHT, cen::haptic_periodic::left_right);
  EXPECT_EQ(SDL_HAPTIC_TRIANGLE, cen::haptic_periodic::triangle);
  EXPECT_EQ(SDL_HAPTIC_SAWTOOTHDOWN, cen::haptic_periodic::sawtooth_down);
  EXPECT_EQ(SDL_HAPTIC_SAWTOOTHUP, cen::haptic_periodic::sawtooth_up);
}