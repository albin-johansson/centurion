#include <gtest/gtest.h>

#include <iostream>  // cout

#include "audio.hpp"
#include "common.hpp"

TEST(MusicType, Values)
{
  ASSERT_EQ(MUS_NONE, ToUnderlying(cen::music_type::none));
  ASSERT_EQ(MUS_MP3, ToUnderlying(cen::music_type::mp3));
  ASSERT_EQ(MUS_WAV, ToUnderlying(cen::music_type::wav));
  ASSERT_EQ(MUS_CMD, ToUnderlying(cen::music_type::cmd));
  ASSERT_EQ(MUS_MOD, ToUnderlying(cen::music_type::mod));
  ASSERT_EQ(MUS_OGG, ToUnderlying(cen::music_type::ogg));
  ASSERT_EQ(MUS_FLAC, ToUnderlying(cen::music_type::flac));
  ASSERT_EQ(MUS_MID, ToUnderlying(cen::music_type::midi));
  ASSERT_EQ(MUS_OPUS, ToUnderlying(cen::music_type::opus));
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
