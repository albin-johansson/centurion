#ifndef CENTURION_NOAUDIO
#include "music.hpp"

#include <catch.hpp>
#include <iostream>

#include "centurion_as_ctn.hpp"
#include "centurion_exception.hpp"
#include "log.hpp"

static inline constexpr auto* path = "resources/hiddenPond.mp3";

TEST_CASE("music::music(nn_czstring)", "[music]")
{
  CHECK_THROWS_AS(ctn::music{""}, ctn::mix_error);
  CHECK_NOTHROW(ctn::music{path});
}

TEST_CASE("music(music&&)", "[music]")
{
  ctn::music music{path};
  ctn::music other{std::move(music)};

  CHECK(!music.get());
  CHECK(other.get());
}

TEST_CASE("music::operator=(music&&)", "[music]")
{
  SECTION("Self-assignment")
  {
    ctn::music music{path};
    music = std::move(music);
    CHECK(music.get());
  }

  SECTION("Normal usage")
  {
    ctn::music music{path};
    ctn::music other{path};

    other = std::move(music);

    CHECK(!music.get());
    CHECK(other.get());
  }
}

TEST_CASE("music smart pointer factory methods", "[music]")
{
  CHECK_THROWS_AS(ctn::music::unique(""), ctn::mix_error);
  CHECK_THROWS_AS(ctn::music::unique(""), ctn::mix_error);
  CHECK_NOTHROW(ctn::music::unique(path));
  CHECK_NOTHROW(ctn::music::shared(path));
}

TEST_CASE("music::play", "[music]")
{
  ctn::music music{path};
  music.play();
  CHECK(ctn::music::is_playing());
  CHECK(!ctn::music::is_fading());
  CHECK(!ctn::music::is_paused());
  CHECK(ctn::music::get_fade_status() == ctn::fade_status::none);

  ctn::music::halt();

  music.play(ctn::music::loopForever);
  CHECK(ctn::music::is_playing());

  ctn::music::halt();
}

TEST_CASE("music::resume", "[music]")
{
  CHECK_NOTHROW(ctn::music::resume());

  ctn::music music{path};

  music.play();
  CHECK_NOTHROW(ctn::music::resume());

  ctn::music::pause();
  CHECK(ctn::music::is_paused());

  ctn::music::resume();
  CHECK(ctn::music::is_playing());

  ctn::music::halt();
  CHECK_NOTHROW(ctn::music::resume());
}

TEST_CASE("music::pause", "[music]")
{
  CHECK_NOTHROW(ctn::music::pause());

  ctn::music music{path};

  music.play();
  ctn::music::pause();
  CHECK(ctn::music::is_paused());

  music.fade_in(ctn::milliseconds<int>{100});
  ctn::music::pause();
  CHECK(ctn::music::is_paused());
}

TEST_CASE("music::halt", "[music]")
{
  CHECK_NOTHROW(ctn::music::halt());

  ctn::music music{path};

  music.play();
  ctn::music::halt();

  CHECK(!ctn::music::is_playing());
  CHECK(!ctn::music::is_fading());

  music.fade_in(ctn::milliseconds<int>{100});
  ctn::music::halt();

  CHECK(!ctn::music::is_playing());
  CHECK(!ctn::music::is_fading());
}

TEST_CASE("music::fade_in", "[music]")
{
  CHECK(!ctn::music::is_fading());

  ctn::music music{path};
  CHECK_NOTHROW(music.fade_in(ctn::milliseconds<int>{-1}));

  ctn::music::halt();

  music.fade_in(ctn::milliseconds<int>{100});
  CHECK(ctn::music::is_fading());
}

TEST_CASE("music::fade_out", "[music]")
{
  CHECK(!ctn::music::is_fading());
  CHECK_NOTHROW(ctn::music::fade_out(ctn::milliseconds<int>{100}));
  CHECK_NOTHROW(ctn::music::fade_out(ctn::milliseconds<int>{-1}));

  ctn::music music{path};
  music.fade_in(ctn::milliseconds<int>{100});

  CHECK(ctn::music::is_fading());
}

