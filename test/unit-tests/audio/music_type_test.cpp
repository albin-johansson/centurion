#include <gtest/gtest.h>

#include <iostream>  // clog

#include "audio/music.hpp"
#include "core/common.hpp"

TEST(MusicType, Values)
{
  ASSERT_EQ(cen::ToUnderlying(cen::MusicType::None), MUS_NONE);
  ASSERT_EQ(cen::ToUnderlying(cen::MusicType::MP3), MUS_MP3);
  ASSERT_EQ(cen::ToUnderlying(cen::MusicType::WAV), MUS_WAV);
  ASSERT_EQ(cen::ToUnderlying(cen::MusicType::CMD), MUS_CMD);
  ASSERT_EQ(cen::ToUnderlying(cen::MusicType::MOD), MUS_MOD);
  ASSERT_EQ(cen::ToUnderlying(cen::MusicType::OGG), MUS_OGG);
  ASSERT_EQ(cen::ToUnderlying(cen::MusicType::FLAC), MUS_FLAC);
  ASSERT_EQ(cen::ToUnderlying(cen::MusicType::MIDI), MUS_MID);
  ASSERT_EQ(cen::ToUnderlying(cen::MusicType::OPUS), MUS_OPUS);
}
