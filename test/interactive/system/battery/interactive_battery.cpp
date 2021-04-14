#include "centurion.hpp"

namespace {

inline constexpr auto msg_existence = "Does the system have a battery? ";
inline constexpr auto msg_charged = "Is battery charged? ";
inline constexpr auto msg_charging = "Is battery currently charging? ";
inline constexpr auto msg_available = "Is battery available? ";

inline constexpr auto msg_power = "Battery percentage: ";
inline constexpr auto msg_minutes = "Minutes remaining: ";
inline constexpr auto msg_seconds = "Seconds remaining: ";

inline constexpr auto msg_state = "Current battery state: ";
inline constexpr auto msg_state_unknown = "unknown";
inline constexpr auto msg_state_on_battery = "on_battery";
inline constexpr auto msg_state_no_battery = "no_battery";
inline constexpr auto msg_state_charging = "charging";
inline constexpr auto msg_state_charged = "charged";

inline constexpr auto id_no = 0;
inline constexpr auto id_yes = 1;
inline constexpr auto id_none = 2;

inline constexpr auto id_existence = 10;
inline constexpr auto id_charged = 11;
inline constexpr auto id_charging = 12;
inline constexpr auto id_available = 13;
inline constexpr auto id_state = 14;

inline constexpr auto id_power = 21;
inline constexpr auto id_minutes = 22;
inline constexpr auto id_seconds = 23;

inline constexpr auto id_state_unknown = 30;
inline constexpr auto id_state_on_battery = 31;
inline constexpr auto id_state_no_battery = 32;
inline constexpr auto id_state_charging = 33;
inline constexpr auto id_state_charged = 34;

inline constexpr auto answer_x = 500;

inline constexpr cen::iarea window_size{700, 350};

[[nodiscard]] auto get_id(const cen::power_state state)
{
  switch (state)
  {
    default:
      [[fallthrough]];

    case cen::power_state::unknown:
      return id_state_unknown;

    case cen::power_state::on_battery:
      return id_state_on_battery;

    case cen::power_state::no_battery:
      return id_state_no_battery;

    case cen::power_state::charging:
      return id_state_charging;

    case cen::power_state::charged:
      return id_state_charged;
  }
};

class battery_demo final
{
 public:
  battery_demo()
      : m_window{"Battery demo", window_size}
      , m_renderer{m_window}
      , m_cache{"resources/fira_code.ttf", 24}
  {
    m_renderer.set_color(cen::colors::white);
    m_cache.add_latin1(m_renderer);

    const auto store = [this](auto id, auto msg) {
      m_cache.store_blended_utf8(id, msg, m_renderer);
    };

    store(id_no, "No");
    store(id_yes, "Yes");
    store(id_none, "N/A");
    store(id_existence, msg_existence);
    store(id_charged, msg_charged);
    store(id_charging, msg_charging);
    store(id_available, msg_available);
    store(id_power, msg_power);
    store(id_minutes, msg_minutes);
    store(id_seconds, msg_seconds);
    store(id_state, msg_state);
    store(id_state_unknown, msg_state_unknown);
    store(id_state_on_battery, msg_state_on_battery);
    store(id_state_no_battery, msg_state_no_battery);
    store(id_state_charging, msg_state_charging);
    store(id_state_charged, msg_state_charged);
  }

  auto run() -> int
  {
    m_window.show();

    cen::event event;
    while (m_running)
    {
      while (event.poll())
      {
        if (event.is<cen::quit_event>())
        {
          m_running = false;
          break;
        }
      }

      render();
    }

    m_window.hide();

    return 0;
  }

 private:
  cen::window m_window;
  cen::renderer m_renderer;
  cen::font_cache m_cache;
  bool m_running{true};

  void render()
  {
    m_renderer.clear_with(cen::colors::light_coral);

    auto nextY = [y = 10]() mutable {
      const auto tmp = y;
      y += 30;
      return tmp;
    };

    render_yes_no_answer(id_existence, cen::battery::exists(), nextY());

    nextY();
    constexpr auto null = std::optional<int>{};
    const auto minutes = cen::battery::minutes_left();
    const auto seconds = cen::battery::seconds_left();
    render_value(id_power, cen::battery::percentage(), nextY());
    render_value(id_minutes, minutes ? minutes->count() : null, nextY());
    render_value(id_seconds, seconds ? seconds->count() : null, nextY());

    nextY();
    render_text_pair(id_state, get_id(cen::battery::state()), nextY());
    render_yes_no_answer(id_available, cen::battery::is_available(), nextY());
    render_yes_no_answer(id_charging, cen::battery::is_charging(), nextY());
    render_yes_no_answer(id_charged, cen::battery::is_charged(), nextY());

    m_renderer.present();
  }

  void render_text_pair(const int firstId, const int secondId, const int y)
  {
    m_renderer.render(m_cache.get_stored(firstId), cen::point(10, y));
    m_renderer.render(m_cache.get_stored(secondId), cen::point(answer_x, y));
  }

  void render_yes_no_answer(const int id, const bool condition, const int y)
  {
    m_renderer.render(m_cache.get_stored(id), cen::point(10, y));

    if (condition)
    {
      m_renderer.render(m_cache.get_stored(id_yes), cen::point(answer_x, y));
    }
    else
    {
      m_renderer.render(m_cache.get_stored(id_no), cen::point(answer_x, y));
    }
  }

  void render_value(const int id, const std::optional<int> value, const int y)
  {
    m_renderer.render(m_cache.get_stored(id), cen::point(10, y));
    if (value)
    {
      m_renderer.render_text(m_cache,
                             std::to_string(*value),
                             cen::point(answer_x, y));
    }
    else
    {
      m_renderer.render(m_cache.get_stored(id_none), cen::point(answer_x, y));
    }
  }
};

}  // namespace

auto main(int, char**) -> int
{
  cen::library centurion;
  battery_demo demo;
  return demo.run();
}