TEST_CASE("music::set_volume", "[music]")
{
  const auto originalVolume = ctn::music::volume();

  SECTION("Valid volume")
  {
    const auto volume = 102;
    ctn::music::set_volume(volume);
    CHECK(volume == ctn::music::volume());
  }

  SECTION("Negative volume")
  {
    const auto volume = -1;
    ctn::music::set_volume(volume);
    CHECK(ctn::music::volume() == 0);
  }

  SECTION("Volume overflow")
  {
    const auto volume = ctn::music::max_volume() + 1;
    ctn::music::set_volume(volume);
    CHECK(ctn::music::max_volume() == ctn::music::volume());
  }

  ctn::music::set_volume(originalVolume);
}

TEST_CASE("music::playing", "[music]")
{
  CHECK(!ctn::music::is_playing());

  ctn::music music{path};

  music.play();
  CHECK(ctn::music::is_playing());

  ctn::music::halt();

  music.fade_in(ctn::milliseconds<int>{100});
  CHECK(ctn::music::is_playing());
}

TEST_CASE("music::paused", "[music]")
{
  ctn::music music{path};
  music.play();

  ctn::music::pause();
  CHECK(ctn::music::is_paused());
}

TEST_CASE("music::fading", "[music]")
{
  CHECK(!ctn::music::is_fading());

  ctn::music music{path};

  music.play();
  CHECK(!ctn::music::is_fading());
  ctn::music::halt();

  music.fade_in(ctn::milliseconds<int>{200});
  CHECK(ctn::music::is_fading());

  // This should have no effect, since the music is fading in
  ctn::music::fade_out(ctn::milliseconds<int>{50});
  CHECK(ctn::music::get_fade_status() == ctn::fade_status::in);
}

TEST_CASE("music::volume", "[music]")
{
  CHECK(ctn::music::volume() == ctn::music::max_volume());

  const auto volume = 47;
  ctn::music::set_volume(volume);

  CHECK(ctn::music::volume() == volume);
}

TEST_CASE("music::fade_status", "[music]")
{
  CHECK(ctn::music::get_fade_status() == ctn::fade_status::none);
  CHECK(!ctn::music::is_fading());

  ctn::music music{path};

  music.fade_in(ctn::milliseconds<int>{100});
  CHECK(ctn::music::get_fade_status() == ctn::fade_status::in);
  CHECK(ctn::music::is_fading());
  CHECK(ctn::music::is_playing());
  CHECK(!ctn::music::is_paused());

  ctn::music::halt();

  music.play();
  ctn::music::fade_out(ctn::milliseconds<int>{100});
  CHECK(ctn::music::get_fade_status() == ctn::fade_status::out);
  CHECK(ctn::music::is_fading());
  CHECK(ctn::music::is_playing());
  CHECK(!ctn::music::is_paused());

  ctn::music::halt();
  CHECK(ctn::music::get_fade_status() == ctn::fade_status::none);
}

TEST_CASE("music::music_type", "[music]")
{
  ctn::music music{path};
  CHECK(music.type() == ctn::music_type::mp3);
}

TEST_CASE("music to_string", "[music]")
{
  const ctn::music music{path};
  ctn::log::put(ctn::to_string(music));
}

TEST_CASE("music stream operator", "[music]")
{
  const ctn::music music{path};
  std::cout << "COUT: " << music << '\n';
}

TEST_CASE("music to Mix_Music*", "[music]")
{
  ctn::music music{path};
  auto* sdlMusic = static_cast<Mix_Music*>(music);
  CHECK(sdlMusic);

  const ctn::music& cmusic = music;
  const auto* csdlMusic = static_cast<const Mix_Music*>(cmusic);
  CHECK(csdlMusic);
}

TEST_CASE("fade_status enum values", "[music]")
{
  CHECK(ctn::fade_status::none == MIX_NO_FADING);
  CHECK(ctn::fade_status::in == MIX_FADING_IN);
  CHECK(ctn::fade_status::out == MIX_FADING_OUT);

  CHECK(MIX_NO_FADING == ctn::fade_status::none);
  CHECK(MIX_FADING_IN == ctn::fade_status::in);
  CHECK(MIX_FADING_OUT == ctn::fade_status::out);
}

