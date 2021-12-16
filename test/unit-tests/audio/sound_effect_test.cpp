#include <gtest/gtest.h>

#include <iostream>  // clog
#include <memory>    // unique_ptr
#include <type_traits>

#include "audio.hpp"
#include "core/exception.hpp"

static_assert(std::is_final_v<cen::SoundEffect>);
static_assert(!std::is_default_constructible_v<cen::SoundEffect>);

static_assert(std::is_nothrow_move_constructible_v<cen::SoundEffect>);
static_assert(std::is_nothrow_move_assignable_v<cen::SoundEffect>);

static_assert(!std::is_copy_constructible_v<cen::SoundEffect>);
static_assert(!std::is_copy_assignable_v<cen::SoundEffect>);

using ms = cen::Millis<int>;

inline constexpr auto path = "resources/click.wav";

class SoundEffect : public testing::Test {
 protected:
  static void SetUpTestSuite() { sound = std::make_unique<cen::SoundEffect>(path); }

  static void TearDownTestSuite() { sound.reset(); }

  inline static std::unique_ptr<cen::SoundEffect> sound;
};

TEST_F(SoundEffect, Constructor)
{
  ASSERT_THROW(cen::SoundEffect("foobar"), cen::MixError);

  using namespace std::string_literals;
  ASSERT_THROW(cen::SoundEffect("foobar"s), cen::MixError);
}

TEST_F(SoundEffect, PlayAndStop)
{
  ASSERT_FALSE(sound->IsPlaying());

  sound->Play();
  ASSERT_TRUE(sound->IsPlaying());

  sound->Stop();
  ASSERT_FALSE(sound->IsPlaying());

  sound->Play(5);
  ASSERT_TRUE(sound->IsPlaying());

  sound->Stop();
}

TEST_F(SoundEffect, Looping)
{
  const auto oldVolume = sound->GetVolume();

  sound->SetVolume(1);

  sound->Play(10);
  ASSERT_TRUE(sound->IsPlaying());

  sound->Stop();

  ASSERT_LT(cen::SoundEffect::forever, 0);
  ASSERT_NO_THROW(sound->Play(cen::SoundEffect::forever));

  ASSERT_TRUE(sound->IsPlaying());

  sound->Stop();
  ASSERT_FALSE(sound->IsPlaying());

  sound->SetVolume(oldVolume);
}

TEST_F(SoundEffect, FadeIn)
{
  sound->Stop();

  ASSERT_FALSE(sound->IsFading());
  ASSERT_FALSE(sound->IsPlaying());

  sound->FadeIn(ms{100});
  ASSERT_TRUE(sound->IsFading());
  ASSERT_TRUE(sound->IsPlaying());

  sound->Stop();
}

TEST_F(SoundEffect, FadeOut)
{
  ASSERT_FALSE(sound->IsPlaying());

  sound->Play();
  sound->FadeOut(ms{5});
  ASSERT_TRUE(sound->IsFading());
  ASSERT_TRUE(sound->IsPlaying());

  sound->Stop();
  ASSERT_FALSE(sound->IsFading());
  ASSERT_FALSE(sound->IsPlaying());
}

TEST_F(SoundEffect, SetVolume)
{
  const auto oldVolume = sound->GetVolume();

  {  // Valid volume
    const auto volume = 27;
    sound->SetVolume(volume);
    ASSERT_EQ(volume, sound->GetVolume());
  }

  {  // Volume underflow
    const auto volume = -1;
    sound->SetVolume(volume);
    ASSERT_EQ(0, sound->GetVolume());
  }

  {  // Volume overflow
    const auto volume = cen::SoundEffect::GetMaxVolume() + 1;
    sound->SetVolume(volume);
    ASSERT_EQ(cen::SoundEffect::GetMaxVolume(), sound->GetVolume());
  }

  sound->SetVolume(oldVolume);
}

TEST_F(SoundEffect, GetVolume)
{
  ASSERT_EQ(cen::SoundEffect::GetMaxVolume(), sound->GetVolume());
  ASSERT_EQ(128, sound->GetVolume());  // because of the documentation guarantee
  ASSERT_EQ(MIX_MAX_VOLUME, cen::SoundEffect::GetMaxVolume());
}

TEST_F(SoundEffect, Forever)
{
  ASSERT_EQ(-1, cen::SoundEffect::forever);
}

TEST_F(SoundEffect, GetMaxVolume)
{
  ASSERT_EQ(MIX_MAX_VOLUME, cen::SoundEffect::GetMaxVolume());
}
