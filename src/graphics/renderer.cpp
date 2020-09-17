#include "renderer.hpp"

#include "detail/utils.hpp"
#include "exception.hpp"

namespace centurion {

renderer::renderer(nn_owner<SDL_Renderer*> sdlRenderer) noexcept
    : m_renderer{sdlRenderer}
{}

renderer::renderer(const window& window, SDL_RendererFlags flags)
    : m_renderer{SDL_CreateRenderer(window.get(), -1, flags)}
{
  if (!m_renderer) {
    throw sdl_error{"Failed to create renderer"};
  }

  set_blend_mode(blend_mode::blend);
  set_color(colors::black);
  set_logical_integer_scale(false);
}

void renderer::add_font(entt::id_type id, font&& font)
{
  if (m_fonts.find(id) != m_fonts.end()) {
    remove_font(id);
  }
  m_fonts.emplace(id, std::move(font));
}

void renderer::remove_font(entt::id_type id)
{
  m_fonts.erase(id);
}

auto to_string(const renderer& renderer) -> std::string
{
  return "[renderer | ptr: " + detail::address_of(renderer.get()) + "]";
}

auto operator<<(std::ostream& stream, const renderer& renderer) -> std::ostream&
{
  stream << to_string(renderer);
  return stream;
}

}  // namespace centurion
