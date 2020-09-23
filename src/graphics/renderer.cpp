#include "renderer.hpp"

#include <type_traits>

namespace cen {

static_assert(std::is_final_v<renderer>);
static_assert(std::is_nothrow_destructible_v<renderer>);

static_assert(!std::is_copy_constructible_v<renderer>);
static_assert(!std::is_copy_assignable_v<renderer>);

static_assert(std::is_move_constructible_v<renderer>);
static_assert(std::is_nothrow_move_assignable_v<renderer>);

void renderer::add_font(font_id id, font&& font)
{
  if (m_fonts.find(id) != m_fonts.end()) {
    remove_font(id);
  }
  m_fonts.emplace(id, std::move(font));
}

void renderer::remove_font(font_id id)
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

}  // namespace cen