TEST_CASE("music_type enum values", "[music]")
{
  CHECK(ctn::music_type::unknown == MUS_NONE);
  CHECK(ctn::music_type::mp3 == MUS_MP3);
  CHECK(ctn::music_type::wav == MUS_WAV);
  CHECK(ctn::music_type::cmd == MUS_CMD);
  CHECK(ctn::music_type::mod == MUS_MOD);
  CHECK(ctn::music_type::ogg == MUS_OGG);
  CHECK(ctn::music_type::flac == MUS_FLAC);
  CHECK(ctn::music_type::midi == MUS_MID);
  CHECK(ctn::music_type::opus == MUS_OPUS);

  CHECK(MUS_NONE == ctn::music_type::unknown);
  CHECK(MUS_MP3 == ctn::music_type::mp3);
  CHECK(MUS_WAV == ctn::music_type::wav);
  CHECK(MUS_CMD == ctn::music_type::cmd);
  CHECK(MUS_MOD == ctn::music_type::mod);
  CHECK(MUS_OGG == ctn::music_type::ogg);
  CHECK(MUS_FLAC == ctn::music_type::flac);
  CHECK(MUS_MID == ctn::music_type::midi);
  CHECK(MUS_OPUS == ctn::music_type::opus);
}

#include "event.hpp"
#include "renderer.hpp"
#include "window.hpp"

TEST_CASE("Manual testing of music playback", "[.music]")
{
  ctn::window window;
  window.set_title("Centurion music test");

  ctn::renderer renderer{window};
  ctn::event event;

  ctn::music music{"resources/hiddenPond.mp3"};
  ctn::music click{"resources/click.wav"};

  const ctn::font font{"resources/fira_code.ttf", 14};

  renderer.set_color(ctn::colors::white);

  ctn::czstring zero = "\"0\" to play the click one time.";
  ctn::czstring one = "\"1\" to play the click one time.";
  ctn::czstring two = "\"2\" to play the click two times.";
  ctn::czstring nine = "\"9\" to play the click forever.";
  ctn::czstring fadeIn = "\"F\" to fade in the music over 5 seconds.";
  ctn::czstring esc = "\"ESC\" to halt the music.";

  const auto infoZero = renderer.render_blended_latin1(zero, font);
  const auto infoOne = renderer.render_blended_latin1(one, font);
  const auto infoTwo = renderer.render_blended_latin1(two, font);
  const auto infoNine = renderer.render_blended_latin1(nine, font);
  const auto infoFadeIn = renderer.render_blended_latin1(fadeIn, font);
  const auto infoEsc = renderer.render_blended_latin1(esc, font);

  renderer.set_color(ctn::colors::green);
  const auto playing =
      renderer.render_blended_latin1("music is playing!", font);

  renderer.set_color(ctn::colors::magenta);
  const auto fading = renderer.render_blended_latin1("music is fading!", font);

  renderer.set_color(ctn::colors::red);
  const auto paused =
      renderer.render_blended_latin1("No music is playing", font);

  bool running = true;
  window.show();
  while (running) {
    while (event.poll()) {
      if (event.is<ctn::quit_event>()) {
        running = false;
        break;
      } else if (const auto* key = event.try_get<ctn::keyboard_event>();
                 key && key->state() == ctn::button_state::released) {
        if (key->is_active(SDLK_0)) {
          click.play(0);

        } else if (key->is_active(SDLK_1)) {
          click.play(1);

        } else if (key->is_active(SDLK_2)) {
          click.play(2);

        } else if (key->is_active(SDLK_9)) {
          click.play(-1);

        } else if (key->is_active(SDLK_f)) {
          music.fade_in(ctn::seconds<int>{5});

        } else if (key->is_active(SDLK_ESCAPE)) {
          ctn::music::halt();
        }
      }
    }

    renderer.clear_with(ctn::colors::black);

    renderer.render(infoZero, ctn::ipoint{50, 50});
    renderer.render(infoOne, ctn::ipoint{50, 75});
    renderer.render(infoTwo, ctn::ipoint{50, 100});
    renderer.render(infoNine, ctn::ipoint{50, 125});
    renderer.render(infoFadeIn, ctn::ipoint{50, 150});
    renderer.render(infoEsc, ctn::ipoint{50, 175});

    if (ctn::music::is_playing() && !ctn::music::is_fading()) {
      renderer.render(playing, ctn::ipoint{300, 300});
    } else if (ctn::music::is_fading()) {
      renderer.render(fading, ctn::ipoint{300, 300});
    } else {
      renderer.render(paused, ctn::ipoint{300, 300});
    }

    renderer.present();
  }
  window.hide();
}

#endif