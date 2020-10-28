#include "music.hpp"

#include <catch.hpp>
#include <iostream>

#include "exception.hpp"
#include "log.hpp"

static inline constexpr auto* path = "resources/hiddenPond.mp3";

TEST_CASE("music::music(nn_czstring)", "[music]")
{
  CHECK_THROWS_AS(cen::music{""}, cen::mix_error);
  CHECK_NOTHROW(cen::music{path});
}

TEST_CASE("music(music&&)", "[music]")
{
  cen::music music{path};
  cen::music other{std::move(music)};

  CHECK(!music.get());
  CHECK(other.get());
}

TEST_CASE("music::operator=(music&&)", "[music]")
{
  SECTION("Self-assignment")
  {
    cen::music music{path};
    music = std::move(music);
    CHECK(music.get());
  }

  SECTION("Normal usage")
  {
    cen::music music{path};
    cen::music other{path};

    other = std::move(music);

    CHECK(!music.get());
    CHECK(other.get());
  }
}

TEST_CASE("music::play", "[music]")
{
  cen::music music{path};
  music.play();
  CHECK(cen::music::is_playing());
  CHECK(!cen::music::is_fading());
  CHECK(!cen::music::is_paused());
  CHECK(cen::music::get_fade_status() == cen::fade_status::none);

  cen::music::halt();

  music.play(cen::music::loopForever);
  CHECK(cen::music::is_playing());

  cen::music::halt();
}

TEST_CASE("music::resume", "[music]")
{
  CHECK_NOTHROW(cen::music::resume());

  cen::music music{path};

  music.play();
  CHECK_NOTHROW(cen::music::resume());

  cen::music::pause();
  CHECK(cen::music::is_paused());

  cen::music::resume();
  CHECK(cen::music::is_playing());

  cen::music::halt();
  CHECK_NOTHROW(cen::music::resume());
}

TEST_CASE("music::pause", "[music]")
{
  CHECK_NOTHROW(cen::music::pause());

  cen::music music{path};

  music.play();
  cen::music::pause();
  CHECK(cen::music::is_paused());

  music.fade_in(cen::milliseconds<int>{100});
  cen::music::pause();
  CHECK(cen::music::is_paused());
}

TEST_CASE("music::halt", "[music]")
{
  CHECK_NOTHROW(cen::music::halt());

  cen::music music{path};

  music.play();
  cen::music::halt();

  CHECK(!cen::music::is_playing());
  CHECK(!cen::music::is_fading());

  music.fade_in(cen::milliseconds<int>{100});
  cen::music::halt();

  CHECK(!cen::music::is_playing());
  CHECK(!cen::music::is_fading());
}

TEST_CASE("music::fade_in", "[music]")
{
  CHECK(!cen::music::is_fading());

  cen::music music{path};
  CHECK_NOTHROW(music.fade_in(cen::milliseconds<int>{-1}));

  cen::music::halt();

  music.fade_in(cen::milliseconds<int>{100});
  CHECK(cen::music::is_fading());
}

TEST_CASE("music::fade_out", "[music]")
{
  CHECK(!cen::music::is_fading());
  CHECK_NOTHROW(cen::music::fade_out(cen::milliseconds<int>{100}));
  CHECK_NOTHROW(cen::music::fade_out(cen::milliseconds<int>{-1}));

  cen::music music{path};
  music.fade_in(cen::milliseconds<int>{100});

  CHECK(cen::music::is_fading());
}

TEST_CASE("music::set_volume", "[music]")
{
  const auto originalVolume = cen::music::volume();

  SECTION("Valid volume")
  {
    const auto volume = 102;
    cen::music::set_volume(volume);
    CHECK(volume == cen::music::volume());
  }

  SECTION("Negative volume")
  {
    const auto volume = -1;
    cen::music::set_volume(volume);
    CHECK(cen::music::volume() == 0);
  }

  SECTION("Volume overflow")
  {
    const auto volume = cen::music::max_volume() + 1;
    cen::music::set_volume(volume);
    CHECK(cen::music::max_volume() == cen::music::volume());
  }

  cen::music::set_volume(originalVolume);
}

