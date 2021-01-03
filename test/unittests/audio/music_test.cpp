#include "music.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout
#include <memory>    // unique_ptr
#include <type_traits>

#include "log.hpp"

static_assert(std::is_final_v<cen::music>);

static_assert(!std::is_nothrow_copy_constructible_v<cen::music>);
static_assert(!std::is_nothrow_copy_assignable_v<cen::music>);

static_assert(std::is_nothrow_move_constructible_v<cen::music>);
static_assert(std::is_nothrow_move_assignable_v<cen::music>);

class MusicTest : public testing::Test
{
 protected:
  static void SetUpTestSuite()
  {
    m_music = std::make_unique<cen::music>("resources/hiddenPond.mp3");
  }

  static void TearDownTestSuite()
  {
    m_music.reset();
  }

  inline static std::unique_ptr<cen::music> m_music;
};

TEST_F(MusicTest, Constructor)
{
  EXPECT_THROW(cen::music{"foobar"}, cen::mix_error);
}

TEST_F(MusicTest, Play)
{
  m_music->play();
  EXPECT_TRUE(cen::music::is_playing());
  EXPECT_FALSE(cen::music::is_fading());
  EXPECT_FALSE(cen::music::is_paused());
  EXPECT_EQ(cen::fade_status::none, cen::music::get_fade_status());

  cen::music::halt();

  m_music->play(cen::music::loopForever);
  EXPECT_TRUE(cen::music::is_playing());
  EXPECT_FALSE(cen::music::is_fading());
  EXPECT_FALSE(cen::music::is_paused());
  EXPECT_EQ(cen::fade_status::none, cen::music::get_fade_status());

  m_music->pause();
  cen::music::halt();
}

TEST_F(MusicTest, Resume)
{
  EXPECT_NO_THROW(cen::music::resume());

  m_music->play();
  EXPECT_NO_THROW(cen::music::resume());

  cen::music::pause();
  EXPECT_TRUE(cen::music::is_paused());

  cen::music::resume();
  EXPECT_TRUE(cen::music::is_playing());

  cen::music::halt();
  EXPECT_NO_THROW(cen::music::resume());
}

TEST_F(MusicTest, Pause)
{
  EXPECT_NO_THROW(cen::music::pause());

  m_music->play();

  cen::music::pause();
  EXPECT_TRUE(cen::music::is_paused());

  m_music->fade_in(cen::milliseconds<int>{100});

  cen::music::pause();
  EXPECT_TRUE(cen::music::is_paused());
}

TEST_F(MusicTest, Halt)
{
  EXPECT_NO_THROW(cen::music::halt());

  m_music->play();
  cen::music::halt();

  EXPECT_FALSE(cen::music::is_playing());
  EXPECT_FALSE(cen::music::is_fading());

  m_music->fade_in(cen::milliseconds<int>{100});
  cen::music::halt();

  EXPECT_FALSE(cen::music::is_playing());
  EXPECT_FALSE(cen::music::is_fading());
}

TEST_F(MusicTest, FadeIn)
{
  EXPECT_FALSE(cen::music::is_fading());

  EXPECT_NO_THROW(m_music->fade_in(cen::milliseconds<int>{-1}));

  cen::music::halt();

  m_music->fade_in(cen::milliseconds<int>{100});
  EXPECT_TRUE(cen::music::is_fading());

  cen::music::halt();
}

TEST_F(MusicTest, FadeOut)
{
  EXPECT_FALSE(cen::music::is_fading());

  EXPECT_NO_THROW(cen::music::fade_out(cen::milliseconds<int>{100}));
  EXPECT_NO_THROW(cen::music::fade_out(cen::milliseconds<int>{-1}));

  m_music->fade_in(cen::milliseconds<int>{100});
  EXPECT_TRUE(cen::music::is_fading());

  cen::music::halt();
}

TEST_F(MusicTest, SetVolume)
{
  const auto oldVolume = cen::music::volume();

  {  // Valid volume
    const auto volume = 102;
    cen::music::set_volume(volume);
    EXPECT_EQ(volume, cen::music::volume());
  }

  {  // Volume underflow
    const auto volume = -1;
    cen::music::set_volume(volume);
    EXPECT_EQ(0, cen::music::volume());
  }

  {  // Volume overflow
    const auto volume = cen::music::max_volume() + 1;
    cen::music::set_volume(volume);
    EXPECT_EQ(cen::music::max_volume(), cen::music::volume());
  }

  cen::music::set_volume(oldVolume);
}

TEST_F(MusicTest, IsPlaying)
{
  EXPECT_FALSE(cen::music::is_playing());

  m_music->play();
  EXPECT_TRUE(cen::music::is_playing());

  cen::music::halt();

  m_music->fade_in(cen::milliseconds<int>{100});
  EXPECT_TRUE(cen::music::is_playing());

  cen::music::halt();
}

