#include "input/haptic_feature.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"

TEST(HapticFeature, Values)
{
  ASSERT_EQ(SDL_HAPTIC_CONSTANT, cen::to_underlying(cen::haptic_feature::constant));
  ASSERT_EQ(SDL_HAPTIC_SINE, cen::to_underlying(cen::haptic_feature::sine));
  ASSERT_EQ(SDL_HAPTIC_LEFTRIGHT, cen::to_underlying(cen::haptic_feature::left_right));
  ASSERT_EQ(SDL_HAPTIC_TRIANGLE, cen::to_underlying(cen::haptic_feature::triangle));
  ASSERT_EQ(SDL_HAPTIC_SAWTOOTHUP, cen::to_underlying(cen::haptic_feature::sawtooth_up));
  ASSERT_EQ(SDL_HAPTIC_SAWTOOTHDOWN, cen::to_underlying(cen::haptic_feature::sawtooth_down));
  ASSERT_EQ(SDL_HAPTIC_RAMP, cen::to_underlying(cen::haptic_feature::ramp));
  ASSERT_EQ(SDL_HAPTIC_SPRING, cen::to_underlying(cen::haptic_feature::spring));
  ASSERT_EQ(SDL_HAPTIC_DAMPER, cen::to_underlying(cen::haptic_feature::damper));
  ASSERT_EQ(SDL_HAPTIC_INERTIA, cen::to_underlying(cen::haptic_feature::inertia));
  ASSERT_EQ(SDL_HAPTIC_FRICTION, cen::to_underlying(cen::haptic_feature::friction));
  ASSERT_EQ(SDL_HAPTIC_CUSTOM, cen::to_underlying(cen::haptic_feature::custom));
  ASSERT_EQ(SDL_HAPTIC_GAIN, cen::to_underlying(cen::haptic_feature::gain));
  ASSERT_EQ(SDL_HAPTIC_AUTOCENTER, cen::to_underlying(cen::haptic_feature::autocenter));
  ASSERT_EQ(SDL_HAPTIC_STATUS, cen::to_underlying(cen::haptic_feature::status));
  ASSERT_EQ(SDL_HAPTIC_PAUSE, cen::to_underlying(cen::haptic_feature::pause));
}

TEST(HapticFeature, ToString)
{
  ASSERT_THROW(cen::ToString(static_cast<cen::haptic_feature>(1u << 16u)), cen::exception);

  ASSERT_EQ("constant", cen::ToString(cen::haptic_feature::constant));
  ASSERT_EQ("sine", cen::ToString(cen::haptic_feature::sine));
  ASSERT_EQ("left_right", cen::ToString(cen::haptic_feature::left_right));
  ASSERT_EQ("triangle", cen::ToString(cen::haptic_feature::triangle));
  ASSERT_EQ("sawtooth_up", cen::ToString(cen::haptic_feature::sawtooth_up));
  ASSERT_EQ("sawtooth_down", cen::ToString(cen::haptic_feature::sawtooth_down));
  ASSERT_EQ("ramp", cen::ToString(cen::haptic_feature::ramp));
  ASSERT_EQ("spring", cen::ToString(cen::haptic_feature::spring));
  ASSERT_EQ("damper", cen::ToString(cen::haptic_feature::damper));
  ASSERT_EQ("inertia", cen::ToString(cen::haptic_feature::inertia));
  ASSERT_EQ("friction", cen::ToString(cen::haptic_feature::friction));
  ASSERT_EQ("custom", cen::ToString(cen::haptic_feature::custom));
  ASSERT_EQ("gain", cen::ToString(cen::haptic_feature::gain));
  ASSERT_EQ("autocenter", cen::ToString(cen::haptic_feature::autocenter));
  ASSERT_EQ("status", cen::ToString(cen::haptic_feature::status));
  ASSERT_EQ("pause", cen::ToString(cen::haptic_feature::pause));

  std::clog << "Haptic feature example: " << cen::haptic_feature::spring << '\n';
}
