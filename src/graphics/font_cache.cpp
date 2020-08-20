#include "font_cache.hpp"

#include <utility>

#include "renderer.hpp"

namespace centurion {

font_cache::font_cache(font&& font) noexcept : m_font{std::move(font)}
{}

auto font_cache::unique(font&& font) -> uptr
{
  return std::make_unique<font_cache>(std::move(font));
}

auto font_cache::shared(font&& font) -> sptr
{
  return std::make_shared<font_cache>(std::move(font));
}

void font_cache::store(entt::id_type id, texture&& texture)
{
  if (const auto it = m_strings.find(id); it != m_strings.end()) {
    m_strings.erase(it);
  }
  m_strings.emplace(id, std::move(texture));
}

auto font_cache::try_get_stored(entt::id_type id) const noexcept
    -> const texture*
{
  const auto iterator = m_strings.find(id);
  if (iterator != m_strings.end()) {
    return &iterator->second;
  } else {
    return nullptr;
  }
}

}  // namespace centurion
