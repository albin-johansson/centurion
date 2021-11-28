#include <gtest/gtest.h>

#include <iostream>  // clog

#include "audio/music.hpp"
#include "core/common.hpp"

TEST(MusicType, Values)
{
  ASSERT_EQ(9, cen::music_type_count());

  ASSERT_EQ(cen::to_underlying(cen::music_type::unknown), MUS_NONE);
  ASSERT_EQ(cen::to_underlying(cen::music_type::mp3), MUS_MP3);
  ASSERT_EQ(cen::to_underlying(cen::music_type::wav), MUS_WAV);
  ASSERT_EQ(cen::to_underlying(cen::music_type::cmd), MUS_CMD);
  ASSERT_EQ(cen::to_underlying(cen::music_type::mod), MUS_MOD);
  ASSERT_EQ(cen::to_underlying(cen::music_type::ogg), MUS_OGG);
  ASSERT_EQ(cen::to_underlying(cen::music_type::flac), MUS_FLAC);
  ASSERT_EQ(cen::to_underlying(cen::music_type::midi), MUS_MID);
  ASSERT_EQ(cen::to_underlying(cen::music_type::opus), MUS_OPUS);
}

TEST(MusicType, ToString)
{
  ASSERT_EQ("unknown", cen::to_string(cen::music_type::unknown));
  ASSERT_EQ("mp3", cen::to_string(cen::music_type::mp3));
  ASSERT_EQ("wav", cen::to_string(cen::music_type::wav));
  ASSERT_EQ("ogg", cen::to_string(cen::music_type::ogg));
  ASSERT_EQ("mod", cen::to_string(cen::music_type::mod));
  ASSERT_EQ("midi", cen::to_string(cen::music_type::midi));
  ASSERT_EQ("cmd", cen::to_string(cen::music_type::cmd));
  ASSERT_EQ("flac", cen::to_string(cen::music_type::flac));
  ASSERT_EQ("opus", cen::to_string(cen::music_type::opus));

  std::clog << "Music type example: " << cen::music_type::mp3 << '\n';
}
