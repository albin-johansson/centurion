#include "surface.hpp"

#include <SDL_image.h>

#include <type_traits>

#include "detail/utils.hpp"
#include "exception.hpp"

namespace cen {

static_assert(std::is_final_v<surface>);
static_assert(std::is_copy_constructible_v<surface>);
static_assert(std::is_copy_assignable_v<surface>);
static_assert(std::is_nothrow_move_constructible_v<surface>);
static_assert(std::is_nothrow_move_assignable_v<surface>);

surface::surface(owner<SDL_Surface*> surface) : m_surface{surface}
{
  if (!m_surface) {
    throw exception{"Cannot create surface from null pointer!"};
  }
}

surface::surface(nn_czstring file) : m_surface{IMG_Load(file)}
{
  if (!m_surface) {
    throw img_error{"Failed to create surface from file"};
  }
}

surface::surface(const surface& other)
{
  copy(other);
}

auto surface::operator=(const surface& other) -> surface&
{
  if (this != &other) {
    copy(other);
  }
  return *this;
}

void surface::copy(const surface& other)
{
  m_surface.reset(other.copy_surface());
}

auto surface::in_bounds(const ipoint& point) const noexcept -> bool
{
  return !(point.x() < 0 || point.y() < 0 || point.x() >= width() ||
           point.y() >= height());
}

auto surface::must_lock() const noexcept -> bool
{
  return SDL_MUSTLOCK(m_surface);
}

auto surface::lock() noexcept -> bool
{
  if (must_lock()) {
    const auto result = SDL_LockSurface(m_surface.get());
    return result == 0;
  } else {
    return true;
  }
}

void surface::unlock() noexcept
{
  if (must_lock()) {
    SDL_UnlockSurface(m_surface.get());
  }
}

auto surface::copy_surface() const -> owner<SDL_Surface*>
{
  if (auto* copy = SDL_DuplicateSurface(m_surface.get())) {
    return copy;
  } else {
    throw sdl_error{"Failed to duplicate surface"};
  }
}

void surface::set_pixel(const ipoint& pixel, const color& color) noexcept
{
  if (!in_bounds(pixel)) {
    return;
  }

  const auto success = lock();
  if (!success) {
    return;
  }

  const int nPixels = (m_surface->pitch / 4) * height();
  const int index = (pixel.y() * width()) + pixel.x();

  if ((index >= 0) && (index < nPixels)) {
    const auto value = SDL_MapRGBA(m_surface->format,
                                   color.red(),
                                   color.green(),
                                   color.blue(),
                                   color.alpha());
    auto* pixels = reinterpret_cast<u32*>(m_surface->pixels);
    pixels[index] = value;
  }

  unlock();
}

void surface::set_alpha(u8 alpha) noexcept
{
  SDL_SetSurfaceAlphaMod(m_surface.get(), alpha);
}

void surface::set_color_mod(const color& color) noexcept
{
  SDL_SetSurfaceColorMod(
      m_surface.get(), color.red(), color.green(), color.blue());
}

void surface::set_blend_mode(enum blend_mode mode) noexcept
{
  SDL_SetSurfaceBlendMode(m_surface.get(), static_cast<SDL_BlendMode>(mode));
}

auto surface::alpha() const noexcept -> u8
{
  u8 alpha{0xFF};
  SDL_GetSurfaceAlphaMod(m_surface.get(), &alpha);
  return alpha;
}

auto surface::color_mod() const noexcept -> color
{
  u8 red{};
  u8 green{};
  u8 blue{};
  SDL_GetSurfaceColorMod(m_surface.get(), &red, &green, &blue);
  return color{red, green, blue};
}

auto surface::get_blend_mode() const noexcept -> blend_mode
{
  SDL_BlendMode mode{};
  SDL_GetSurfaceBlendMode(m_surface.get(), &mode);
  return static_cast<blend_mode>(mode);
}

auto surface::convert(pixel_format format) const -> surface
{
  const auto pixelFormat = static_cast<u32>(format);
  if (auto* surf = SDL_ConvertSurfaceFormat(m_surface.get(), pixelFormat, 0)) {
    surface converted{surf};
    converted.set_blend_mode(get_blend_mode());
    return converted;
  } else {
    throw sdl_error{"Failed to convert surface"};
  }
}

auto to_string(const surface& surface) -> std::string
{
  using namespace std::string_literals;
  return "[surface | ptr: "s + detail::address_of(surface.get()) +
         ", width: "s + std::to_string(surface.width()) + ", height: "s +
         std::to_string(surface.height()) + "]";
}

auto operator<<(std::ostream& stream, const surface& surface) -> std::ostream&
{
  stream << to_string(surface);
  return stream;
}

}  // namespace cen
