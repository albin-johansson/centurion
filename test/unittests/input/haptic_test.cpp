#include "haptic.hpp"

#include <gtest/gtest.h>

#include "typed_test_macros.hpp"

using namespace cen::literals;

using all_effects = testing::Types<cen::haptic_constant,
                                   cen::haptic_periodic,
                                   cen::haptic_condition,
                                   cen::haptic_ramp,
                                   cen::haptic_left_right,
                                   cen::haptic_custom>;

CENTURION_DEFINE_TYPED_TEST(HapticCommonTest, all_effects)
{
  TypeParam effect;

  effect.set_duration(12_ms);
  EXPECT_EQ(12_ms, effect.duration());

  const auto type [[maybe_unused]] = effect.type();
}

using delay_effects = testing::Types<cen::haptic_constant,
                                     cen::haptic_periodic,
                                     cen::haptic_condition,
                                     cen::haptic_ramp,
                                     cen::haptic_custom>;

CENTURION_DEFINE_TYPED_TEST(HapticDelayTest, delay_effects)
{
  TypeParam effect;

  effect.set_delay(278_ms);
  EXPECT_EQ(278_ms, effect.delay());
}

using envelope_effects = testing::Types<cen::haptic_constant,
                                        cen::haptic_periodic,
                                        cen::haptic_ramp,
                                        cen::haptic_custom>;

CENTURION_DEFINE_TYPED_TEST(HapticEnvelopeTest, envelope_effects)
{
  TypeParam effect;

  EXPECT_EQ(0_ms, effect.attack_duration());
  EXPECT_EQ(0_ms, effect.fade_duration());
  EXPECT_EQ(0, effect.fade_level());
  EXPECT_EQ(0, effect.attack_level());

  effect.set_attack_duration(12_ms);
  EXPECT_EQ(12_ms, effect.attack_duration());

  effect.set_fade_duration(27_ms);
  EXPECT_EQ(27_ms, effect.fade_duration());

  effect.set_fade_level(3'000);
  EXPECT_EQ(3'000, effect.fade_level());

  effect.set_attack_level(1'000);
  EXPECT_EQ(1'000, effect.attack_level());
}

using trigger_effects = testing::Types<cen::haptic_constant,
                                       cen::haptic_periodic,
                                       cen::haptic_condition,
                                       cen::haptic_ramp,
                                       cen::haptic_custom>;

CENTURION_DEFINE_TYPED_TEST(HapticTriggerTest, trigger_effects)
{
  TypeParam effect;

  EXPECT_EQ(0_ms, effect.interval());
  EXPECT_EQ(0, effect.button());

  effect.set_interval(42_ms);
  EXPECT_EQ(42_ms, effect.interval());

  effect.set_button(3u);
  EXPECT_EQ(3u, effect.button());
}

CENTURION_REGISTER_TYPED_TEST(HapticCommonTest, all_effects);
CENTURION_REGISTER_TYPED_TEST(HapticDelayTest, envelope_effects);
CENTURION_REGISTER_TYPED_TEST(HapticEnvelopeTest, envelope_effects);
CENTURION_REGISTER_TYPED_TEST(HapticTriggerTest, trigger_effects);

TEST(HapticConstant, Defaults)
{
  cen::haptic_constant effect;
  EXPECT_EQ(SDL_HAPTIC_CONSTANT, effect.type());

  effect.set_duration(100_ms);
  EXPECT_EQ(100_ms, effect.duration());

  effect.set_delay(1'337_ms);
  EXPECT_EQ(1'337_ms, effect.delay());
}

TEST(HapticPeriodic, Defaults)
{
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
  cen::haptic_ramp effect;
  EXPECT_EQ(SDL_HAPTIC_RAMP, effect.type());

  effect.set_start_strength(1'234);
  EXPECT_EQ(1'234, effect.start_strength());

  effect.set_end_strength(4'321);
  EXPECT_EQ(4'321, effect.end_strength());
}

TEST(HapticCustom, Defaults)
{
  cen::haptic_custom effect;
  EXPECT_EQ(SDL_HAPTIC_CUSTOM, effect.type());

  effect.set_axis_count(123u);
  EXPECT_EQ(123u, effect.axis_count());

  effect.set_sample_period(27_ms);
  EXPECT_EQ(27_ms, effect.sample_period());

  effect.set_sample_count(42);
  EXPECT_EQ(42, effect.sample_count());

  cen::u16 data{12};
  effect.set_data(&data);
  ASSERT_TRUE(effect.data());
  EXPECT_EQ(data, *effect.data());
}

TEST(HapticCondition, Defaults)
{
  using u16vector = cen::vector3<cen::u16>;
  using i16vector = cen::vector3<cen::i16>;

  cen::haptic_condition effect;
  EXPECT_EQ(cen::haptic_condition::spring, effect.type());

  effect.set_joystick_positive_level({1, 2, 3});
  EXPECT_EQ((u16vector{1, 2, 3}), effect.joystick_positive_level());

  effect.set_joystick_negative_level({4, 5, 6});
  EXPECT_EQ((u16vector{4, 5, 6}), effect.joystick_negative_level());

  effect.set_force_rate_positive({7, 8, 9});
  EXPECT_EQ((i16vector{7, 8, 9}), effect.force_rate_positive());

  effect.set_force_rate_negative({10, 11, 12});
  EXPECT_EQ((i16vector{10, 11, 12}), effect.force_rate_negative());

  effect.set_deadband({13, 14, 15});
  EXPECT_EQ((u16vector{13, 14, 15}), effect.deadband());

  effect.set_center({16, 17, 18});
  EXPECT_EQ((i16vector{16, 17, 18}), effect.center());

  EXPECT_EQ(SDL_HAPTIC_SPRING, cen::haptic_condition::spring);
  EXPECT_EQ(SDL_HAPTIC_DAMPER, cen::haptic_condition::damper);
  EXPECT_EQ(SDL_HAPTIC_INERTIA, cen::haptic_condition::inertia);
  EXPECT_EQ(SDL_HAPTIC_FRICTION, cen::haptic_condition::friction);
}

TEST(HapticLeftRight, Defaults)
{
  cen::haptic_left_right effect;
  EXPECT_EQ(SDL_HAPTIC_LEFTRIGHT, effect.type());

  effect.set_large_magnitude(27u);
  EXPECT_EQ(27u, effect.large_magnitude());

  effect.set_small_magnitude(182u);
  EXPECT_EQ(182u, effect.small_magnitude());
}