#include <gtest/gtest.h>

#include <iostream>     // clog
#include <memory>       // unique_ptr
#include <type_traits>  // ...

#include "audio.hpp"
#include "core/logging.hpp"

static_assert(std::is_final_v<cen::Music>);

static_assert(!std::is_nothrow_copy_constructible_v<cen::Music>);
static_assert(!std::is_nothrow_copy_assignable_v<cen::Music>);

static_assert(std::is_nothrow_move_constructible_v<cen::Music>);
static_assert(std::is_nothrow_move_assignable_v<cen::Music>);

class MusicTest : public testing::Test {
 protected:
  static void SetUpTestSuite()
  {
    music = std::make_unique<cen::Music>("resources/hiddenPond.mp3");
  }

  static void TearDownTestSuite() { music.reset(); }

  inline static std::unique_ptr<cen::Music> music;
};

TEST_F(MusicTest, Forever)
{
  ASSERT_EQ(-1, cen::Music::forever);
}

TEST_F(MusicTest, Constructor)
{
  using namespace std::string_literals;
  ASSERT_THROW(cen::Music{"foobar"s}, cen::MixError);
}

TEST_F(MusicTest, Play)
{
  music->Play();
  ASSERT_TRUE(cen::Music::IsPlaying());
  ASSERT_FALSE(cen::Music::IsFading());
  ASSERT_FALSE(cen::Music::IsPaused());
  ASSERT_EQ(cen::FadeStatus::None, cen::Music::GetFadeStatus());

  cen::Music::Halt();

  music->Play(cen::Music::forever);
  ASSERT_TRUE(cen::Music::IsPlaying());
  ASSERT_FALSE(cen::Music::IsFading());
  ASSERT_FALSE(cen::Music::IsPaused());
  ASSERT_EQ(cen::FadeStatus::None, cen::Music::GetFadeStatus());

  music->Pause();
  cen::Music::Halt();
}

TEST_F(MusicTest, Resume)
{
  ASSERT_NO_THROW(cen::Music::Resume());

  music->Play();
  ASSERT_NO_THROW(cen::Music::Resume());

  cen::Music::Pause();
  ASSERT_TRUE(cen::Music::IsPaused());

  cen::Music::Resume();
  ASSERT_TRUE(cen::Music::IsPlaying());

  cen::Music::Halt();
  ASSERT_NO_THROW(cen::Music::Resume());
}

TEST_F(MusicTest, Pause)
{
  ASSERT_NO_THROW(cen::Music::Pause());

  music->Play();

  cen::Music::Pause();
  ASSERT_TRUE(cen::Music::IsPaused());

  music->FadeIn(cen::Millis<int>{100});

  cen::Music::Pause();
  ASSERT_TRUE(cen::Music::IsPaused());
}

TEST_F(MusicTest, Halt)
{
  ASSERT_NO_THROW(cen::Music::Halt());

  music->Play();
  cen::Music::Halt();

  ASSERT_FALSE(cen::Music::IsPlaying());
  ASSERT_FALSE(cen::Music::IsFading());

  music->FadeIn(cen::Millis<int>{100});
  cen::Music::Halt();

  ASSERT_FALSE(cen::Music::IsPlaying());
  ASSERT_FALSE(cen::Music::IsFading());
}

TEST_F(MusicTest, FadeIn)
{
  ASSERT_FALSE(cen::Music::IsFading());

  cen::Music::Halt();

  music->FadeIn(cen::Millis<int>{100});
  ASSERT_TRUE(cen::Music::IsFading());

  cen::Music::Halt();
}

TEST_F(MusicTest, FadeOut)
{
  ASSERT_FALSE(cen::Music::IsFading());

  ASSERT_NO_THROW(cen::Music::FadeOut(cen::Millis<int>{100}));

  music->FadeIn(cen::Millis<int>{100});
  ASSERT_TRUE(cen::Music::IsFading());

  cen::Music::Halt();
}

TEST_F(MusicTest, SetVolume)
{
  const auto oldVolume = cen::Music::GetVolume();

  {  // Valid GetVolume
    const auto volume = 102;
    cen::Music::SetVolume(volume);
    ASSERT_EQ(volume, cen::Music::GetVolume());
  }

  {  // Volume underflow
    const auto volume = -1;
    cen::Music::SetVolume(volume);
    ASSERT_EQ(0, cen::Music::GetVolume());
  }

  {  // Volume overflow
    const auto volume = cen::Music::GetMaxVolume() + 1;
    cen::Music::SetVolume(volume);
    ASSERT_EQ(cen::Music::GetMaxVolume(), cen::Music::GetVolume());
  }

  cen::Music::SetVolume(oldVolume);
}

TEST_F(MusicTest, IsPlaying)
{
  ASSERT_FALSE(cen::Music::IsPlaying());

  music->Play();
  ASSERT_TRUE(cen::Music::IsPlaying());

  cen::Music::Halt();

  music->FadeIn(cen::Millis<int>{100});
  ASSERT_TRUE(cen::Music::IsPlaying());

  cen::Music::Halt();
}

TEST_F(MusicTest, IsPaused)
{
  music->Play();
  ASSERT_FALSE(cen::Music::IsPaused());

  cen::Music::Pause();
  ASSERT_TRUE(cen::Music::IsPaused());
}

TEST_F(MusicTest, IsFading)
{
  ASSERT_FALSE(cen::Music::IsFading());

  music->Play();
  ASSERT_FALSE(cen::Music::IsFading());

  cen::Music::Halt();

  music->FadeIn(cen::Millis<int>{200});
  ASSERT_TRUE(cen::Music::IsFading());

  // This should have no effect, since the Music is fading in
  cen::Music::FadeOut(cen::Millis<int>{50});
  ASSERT_EQ(cen::FadeStatus::In, cen::Music::GetFadeStatus());

  cen::Music::Halt();
}

TEST_F(MusicTest, Volume)
{
  ASSERT_EQ(cen::Music::GetMaxVolume(), cen::Music::GetVolume());

  const auto GetVolume = 47;
  cen::Music::SetVolume(GetVolume);

  ASSERT_EQ(GetVolume, cen::Music::GetVolume());
}

TEST_F(MusicTest, FadeStatus)
{
  ASSERT_EQ(cen::FadeStatus::None, cen::Music::GetFadeStatus());
  ASSERT_FALSE(cen::Music::IsFading());

  music->FadeIn(cen::Millis<int>{100});
  ASSERT_EQ(cen::FadeStatus::In, cen::Music::GetFadeStatus());
  ASSERT_TRUE(cen::Music::IsFading());
  ASSERT_TRUE(cen::Music::IsPlaying());
  ASSERT_FALSE(cen::Music::IsPaused());

  cen::Music::Halt();

  music->Play();
  cen::Music::FadeOut(cen::Millis<int>{100});
  ASSERT_EQ(cen::FadeStatus::Out, cen::Music::GetFadeStatus());
  ASSERT_TRUE(cen::Music::IsFading());
  ASSERT_TRUE(cen::Music::IsPlaying());
  ASSERT_FALSE(cen::Music::IsPaused());

  cen::Music::Halt();
  ASSERT_EQ(cen::FadeStatus::None, cen::Music::GetFadeStatus());
}

TEST_F(MusicTest, Type)
{
  ASSERT_EQ(cen::MusicType::MP3, music->GetType());
}
