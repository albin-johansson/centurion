#include "audio/sound_effect.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout
#include <memory>    // unique_ptr
#include <type_traits>

#include "misc/exception.hpp"
#include "misc/log.hpp"

static_assert(std::is_final_v<cen::sound_effect>);
static_assert(!std::is_default_constructible_v<cen::sound_effect>);

static_assert(std::is_nothrow_move_constructible_v<cen::sound_effect>);
static_assert(std::is_nothrow_move_assignable_v<cen::sound_effect>);

static_assert(!std::is_copy_constructible_v<cen::sound_effect>);
static_assert(!std::is_copy_assignable_v<cen::sound_effect>);

using ms = cen::milliseconds<int>;

inline constexpr auto path = "resources/click.wav";

class SoundEffect : public testing::Test
{
 protected:
  static void SetUpTestSuite()
  {
    m_sound = std::make_unique<cen::sound_effect>(path);
  }

  static void TearDownTestSuite()
  {
    m_sound.reset();
  }

  inline static std::unique_ptr<cen::sound_effect> m_sound;
};

TEST_F(SoundEffect, Constructor)
{
  EXPECT_THROW(cen::sound_effect("foobar"), cen::mix_error);

  using namespace std::string_literals;
  EXPECT_THROW(cen::sound_effect("foobar"s), cen::mix_error);
}

TEST_F(SoundEffect, PlayAndStop)
{
  EXPECT_FALSE(m_sound->is_playing());

  m_sound->play();
  EXPECT_TRUE(m_sound->is_playing());

  m_sound->stop();
  EXPECT_FALSE(m_sound->is_playing());

  m_sound->play(5);
  EXPECT_TRUE(m_sound->is_playing());

  m_sound->stop();
}

TEST_F(SoundEffect, Looping)
{
  const auto oldVolume = m_sound->volume();

  m_sound->set_volume(1);

  m_sound->play(10);
  EXPECT_TRUE(m_sound->is_playing());

  m_sound->stop();

  EXPECT_LT(cen::sound_effect::forever, 0);
  EXPECT_NO_THROW(m_sound->play(cen::sound_effect::forever));

  EXPECT_TRUE(m_sound->is_playing());

  m_sound->stop();
  EXPECT_FALSE(m_sound->is_playing());

  m_sound->set_volume(oldVolume);
}

TEST_F(SoundEffect, FadeIn)
{
  m_sound->stop();

  EXPECT_FALSE(m_sound->is_fading());
  EXPECT_FALSE(m_sound->is_playing());

  m_sound->fade_in(ms{100});
  EXPECT_TRUE(m_sound->is_fading());
  EXPECT_TRUE(m_sound->is_playing());

  m_sound->stop();
}

TEST_F(SoundEffect, FadeOut)
{
  EXPECT_FALSE(m_sound->is_playing());

  m_sound->play();
  m_sound->fade_out(ms{5});
  EXPECT_TRUE(m_sound->is_fading());
  EXPECT_TRUE(m_sound->is_playing());

  m_sound->stop();
  EXPECT_FALSE(m_sound->is_fading());
  EXPECT_FALSE(m_sound->is_playing());
}

TEST_F(SoundEffect, SetVolume)
{
  const auto oldVolume = m_sound->volume();

  {  // Valid volume
    const auto volume = 27;
    m_sound->set_volume(volume);
    EXPECT_EQ(volume, m_sound->volume());
  }

  {  // Volume underflow
    const auto volume = -1;
    m_sound->set_volume(volume);
    EXPECT_EQ(0, m_sound->volume());
  }

  {  // Volume overflow
    const auto volume = cen::sound_effect::max_volume() + 1;
    m_sound->set_volume(volume);
    EXPECT_EQ(cen::sound_effect::max_volume(), m_sound->volume());
  }

  m_sound->set_volume(oldVolume);
}

TEST_F(SoundEffect, Volume)
{
  EXPECT_EQ(cen::sound_effect::max_volume(), m_sound->volume());
  EXPECT_EQ(128, m_sound->volume());  // because of the documentation guarantee
  EXPECT_EQ(MIX_MAX_VOLUME, cen::sound_effect::max_volume());
}

TEST_F(SoundEffect, ToString)
{
  cen::log::put(cen::to_string(*m_sound));
}

TEST_F(SoundEffect, StreamOperator)
{
  std::cout << "COUT: " << *m_sound << '\n';
}

TEST_F(SoundEffect, Forever)
{
  EXPECT_EQ(-1, cen::sound_effect::forever);
}

TEST_F(SoundEffect, MaxVolume)
{
  EXPECT_EQ(MIX_MAX_VOLUME, cen::sound_effect::max_volume());
}
