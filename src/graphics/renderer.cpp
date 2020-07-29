#include "renderer.hpp"

#include "centurion_utils.hpp"

namespace centurion {

renderer::renderer(nn_owner<SDL_Renderer*> sdlRenderer)
    : m_renderer{sdlRenderer}
{
  // FIXME don't change any previous state here, just accept SDL renderer
  set_color(colors::black);
  set_logical_integer_scale(false);
}

renderer::renderer(const window& window, SDL_RendererFlags flags)
    : m_renderer{SDL_CreateRenderer(window.get(), -1, flags)}
{
  if (!m_renderer) {
    throw detail::core_error("Failed to create renderer!");
  }

  set_blend_mode(blend_mode::blend);
  set_color(colors::black);
  set_logical_integer_scale(false);
}

auto renderer::unique(nn_owner<SDL_Renderer*> sdlRenderer) -> uptr
{
  return std::make_unique<renderer>(sdlRenderer);
}

auto renderer::unique(const window& window, SDL_RendererFlags flags) -> uptr
{
  return std::make_unique<renderer>(window, flags);
}

auto renderer::shared(nn_owner<SDL_Renderer*> sdlRenderer) -> sptr
{
  return std::make_shared<renderer>(sdlRenderer);
}

auto renderer::shared(const window& window, SDL_RendererFlags flags) -> sptr
{
  return std::make_shared<renderer>(window, flags);
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
