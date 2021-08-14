#include "core/log_category.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

TEST(LogCategory, Values)
{
  ASSERT_EQ(10, cen::log_category_count());

  ASSERT_EQ(cen::log_category::app, SDL_LOG_CATEGORY_APPLICATION);
  ASSERT_EQ(cen::log_category::error, SDL_LOG_CATEGORY_ERROR);
  ASSERT_EQ(cen::log_category::assert, SDL_LOG_CATEGORY_ASSERT);
  ASSERT_EQ(cen::log_category::system, SDL_LOG_CATEGORY_SYSTEM);
  ASSERT_EQ(cen::log_category::audio, SDL_LOG_CATEGORY_AUDIO);
  ASSERT_EQ(cen::log_category::video, SDL_LOG_CATEGORY_VIDEO);
  ASSERT_EQ(cen::log_category::render, SDL_LOG_CATEGORY_RENDER);
  ASSERT_EQ(cen::log_category::input, SDL_LOG_CATEGORY_INPUT);
  ASSERT_EQ(cen::log_category::test, SDL_LOG_CATEGORY_TEST);
  ASSERT_EQ(cen::log_category::misc, SDL_LOG_CATEGORY_CUSTOM);

  ASSERT_EQ(SDL_LOG_CATEGORY_APPLICATION, cen::log_category::app);
  ASSERT_EQ(SDL_LOG_CATEGORY_ERROR, cen::log_category::error);
  ASSERT_EQ(SDL_LOG_CATEGORY_ASSERT, cen::log_category::assert);
  ASSERT_EQ(SDL_LOG_CATEGORY_SYSTEM, cen::log_category::system);
  ASSERT_EQ(SDL_LOG_CATEGORY_AUDIO, cen::log_category::audio);
  ASSERT_EQ(SDL_LOG_CATEGORY_VIDEO, cen::log_category::video);
  ASSERT_EQ(SDL_LOG_CATEGORY_RENDER, cen::log_category::render);
  ASSERT_EQ(SDL_LOG_CATEGORY_INPUT, cen::log_category::input);
  ASSERT_EQ(SDL_LOG_CATEGORY_TEST, cen::log_category::test);
  ASSERT_EQ(SDL_LOG_CATEGORY_CUSTOM, cen::log_category::misc);

  ASSERT_NE(cen::log_category::audio, SDL_LOG_CATEGORY_ERROR);
  ASSERT_NE(SDL_LOG_CATEGORY_SYSTEM, cen::log_category::render);
}

TEST(LogCategory, ToString)
{
  ASSERT_THROW(
      cen::to_string(static_cast<cen::log_category>(SDL_LOG_CATEGORY_CUSTOM + 1)),
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
  ASSERT_EQ("misc", cen::to_string(cen::log_category::misc));

  std::clog << "Log category example: " << cen::log_category::video << '\n';
}