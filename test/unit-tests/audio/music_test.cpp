#include "audio/music.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout
#include <memory>    // unique_ptr
#include <type_traits>

#include "core/log.hpp"

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
    using namespace std::string_literals;
    m_music = std::make_unique<cen::music>("resources/hiddenPond.mp3"s);
  }

  static void TearDownTestSuite()
  {
    m_music.reset();
  }

  inline static std::unique_ptr<cen::music> m_music;
};

TEST_F(MusicTest, Forever)
{
  ASSERT_EQ(-1, cen::music::forever);
}

TEST_F(MusicTest, Constructor)
{
  using namespace std::string_literals;
  ASSERT_THROW(cen::music{"foobar"s}, cen::mix_error);
}

TEST_F(MusicTest, Play)
{
  m_music->play();
  ASSERT_TRUE(cen::music::is_playing());
  ASSERT_FALSE(cen::music::is_fading());
  ASSERT_FALSE(cen::music::is_paused());
  ASSERT_EQ(cen::fade_status::none, cen::music::get_fade_status());

  cen::music::halt();

  m_music->play(cen::music::forever);
  ASSERT_TRUE(cen::music::is_playing());
  ASSERT_FALSE(cen::music::is_fading());
  ASSERT_FALSE(cen::music::is_paused());
  ASSERT_EQ(cen::fade_status::none, cen::music::get_fade_status());

  m_music->pause();
  cen::music::halt();
}

TEST_F(MusicTest, Resume)
{
  ASSERT_NO_THROW(cen::music::resume());

  m_music->play();
  ASSERT_NO_THROW(cen::music::resume());

  cen::music::pause();
  ASSERT_TRUE(cen::music::is_paused());

  cen::music::resume();
  ASSERT_TRUE(cen::music::is_playing());

  cen::music::halt();
  ASSERT_NO_THROW(cen::music::resume());
}

TEST_F(MusicTest, Pause)
{
  ASSERT_NO_THROW(cen::music::pause());

  m_music->play();

  cen::music::pause();
  ASSERT_TRUE(cen::music::is_paused());

  m_music->fade_in(cen::milliseconds<int>{100});

  cen::music::pause();
  ASSERT_TRUE(cen::music::is_paused());
}

TEST_F(MusicTest, Halt)
{
  ASSERT_NO_THROW(cen::music::halt());

  m_music->play();
  cen::music::halt();

  ASSERT_FALSE(cen::music::is_playing());
  ASSERT_FALSE(cen::music::is_fading());

  m_music->fade_in(cen::milliseconds<int>{100});
  cen::music::halt();

  ASSERT_FALSE(cen::music::is_playing());
  ASSERT_FALSE(cen::music::is_fading());
}

TEST_F(MusicTest, FadeIn)
{
  ASSERT_FALSE(cen::music::is_fading());

  cen::music::halt();

  m_music->fade_in(cen::milliseconds<int>{100});
  ASSERT_TRUE(cen::music::is_fading());

  cen::music::halt();
}

TEST_F(MusicTest, FadeOut)
{
  ASSERT_FALSE(cen::music::is_fading());

  ASSERT_NO_THROW(cen::music::fade_out(cen::milliseconds<int>{100}));

  m_music->fade_in(cen::milliseconds<int>{100});
  ASSERT_TRUE(cen::music::is_fading());

  cen::music::halt();
}

TEST_F(MusicTest, SetVolume)
{
  const auto oldVolume = cen::music::volume();

  {  // Valid volume
    const auto volume = 102;
    cen::music::set_volume(volume);
    ASSERT_EQ(volume, cen::music::volume());
  }

  {  // Volume underflow
    const auto volume = -1;
    cen::music::set_volume(volume);
    ASSERT_EQ(0, cen::music::volume());
  }

  {  // Volume overflow
    const auto volume = cen::music::max_volume() + 1;
    cen::music::set_volume(volume);
    ASSERT_EQ(cen::music::max_volume(), cen::music::volume());
  }

  cen::music::set_volume(oldVolume);
}

TEST_F(MusicTest, IsPlaying)
{
  ASSERT_FALSE(cen::music::is_playing());

  m_music->play();
  ASSERT_TRUE(cen::music::is_playing());

  cen::music::halt();

  m_music->fade_in(cen::milliseconds<int>{100});
  ASSERT_TRUE(cen::music::is_playing());

  cen::music::halt();
}

TEST_F(MusicTest, IsPaused)
{
  m_music->play();
  ASSERT_FALSE(cen::music::is_paused());

  cen::music::pause();
  ASSERT_TRUE(cen::music::is_paused());
}

TEST_F(MusicTest, IsFading)
{
  ASSERT_FALSE(cen::music::is_fading());

  m_music->play();
  ASSERT_FALSE(cen::music::is_fading());

  cen::music::halt();

  m_music->fade_in(cen::milliseconds<int>{200});
  ASSERT_TRUE(cen::music::is_fading());

  // This should have no effect, since the music is fading in
  cen::music::fade_out(cen::milliseconds<int>{50});
  ASSERT_EQ(cen::fade_status::in, cen::music::get_fade_status());

  cen::music::halt();
}

TEST_F(MusicTest, Volume)
{
  ASSERT_EQ(cen::music::max_volume(), cen::music::volume());

  const auto volume = 47;
  cen::music::set_volume(volume);

  ASSERT_EQ(volume, cen::music::volume());
}

TEST_F(MusicTest, FadeStatus)
{
  ASSERT_EQ(cen::fade_status::none, cen::music::get_fade_status());
  ASSERT_FALSE(cen::music::is_fading());

  m_music->fade_in(cen::milliseconds<int>{100});
  ASSERT_EQ(cen::fade_status::in, cen::music::get_fade_status());
  ASSERT_TRUE(cen::music::is_fading());
  ASSERT_TRUE(cen::music::is_playing());
  ASSERT_FALSE(cen::music::is_paused());

  cen::music::halt();

  m_music->play();
  cen::music::fade_out(cen::milliseconds<int>{100});
  ASSERT_EQ(cen::fade_status::out, cen::music::get_fade_status());
  ASSERT_TRUE(cen::music::is_fading());
  ASSERT_TRUE(cen::music::is_playing());
  ASSERT_FALSE(cen::music::is_paused());

  cen::music::halt();
  ASSERT_EQ(cen::fade_status::none, cen::music::get_fade_status());
}

TEST_F(MusicTest, Type)
{
  ASSERT_EQ(cen::music_type::mp3, m_music->type());
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
  ASSERT_TRUE(static_cast<Mix_Music*>(*m_music));

  const auto& cMusic = *m_music;
  ASSERT_TRUE(static_cast<const Mix_Music*>(cMusic));
}

TEST_F(MusicTest, FadeStatusEnum)
{
  ASSERT_EQ(cen::fade_status::none, MIX_NO_FADING);
  ASSERT_EQ(cen::fade_status::in, MIX_FADING_IN);
  ASSERT_EQ(cen::fade_status::out, MIX_FADING_OUT);

  ASSERT_EQ(MIX_NO_FADING, cen::fade_status::none);
  ASSERT_EQ(MIX_FADING_IN, cen::fade_status::in);
  ASSERT_EQ(MIX_FADING_OUT, cen::fade_status::out);
}

TEST_F(MusicTest, MusicTypeEnum)
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
}