TEST_F(MusicTest, IsPaused)
{
  m_music->play();
  EXPECT_FALSE(cen::music::is_paused());

  cen::music::pause();
  EXPECT_TRUE(cen::music::is_paused());
}

TEST_F(MusicTest, IsFading)
{
  EXPECT_FALSE(cen::music::is_fading());

  m_music->play();
  EXPECT_FALSE(cen::music::is_fading());

  cen::music::halt();

  m_music->fade_in(cen::milliseconds<int>{200});
  EXPECT_TRUE(cen::music::is_fading());

  // This should have no effect, since the music is fading in
  cen::music::fade_out(cen::milliseconds<int>{50});
  EXPECT_EQ(cen::fade_status::in, cen::music::get_fade_status());

  cen::music::halt();
}

TEST_F(MusicTest, Volume)
{
  EXPECT_EQ(cen::music::max_volume(), cen::music::volume());

  const auto volume = 47;
  cen::music::set_volume(volume);

  EXPECT_EQ(volume, cen::music::volume());
}

TEST_F(MusicTest, FadeStatus)
{
  EXPECT_EQ(cen::fade_status::none, cen::music::get_fade_status());
  EXPECT_FALSE(cen::music::is_fading());

  m_music->fade_in(cen::milliseconds<int>{100});
  EXPECT_EQ(cen::fade_status::in, cen::music::get_fade_status());
  EXPECT_TRUE(cen::music::is_fading());
  EXPECT_TRUE(cen::music::is_playing());
  EXPECT_FALSE(cen::music::is_paused());

  cen::music::halt();

  m_music->play();
  cen::music::fade_out(cen::milliseconds<int>{100});
  EXPECT_EQ(cen::fade_status::out, cen::music::get_fade_status());
  EXPECT_TRUE(cen::music::is_fading());
  EXPECT_TRUE(cen::music::is_playing());
  EXPECT_FALSE(cen::music::is_paused());

  cen::music::halt();
  EXPECT_EQ(cen::fade_status::none, cen::music::get_fade_status());
}

TEST_F(MusicTest, Type)
{
  EXPECT_EQ(cen::music_type::mp3, m_music->type());
}

TEST_F(MusicTest, ToString)
{
  cen::log::put(cen::to_string(*m_music));
}

TEST_F(MusicTest, StreamOperator)
{
  std::cout << "COUT: " << *m_music << '\n';
}

TEST_F(MusicTest, SDLPointerConversion)
{
  EXPECT_TRUE(static_cast<Mix_Music*>(*m_music));

  const auto& cMusic = *m_music;
  EXPECT_TRUE(static_cast<const Mix_Music*>(cMusic));
}

TEST_F(MusicTest, FadeStatusEnum)
{
  EXPECT_EQ(cen::fade_status::none, MIX_NO_FADING);
  EXPECT_EQ(cen::fade_status::in, MIX_FADING_IN);
  EXPECT_EQ(cen::fade_status::out, MIX_FADING_OUT);

  EXPECT_EQ(MIX_NO_FADING, cen::fade_status::none);
  EXPECT_EQ(MIX_FADING_IN, cen::fade_status::in);
  EXPECT_EQ(MIX_FADING_OUT, cen::fade_status::out);
}

TEST_F(MusicTest, MusicTypeEnum)
{
  EXPECT_EQ(cen::music_type::unknown, MUS_NONE);
  EXPECT_EQ(cen::music_type::mp3, MUS_MP3);
  EXPECT_EQ(cen::music_type::wav, MUS_WAV);
  EXPECT_EQ(cen::music_type::cmd, MUS_CMD);
  EXPECT_EQ(cen::music_type::mod, MUS_MOD);
  EXPECT_EQ(cen::music_type::ogg, MUS_OGG);
  EXPECT_EQ(cen::music_type::flac, MUS_FLAC);
  EXPECT_EQ(cen::music_type::midi, MUS_MID);
  EXPECT_EQ(cen::music_type::opus, MUS_OPUS);

  EXPECT_EQ(MUS_NONE, cen::music_type::unknown);
  EXPECT_EQ(MUS_MP3, cen::music_type::mp3);
  EXPECT_EQ(MUS_WAV, cen::music_type::wav);
  EXPECT_EQ(MUS_CMD, cen::music_type::cmd);
  EXPECT_EQ(MUS_MOD, cen::music_type::mod);
  EXPECT_EQ(MUS_OGG, cen::music_type::ogg);
  EXPECT_EQ(MUS_FLAC, cen::music_type::flac);
  EXPECT_EQ(MUS_MID, cen::music_type::midi);
  EXPECT_EQ(MUS_OPUS, cen::music_type::opus);
}
