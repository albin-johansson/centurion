#include "centurion/input/haptic_feature.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

TEST(HapticFeature, Values)
{
  ASSERT_EQ(SDL_HAPTIC_CONSTANT, to_underlying(cen::haptic_feature::constant));
  ASSERT_EQ(SDL_HAPTIC_SINE, to_underlying(cen::haptic_feature::sine));
  ASSERT_EQ(SDL_HAPTIC_LEFTRIGHT, to_underlying(cen::haptic_feature::left_right));
  ASSERT_EQ(SDL_HAPTIC_TRIANGLE, to_underlying(cen::haptic_feature::triangle));
  ASSERT_EQ(SDL_HAPTIC_SAWTOOTHUP, to_underlying(cen::haptic_feature::sawtooth_up));
  ASSERT_EQ(SDL_HAPTIC_SAWTOOTHDOWN, to_underlying(cen::haptic_feature::sawtooth_down));
  ASSERT_EQ(SDL_HAPTIC_RAMP, to_underlying(cen::haptic_feature::ramp));
  ASSERT_EQ(SDL_HAPTIC_SPRING, to_underlying(cen::haptic_feature::spring));
  ASSERT_EQ(SDL_HAPTIC_DAMPER, to_underlying(cen::haptic_feature::damper));
  ASSERT_EQ(SDL_HAPTIC_INERTIA, to_underlying(cen::haptic_feature::inertia));
  ASSERT_EQ(SDL_HAPTIC_FRICTION, to_underlying(cen::haptic_feature::friction));
  ASSERT_EQ(SDL_HAPTIC_CUSTOM, to_underlying(cen::haptic_feature::custom));
  ASSERT_EQ(SDL_HAPTIC_GAIN, to_underlying(cen::haptic_feature::gain));
  ASSERT_EQ(SDL_HAPTIC_AUTOCENTER, to_underlying(cen::haptic_feature::autocenter));
  ASSERT_EQ(SDL_HAPTIC_STATUS, to_underlying(cen::haptic_feature::status));
  ASSERT_EQ(SDL_HAPTIC_PAUSE, to_underlying(cen::haptic_feature::pause));
}

TEST(HapticFeature, ToString)
{
  ASSERT_THROW(to_string(cen::haptic_feature(1u << 16u)), cen::exception);

  ASSERT_EQ("constant", to_string(cen::haptic_feature::constant));
  ASSERT_EQ("sine", to_string(cen::haptic_feature::sine));
  ASSERT_EQ("left_right", to_string(cen::haptic_feature::left_right));
  ASSERT_EQ("triangle", to_string(cen::haptic_feature::triangle));
  ASSERT_EQ("sawtooth_up", to_string(cen::haptic_feature::sawtooth_up));
  ASSERT_EQ("sawtooth_down", to_string(cen::haptic_feature::sawtooth_down));
  ASSERT_EQ("ramp", to_string(cen::haptic_feature::ramp));
  ASSERT_EQ("spring", to_string(cen::haptic_feature::spring));
  ASSERT_EQ("damper", to_string(cen::haptic_feature::damper));
  ASSERT_EQ("inertia", to_string(cen::haptic_feature::inertia));
  ASSERT_EQ("friction", to_string(cen::haptic_feature::friction));
  ASSERT_EQ("custom", to_string(cen::haptic_feature::custom));
  ASSERT_EQ("gain", to_string(cen::haptic_feature::gain));
  ASSERT_EQ("autocenter", to_string(cen::haptic_feature::autocenter));
  ASSERT_EQ("status", to_string(cen::haptic_feature::status));
  ASSERT_EQ("pause", to_string(cen::haptic_feature::pause));

  std::cout << "haptic_feature::spring == " << cen::haptic_feature::spring << '\n';
}
