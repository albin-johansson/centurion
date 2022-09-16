/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
