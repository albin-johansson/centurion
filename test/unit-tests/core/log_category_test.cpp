#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"
#include "core/logging.hpp"

TEST(LogCategory, Values)
{
  ASSERT_EQ(10, cen::log_category_count());
  ASSERT_EQ(cen::to_underlying(cen::log_category::app), SDL_LOG_CATEGORY_APPLICATION);
  ASSERT_EQ(cen::to_underlying(cen::log_category::error), SDL_LOG_CATEGORY_ERROR);
  ASSERT_EQ(cen::to_underlying(cen::log_category::assert), SDL_LOG_CATEGORY_ASSERT);
  ASSERT_EQ(cen::to_underlying(cen::log_category::system), SDL_LOG_CATEGORY_SYSTEM);
  ASSERT_EQ(cen::to_underlying(cen::log_category::audio), SDL_LOG_CATEGORY_AUDIO);
  ASSERT_EQ(cen::to_underlying(cen::log_category::video), SDL_LOG_CATEGORY_VIDEO);
  ASSERT_EQ(cen::to_underlying(cen::log_category::render), SDL_LOG_CATEGORY_RENDER);
  ASSERT_EQ(cen::to_underlying(cen::log_category::input), SDL_LOG_CATEGORY_INPUT);
  ASSERT_EQ(cen::to_underlying(cen::log_category::test), SDL_LOG_CATEGORY_TEST);
  ASSERT_EQ(cen::to_underlying(cen::log_category::custom), SDL_LOG_CATEGORY_CUSTOM);
}

TEST(LogCategory, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::log_category>(SDL_LOG_CATEGORY_CUSTOM + 1)),
               cen::cen_error);

  ASSERT_EQ("app", cen::to_string(cen::log_category::app));
  ASSERT_EQ("error", cen::to_string(cen::log_category::error));
  ASSERT_EQ("assert", cen::to_string(cen::log_category::assert));
  ASSERT_EQ("system", cen::to_string(cen::log_category::system));
  ASSERT_EQ("audio", cen::to_string(cen::log_category::audio));
  ASSERT_EQ("video", cen::to_string(cen::log_category::video));
  ASSERT_EQ("render", cen::to_string(cen::log_category::render));
  ASSERT_EQ("input", cen::to_string(cen::log_category::input));
  ASSERT_EQ("test", cen::to_string(cen::log_category::test));
  ASSERT_EQ("custom", cen::to_string(cen::log_category::custom));

  std::clog << "Log category example: " << cen::log_category::video << '\n';
}