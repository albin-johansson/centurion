#include "audio/music_type.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

TEST(MusicType, Values)
{
  ASSERT_EQ(cen::music_type::unknown, MUS_NONE);
  ASSERT_EQ(cen::music_type::mp3, MUS_MP3);
  ASSERT_EQ(cen::music_type::wav, MUS_WAV);
  ASSERT_EQ(cen::music_type::cmd, MUS_CMD);
  ASSERT_EQ(cen::music_type::mod, MUS_MOD);
  ASSERT_EQ(cen::music_type::ogg, MUS_OGG);
  ASSERT_EQ(cen::music_type::flac, MUS_FLAC);
  ASSERT_EQ(cen::music_type::midi, MUS_MID);
  ASSERT_EQ(cen::music_type::opus, MUS_OPUS);

  ASSERT_EQ(MUS_NONE, cen::music_type::unknown);
  ASSERT_EQ(MUS_MP3, cen::music_type::mp3);
  ASSERT_EQ(MUS_WAV, cen::music_type::wav);
  ASSERT_EQ(MUS_CMD, cen::music_type::cmd);
  ASSERT_EQ(MUS_MOD, cen::music_type::mod);
  ASSERT_EQ(MUS_OGG, cen::music_type::ogg);
  ASSERT_EQ(MUS_FLAC, cen::music_type::flac);
  ASSERT_EQ(MUS_MID, cen::music_type::midi);
  ASSERT_EQ(MUS_OPUS, cen::music_type::opus);

  ASSERT_NE(cen::music_type::cmd, MUS_MP3);
  ASSERT_NE(MUS_FLAC, cen::music_type::mod);
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