TEST_CASE("music::playing", "[music]")
{
  CHECK(!cen::music::is_playing());

  cen::music music{path};

  music.play();
  CHECK(cen::music::is_playing());

  cen::music::halt();

  music.fade_in(cen::milliseconds<int>{100});
  CHECK(cen::music::is_playing());
}

TEST_CASE("music::paused", "[music]")
{
  cen::music music{path};
  music.play();

  cen::music::pause();
  CHECK(cen::music::is_paused());
}

TEST_CASE("music::fading", "[music]")
{
  CHECK(!cen::music::is_fading());

  cen::music music{path};

  music.play();
  CHECK(!cen::music::is_fading());
  cen::music::halt();

  music.fade_in(cen::milliseconds<int>{200});
  CHECK(cen::music::is_fading());

  // This should have no effect, since the music is fading in
  cen::music::fade_out(cen::milliseconds<int>{50});
  CHECK(cen::music::get_fade_status() == cen::fade_status::in);
}

TEST_CASE("music::volume", "[music]")
{
  CHECK(cen::music::volume() == cen::music::max_volume());

  const auto volume = 47;
  cen::music::set_volume(volume);

  CHECK(cen::music::volume() == volume);
}

TEST_CASE("music::fade_status", "[music]")
{
  CHECK(cen::music::get_fade_status() == cen::fade_status::none);
  CHECK(!cen::music::is_fading());

  cen::music music{path};

  music.fade_in(cen::milliseconds<int>{100});
  CHECK(cen::music::get_fade_status() == cen::fade_status::in);
  CHECK(cen::music::is_fading());
  CHECK(cen::music::is_playing());
  CHECK(!cen::music::is_paused());

  cen::music::halt();

  music.play();
  cen::music::fade_out(cen::milliseconds<int>{100});
  CHECK(cen::music::get_fade_status() == cen::fade_status::out);
  CHECK(cen::music::is_fading());
  CHECK(cen::music::is_playing());
  CHECK(!cen::music::is_paused());

  cen::music::halt();
  CHECK(cen::music::get_fade_status() == cen::fade_status::none);
}

TEST_CASE("music::music_type", "[music]")
{
  cen::music music{path};
  CHECK(music.type() == cen::music_type::mp3);
}

TEST_CASE("music to_string", "[music]")
{
  const cen::music music{path};
  cen::log::put(cen::to_string(music));
}

TEST_CASE("music stream operator", "[music]")
{
  const cen::music music{path};
  std::cout << "COUT: " << music << '\n';
}

TEST_CASE("music to Mix_Music*", "[music]")
{
  cen::music music{path};
  auto* sdlMusic = static_cast<Mix_Music*>(music);
  CHECK(sdlMusic);

  const cen::music& cmusic = music;
  const auto* csdlMusic = static_cast<const Mix_Music*>(cmusic);
  CHECK(csdlMusic);
}

TEST_CASE("fade_status enum values", "[music]")
{
  CHECK(cen::fade_status::none == MIX_NO_FADING);
  CHECK(cen::fade_status::in == MIX_FADING_IN);
  CHECK(cen::fade_status::out == MIX_FADING_OUT);

  CHECK(MIX_NO_FADING == cen::fade_status::none);
  CHECK(MIX_FADING_IN == cen::fade_status::in);
  CHECK(MIX_FADING_OUT == cen::fade_status::out);
}

