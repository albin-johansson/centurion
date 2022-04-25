#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/audio.hpp"

TEST(MusicType, Values)
{
  ASSERT_EQ(MUS_NONE, to_underlying(cen::music_type::none));
  ASSERT_EQ(MUS_MP3, to_underlying(cen::music_type::mp3));
  ASSERT_EQ(MUS_WAV, to_underlying(cen::music_type::wav));
  ASSERT_EQ(MUS_CMD, to_underlying(cen::music_type::cmd));
  ASSERT_EQ(MUS_MOD, to_underlying(cen::music_type::mod));
  ASSERT_EQ(MUS_OGG, to_underlying(cen::music_type::ogg));
  ASSERT_EQ(MUS_FLAC, to_underlying(cen::music_type::flac));
  ASSERT_EQ(MUS_MID, to_underlying(cen::music_type::midi));
  ASSERT_EQ(MUS_OPUS, to_underlying(cen::music_type::opus));
}

TEST(MusicType, ToString)
{
  ASSERT_EQ("none", to_string(cen::music_type::none));
  ASSERT_EQ("mp3", to_string(cen::music_type::mp3));
  ASSERT_EQ("wav", to_string(cen::music_type::wav));
  ASSERT_EQ("ogg", to_string(cen::music_type::ogg));
  ASSERT_EQ("mod", to_string(cen::music_type::mod));
  ASSERT_EQ("midi", to_string(cen::music_type::midi));
  ASSERT_EQ("cmd", to_string(cen::music_type::cmd));
  ASSERT_EQ("flac", to_string(cen::music_type::flac));
  ASSERT_EQ("opus", to_string(cen::music_type::opus));

  std::cout << "music_type::mp3 == " << cen::music_type::mp3 << '\n';
}
