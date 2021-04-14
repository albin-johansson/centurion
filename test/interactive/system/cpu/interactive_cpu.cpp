#include "centurion.hpp"

namespace {

inline constexpr auto msg_cache = "L1 cache size in bytes: ";
inline constexpr auto msg_cores = "Number of cores: ";
inline constexpr auto msg_endianness = "Endianness: ";
inline constexpr auto msg_simd = "SIMD alignment: ";

inline constexpr auto id_msg_cache = 0;
inline constexpr auto id_msg_cores = 1;
inline constexpr auto id_msg_endianness = 2;
inline constexpr auto id_msg_simd = 3;

inline constexpr auto id_value_cache = 10;
inline constexpr auto id_value_cores = 11;
inline constexpr auto id_value_endianness = 12;
inline constexpr auto id_value_simd = 13;

inline constexpr cen::iarea window_size{500, 150};

class cpu_demo final
{
 public:
  cpu_demo()
      : m_window{"CPU information", window_size}
      , m_renderer{m_window}
      , m_cache{"resources/fira_code.ttf", 24}
  {
    m_renderer.set_color(cen::colors::white);
    m_cache.store_blended_utf8(id_msg_cache, msg_cache, m_renderer);
    m_cache.store_blended_utf8(id_msg_cores, msg_cores, m_renderer);
    m_cache.store_blended_utf8(id_msg_endianness, msg_endianness, m_renderer);
    m_cache.store_blended_utf8(id_msg_simd, msg_simd, m_renderer);

    m_cache.store_blended_utf8(id_value_cache,
                               std::to_string(cen::cpu::cache_line_size()),
                               m_renderer);
    m_cache.store_blended_utf8(id_value_cores,
                               std::to_string(cen::cpu::cores()),
                               m_renderer);
    m_cache.store_blended_utf8(id_value_endianness,
                               cen::cpu::is_big_endian() ? "Big" : "Little",
                               m_renderer);
    m_cache.store_blended_utf8(id_value_simd,
                               std::to_string(cen::cpu::simd_alignment()),
                               m_renderer);
  }

  auto run() -> int
  {
    cen::event event;
    m_window.show();

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

      const auto render = [this](const int msg, const int value, const int y) {
        auto& texture = m_cache.get_stored(msg);
        m_renderer.render(texture, cen::point(350 - texture.width(), y));
        m_renderer.render(m_cache.get_stored(value), cen::point(350, y));
      };

      m_renderer.clear_with(cen::colors::steel_blue);

      render(id_msg_cache, id_value_cache, 10);
      render(id_msg_cores, id_value_cores, 40);
      render(id_msg_endianness, id_value_endianness, 70);
      render(id_msg_simd, id_value_simd, 100);

      m_renderer.present();
    }

    m_window.hide();

    return 0;
  }

 private:
  cen::window m_window;
  cen::renderer m_renderer;
  cen::font_cache m_cache;
  bool m_running{true};
};

}  // namespace

auto main(int, char**) -> int
{
  cen::library centurion;
  cpu_demo demo;
  return demo.run();
}