TEST_CASE("music_type enum values", "[music]")
{
  CHECK(cen::music_type::unknown == MUS_NONE);
  CHECK(cen::music_type::mp3 == MUS_MP3);
  CHECK(cen::music_type::wav == MUS_WAV);
  CHECK(cen::music_type::cmd == MUS_CMD);
  CHECK(cen::music_type::mod == MUS_MOD);
  CHECK(cen::music_type::ogg == MUS_OGG);
  CHECK(cen::music_type::flac == MUS_FLAC);
  CHECK(cen::music_type::midi == MUS_MID);
  CHECK(cen::music_type::opus == MUS_OPUS);

  CHECK(MUS_NONE == cen::music_type::unknown);
  CHECK(MUS_MP3 == cen::music_type::mp3);
  CHECK(MUS_WAV == cen::music_type::wav);
  CHECK(MUS_CMD == cen::music_type::cmd);
  CHECK(MUS_MOD == cen::music_type::mod);
  CHECK(MUS_OGG == cen::music_type::ogg);
  CHECK(MUS_FLAC == cen::music_type::flac);
  CHECK(MUS_MID == cen::music_type::midi);
  CHECK(MUS_OPUS == cen::music_type::opus);
}

#include "event.hpp"
#include "renderer.hpp"
#include "window.hpp"

TEST_CASE("Manual testing of music playback", "[.music]")
{
  cen::window window;
  window.set_title("Centurion music test");

  cen::renderer renderer{window};
  cen::event event;

  cen::music music{"resources/hiddenPond.mp3"};
  cen::music click{"resources/click.wav"};

  const cen::font font{"resources/fira_code.ttf", 14};

  renderer.set_color(cen::colors::white);

  cen::czstring zero = "\"0\" to play the click one time.";
  cen::czstring one = "\"1\" to play the click one time.";
  cen::czstring two = "\"2\" to play the click two times.";
  cen::czstring nine = "\"9\" to play the click forever.";
  cen::czstring fadeIn = "\"F\" to fade in the music over 5 seconds.";
  cen::czstring esc = "\"ESC\" to halt the music.";

  const auto infoZero = renderer.render_blended_latin1(zero, font);
  const auto infoOne = renderer.render_blended_latin1(one, font);
  const auto infoTwo = renderer.render_blended_latin1(two, font);
  const auto infoNine = renderer.render_blended_latin1(nine, font);
  const auto infoFadeIn = renderer.render_blended_latin1(fadeIn, font);
  const auto infoEsc = renderer.render_blended_latin1(esc, font);

  renderer.set_color(cen::colors::green);
  const auto playing =
      renderer.render_blended_latin1("music is playing!", font);

  renderer.set_color(cen::colors::magenta);
  const auto fading = renderer.render_blended_latin1("music is fading!", font);

  renderer.set_color(cen::colors::red);
  const auto paused =
      renderer.render_blended_latin1("No music is playing", font);

  bool running = true;
  window.show();
  while (running) {
    while (event.poll()) {
      if (event.is<cen::quit_event>()) {
        running = false;
        break;
      } else if (const auto* key = event.try_get<cen::keyboard_event>();
                 key && key->state() == cen::button_state::released) {
        if (key->is_active(SDLK_0)) {
          click.play(0);

        } else if (key->is_active(SDLK_1)) {
          click.play(1);

        } else if (key->is_active(SDLK_2)) {
          click.play(2);

        } else if (key->is_active(SDLK_9)) {
          click.play(-1);

        } else if (key->is_active(SDLK_f)) {
          music.fade_in(cen::seconds<int>{5});

        } else if (key->is_active(SDLK_ESCAPE)) {
          cen::music::halt();
        }
      }
    }

    renderer.clear_with(cen::colors::black);

    renderer.render(infoZero, cen::ipoint{50, 50});
    renderer.render(infoOne, cen::ipoint{50, 75});
    renderer.render(infoTwo, cen::ipoint{50, 100});
    renderer.render(infoNine, cen::ipoint{50, 125});
    renderer.render(infoFadeIn, cen::ipoint{50, 150});
    renderer.render(infoEsc, cen::ipoint{50, 175});

    if (cen::music::is_playing() && !cen::music::is_fading()) {
      renderer.render(playing, cen::ipoint{300, 300});
    } else if (cen::music::is_fading()) {
      renderer.render(fading, cen::ipoint{300, 300});
    } else {
      renderer.render(paused, cen::ipoint{300, 300});
    }

    renderer.present();
  }
  window.hide();
}
