#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/logging.hpp"

TEST(LogCategory, Values)
{
  ASSERT_EQ(SDL_LOG_CATEGORY_APPLICATION, to_underlying(cen::log_category::app));
  ASSERT_EQ(SDL_LOG_CATEGORY_ERROR, to_underlying(cen::log_category::error));
  ASSERT_EQ(SDL_LOG_CATEGORY_ASSERT, to_underlying(cen::log_category::assert));
  ASSERT_EQ(SDL_LOG_CATEGORY_SYSTEM, to_underlying(cen::log_category::system));
  ASSERT_EQ(SDL_LOG_CATEGORY_AUDIO, to_underlying(cen::log_category::audio));
  ASSERT_EQ(SDL_LOG_CATEGORY_VIDEO, to_underlying(cen::log_category::video));
  ASSERT_EQ(SDL_LOG_CATEGORY_RENDER, to_underlying(cen::log_category::render));
  ASSERT_EQ(SDL_LOG_CATEGORY_INPUT, to_underlying(cen::log_category::input));
  ASSERT_EQ(SDL_LOG_CATEGORY_TEST, to_underlying(cen::log_category::test));
  ASSERT_EQ(SDL_LOG_CATEGORY_CUSTOM, to_underlying(cen::log_category::custom));
}

TEST(LogCategory, ToString)
{
  ASSERT_THROW(to_string(cen::log_category(SDL_LOG_CATEGORY_RESERVED1)), cen::exception);

  ASSERT_EQ("app", to_string(cen::log_category::app));
  ASSERT_EQ("error", to_string(cen::log_category::error));
  ASSERT_EQ("assert", to_string(cen::log_category::assert));
  ASSERT_EQ("system", to_string(cen::log_category::system));
  ASSERT_EQ("audio", to_string(cen::log_category::audio));
  ASSERT_EQ("video", to_string(cen::log_category::video));
  ASSERT_EQ("render", to_string(cen::log_category::render));
  ASSERT_EQ("input", to_string(cen::log_category::input));
  ASSERT_EQ("test", to_string(cen::log_category::test));

  ASSERT_EQ("custom", to_string(cen::log_category::custom));
  ASSERT_EQ("custom", to_string(cen::log_category(SDL_LOG_CATEGORY_CUSTOM + 1)));

  std::cout << "log_category::video == " << cen::log_category::video << '\n';
}