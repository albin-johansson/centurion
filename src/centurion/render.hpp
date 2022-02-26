#ifndef CENTURION_RENDER_HPP_
#define CENTURION_RENDER_HPP_

#include <SDL.h>

#ifndef CENTURION_NO_SDL_IMAGE
#include <SDL_image.h>
#endif  // CENTURION_NO_SDL_IMAGE

#include <cassert>      // assert
#include <cmath>        // floor, sqrt
#include <cstddef>      // size_t
#include <optional>     // optional
#include <ostream>      // ostream
#include <string>       // string, to_string
#include <string>       // string, string_literals
#include <string_view>  // string_view
#include <utility>      // pair

#include "color.hpp"
#include "common.hpp"
#include "detail/owner_handle_api.hpp"
#include "detail/stdlib.hpp"
#include "features.hpp"
#include "math.hpp"
#include "surface.hpp"
#include "texture.hpp"
#include "unicode.hpp"
#include "video.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/**
 * \ingroup video
 * \defgroup render Rendering
 *
 * \brief Contains components related to hardware-accelerated 2D rendering.
 *
 * \see `basic_renderer`
 * \see `renderer_flip`
 * \see `renderer_info`
 */

/// \addtogroup render
/// \{

enum class renderer_flip
{
  none = SDL_FLIP_NONE,
  horizontal = SDL_FLIP_HORIZONTAL,
  vertical = SDL_FLIP_VERTICAL
};

/// \name Renderer flip functions
/// \{

[[nodiscard]] constexpr auto to_string(const renderer_flip flip) -> std::string_view
{
  switch (flip) {
    case renderer_flip::none:
      return "none";

    case renderer_flip::horizontal:
      return "horizontal";

    case renderer_flip::vertical:
      return "vertical";

    default:
      throw exception{"Did not recognize renderer flip value!"};
  }
}

inline auto operator<<(std::ostream& stream, const renderer_flip flip) -> std::ostream&
{
  return stream << to_string(flip);
}

/// \} End of renderer flip functions

/**
 * \brief Provides information about rendering scale.
 */
struct renderer_scale final
{
  float x{};  ///< The x-axis scaling.
  float y{};  ///< The y-axis scaling.
};

template <typename T>
class basic_renderer;

using renderer = basic_renderer<detail::owner_tag>;          ///< An owning renderer.
using renderer_handle = basic_renderer<detail::handle_tag>;  ///< A non-owning renderer.

/**
 * \brief Provides the primary 2D rendering API.
 *
 * \ownerhandle `renderer`/`renderer_handle`
 *
 * \details Rendering primitives such as points, rectangles, lines and circles are supported.
 *
 * \details An example usage of this class can be found \subpage page-basic-rendering "here".
 *
 * \note Each window is associated with at most one renderer.
 *
 * \see `renderer`
 * \see `renderer_handle`
 * \see `renderer_info`
 */
template <typename T>
class basic_renderer final
{
 public:
  /// \brief Represents different renderer features.
  enum renderer_flags : uint32 {
    software = SDL_RENDERER_SOFTWARE,              ///< Software renderer.
    accelerated = SDL_RENDERER_ACCELERATED,        ///< Hardware-accelerated.
    target_textures = SDL_RENDERER_TARGETTEXTURE,  ///< Supports target textures.
    vsync = SDL_RENDERER_PRESENTVSYNC              ///< Uses VSync.
  };

  /// \name Construction
  /// \{

  explicit basic_renderer(maybe_owner<SDL_Renderer*> renderer) noexcept(detail::is_handle<T>)
      : mRenderer{renderer}
  {
    if constexpr (detail::is_owner<T>) {
      if (!get()) {
        throw exception{"Cannot create renderer from null pointer!"};
      }
    }
  }

  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit basic_renderer(const renderer& owner) noexcept : mRenderer{owner.get()}
  {}

  /// \} End of construction

  /// \name Texture factory functions
  /// \{

  /**
   * \brief Creates a texture based on an existing surface.
   *
   * \param surface the surface that the texture will be based on.
   *
   * \return the created texture.
   */
  template <typename X>
  [[nodiscard]] auto create_texture(const basic_surface<X>& surface) const -> texture
  {
    if (auto* ptr = SDL_CreateTextureFromSurface(get(), surface.get())) {
      return texture{ptr};
    }
    else {
      throw sdl_error{};
    }
  }

  /**
   * \brief Creates a blank texture with the specified characteristics.
   *
   * \param format the pixel format that will be used.
   * \param access the texture access that will be used.
   * \param size the size of the texture.
   *
   * \throws sdl_error if the texture cannot be created.
   *
   * \return the created texture.
   */
  [[nodiscard]] auto create_texture(const iarea& size,
                                    const pixel_format format,
                                    const texture_access access) const -> texture
  {
    if (auto* ptr = SDL_CreateTexture(get(),
                                      to_underlying(format),
                                      to_underlying(access),
                                      size.width,
                                      size.height)) {
      return texture{ptr};
    }
    else {
      throw sdl_error{};
    }
  }

#ifndef CENTURION_NO_SDL_IMAGE

  /**
   * \brief Creates a texture based on an image file.
   *
   * \param path the file path to the source image.
   *
   * \throws img_error if the texture cannot be created.
   *
   * \return the loaded texture.
   */
  [[nodiscard]] auto create_texture(const char* path) const -> texture
  {
    assert(path);
    if (auto* ptr = IMG_LoadTexture(get(), path)) {
      return texture{ptr};
    }
    else {
      throw img_error{};
    }
  }

  [[nodiscard]] auto create_texture(const std::string& path) const -> texture
  {
    return create_texture(path.c_str());
  }

#endif  // CENTURION_NO_SDL_IMAGE

  /// \} End of texture factory functions

  /// \name Basic rendering commands
  /// \{

  /**
   * \brief Clears the rendering target with the currently selected color.
   *
   * \return `success` if the rendering target was successfully cleared; `failure` otherwise.
   *
   * \see `clear_with()`
   */
  auto clear() noexcept -> result { return SDL_RenderClear(get()) == 0; }

  /**
   * \brief Clears the rendering target with a specific color.
   *
   * \details The previously selected color is unaffected by this function.
   *
   * \param color the color that will be used.
   */
  void clear_with(const color& color) noexcept
  {
    const auto previous = get_color();
    set_color(color);
    clear();
    set_color(previous);
  }

  /**
   * \brief Submits previous rendering calls to the rendering target.
   */
  void present() noexcept { SDL_RenderPresent(get()); }

  /// \} End of basic rendering commands

  /// \name Primitive rendering
  /// \{

  /**
   * \brief Fills the entire rendering target with the currently selected color.
   *
   * \details This function is different from `clear()` and `clear_with()` in that it can
   * be used as an intermediate rendering command (just like all rendering functions). An
   * example of a use case of this function could be for rendering a transparent
   * background for game menus.
   */
  void fill() noexcept
  {
    cen::irect rect;
    rect.set_size(output_size());
    fill_rect(rect);
  }

  /**
   * \brief Fills the entire rendering target with the specified color.
   *
   * \copydetails fill()
   *
   * \note The previously set color is not overridden by this function.
   */
  void fill_with(const color& color) noexcept
  {
    const auto previous = get_color();

    set_color(color);
    fill();

    set_color(previous);
  }

  /**
   * \brief Renders the outline of a rectangle in the currently selected color.
   *
   * \param rect the rectangle that will be rendered.
   *
   * \return `success` if the rendering was successful; `failure` otherwise.
   */
  template <typename X>
  auto draw_rect(const basic_rect<X>& rect) noexcept -> result
  {
    if constexpr (basic_rect<X>::integral) {
      return SDL_RenderDrawRect(get(), rect.data()) == 0;
    }
    else {
      return SDL_RenderDrawRectF(get(), rect.data()) == 0;
    }
  }

  /**
   * \brief Renders a filled rectangle in the currently selected color.
   *
   * \param rect the rectangle that will be rendered.
   *
   * \return `success` if the rendering was successful; `failure` otherwise.
   */
  template <typename X>
  auto fill_rect(const basic_rect<X>& rect) noexcept -> result
  {
    if constexpr (basic_rect<X>::integral) {
      return SDL_RenderFillRect(get(), rect.data()) == 0;
    }
    else {
      return SDL_RenderFillRectF(get(), rect.data()) == 0;
    }
  }

  /**
   * \brief Renders a line between the supplied points, in the currently selected color.
   *
   * \param start the start point of the line.
   * \param end the end point of the line.
   *
   * \return `success` if the rendering was successful; `failure` otherwise.
   */
  template <typename X>
  auto draw_line(const basic_point<X>& start, const basic_point<X>& end) noexcept -> result
  {
    if constexpr (basic_point<X>::integral) {
      return SDL_RenderDrawLine(get(), start.x(), start.y(), end.x(), end.y()) == 0;
    }
    else {
      return SDL_RenderDrawLineF(get(), start.x(), start.y(), end.x(), end.y()) == 0;
    }
  }

  /**
   * \brief Renders a collection of lines.
   *
   * \details This function requires the the `Container` type provides the public member
   * `value_type` and subsequently, that the `value_type` in turn provides a `value_type`
   * member. The former would correspond to the actual point type, and the latter
   * corresponds to either `int` or `float`.
   *
   * \warning `Container` *must* be a collection that stores its data contiguously! The
   * behaviour of this function is undefined if this condition isn't met.
   *
   * \tparam Container the container type. Must store its elements contiguously, such as
   * `std::vector` or `std::array`.
   *
   * \param container the container that holds the points that will be used to render the line.
   *
   * \return `success` if the lines were rendered; `failure` otherwise.
   */
  template <typename Container>
  auto draw_lines(const Container& container) noexcept -> result
  {
    using point_t = typename Container::value_type;  // a point of int or float
    using value_t = typename point_t::value_type;    // either int or float

    if (!container.empty()) {
      const auto& front = container.front();
      const auto* first = front.data();

      if constexpr (std::is_same_v<value_t, int>) {
        return SDL_RenderDrawLines(get(), first, isize(container)) == 0;
      }
      else {
        return SDL_RenderDrawLinesF(get(), first, isize(container)) == 0;
      }
    }
    else {
      return failure;
    }
  }

  /**
   * \brief Renders a point using the currently selected color.
   *
   * \param point the point that will be rendered.
   *
   * \return `success` if the rendering was successful; `failure` otherwise.
   */
  template <typename X>
  auto draw_point(const basic_point<X>& point) noexcept -> result
  {
    if constexpr (basic_point<X>::integral) {
      return SDL_RenderDrawPoint(get(), point.x(), point.y()) == 0;
    }
    else {
      return SDL_RenderDrawPointF(get(), point.x(), point.y()) == 0;
    }
  }

  /**
   * \brief Renders a circle using the currently selected color.
   *
   * \param position the position of the rendered circle.
   * \param radius the radius of the rendered circle.
   */
  template <typename X>
  void draw_circle(const basic_point<X>& position, const float radius) noexcept
  {
    using value_t = typename basic_point<X>::value_type;

    auto error = -radius;
    auto x = radius - 0.5f;
    auto y = 0.5f;

    const auto cx = static_cast<float>(position.x()) - 0.5f;
    const auto cy = static_cast<float>(position.y()) - 0.5f;

    while (x >= y) {
      draw_point<value_t>({static_cast<value_t>(cx + x), static_cast<value_t>(cy + y)});
      draw_point<value_t>({static_cast<value_t>(cx + y), static_cast<value_t>(cy + x)});

      if (x != 0) {
        draw_point<value_t>({static_cast<value_t>(cx - x), static_cast<value_t>(cy + y)});
        draw_point<value_t>({static_cast<value_t>(cx + y), static_cast<value_t>(cy - x)});
      }

      if (y != 0) {
        draw_point<value_t>({static_cast<value_t>(cx + x), static_cast<value_t>(cy - y)});
        draw_point<value_t>({static_cast<value_t>(cx - y), static_cast<value_t>(cy + x)});
      }

      if (x != 0 && y != 0) {
        draw_point<value_t>({static_cast<value_t>(cx - x), static_cast<value_t>(cy - y)});
        draw_point<value_t>({static_cast<value_t>(cx - y), static_cast<value_t>(cy - x)});
      }

      error += y;
      ++y;
      error += y;

      if (error >= 0) {
        --x;
        error -= x;
        error -= x;
      }
    }
  }

  /**
   * \brief Renders a filled circle using the currently selected color.
   *
   * \param center the position of the rendered circle.
   * \param radius the radius of the rendered circle.
   */
  template <typename X>
  void fill_circle(const basic_point<X>& center, const float radius)
  {
    const auto cx = static_cast<float>(center.x());
    const auto cy = static_cast<float>(center.y());

    for (auto dy = 1.0f; dy <= radius; dy += 1.0f) {
      const auto dx = std::floor(std::sqrt((2.0f * radius * dy) - (dy * dy)));
      draw_line<float>({cx - dx, cy + dy - radius}, {cx + dx, cy + dy - radius});
      draw_line<float>({cx - dx, cy - dy + radius}, {cx + dx, cy - dy + radius});
    }
  }

  /// \} End of primitive rendering

  /// \name Texture rendering functions
  /// \{

  /**
   * \brief Renders a texture.
   *
   * \param texture the texture that will be rendered.
   * \param pos the position of the rendered texture.
   *
   * \return `success` if the rendering was successful; `failure` otherwise.
   */
  template <typename X, typename Y>
  auto render(const basic_texture<X>& texture, const basic_point<Y>& pos) noexcept -> result
  {
    if constexpr (basic_point<Y>::floating) {
      const auto size = texture.size().as_f();
      const SDL_FRect dst{pos.x(), pos.y(), size.width, size.height};
      return SDL_RenderCopyF(get(), texture.get(), nullptr, &dst) == 0;
    }
    else {
      const SDL_Rect dst{pos.x(), pos.y(), texture.width(), texture.height()};
      return SDL_RenderCopy(get(), texture.get(), nullptr, &dst) == 0;
    }
  }

  /**
   * \brief Renders a texture.
   *
   * \param texture the texture that will be rendered.
   * \param dst the position and size of the rendered texture.
   *
   * \return `success` if the rendering was successful; `failure` otherwise.
   */
  template <typename X, typename Y>
  auto render(const basic_texture<X>& texture, const basic_rect<Y>& dst) noexcept -> result
  {
    if constexpr (basic_rect<Y>::floating) {
      return SDL_RenderCopyF(get(), texture.get(), nullptr, dst.data()) == 0;
    }
    else {
      return SDL_RenderCopy(get(), texture.get(), nullptr, dst.data()) == 0;
    }
  }

  /**
   * \brief Renders a texture.
   *
   * \param texture the texture that will be rendered.
   * \param src the region of the texture that will be rendered.
   * \param dst the position and size of the rendered texture.
   *
   * \return `success` if the rendering was successful; `failure` otherwise.
   */
  template <typename X, typename Y>
  auto render(const basic_texture<X>& texture,
              const irect& src,
              const basic_rect<Y>& dst) noexcept -> result
  {
    if constexpr (basic_rect<Y>::floating) {
      return SDL_RenderCopyF(get(), texture.get(), src.data(), dst.data()) == 0;
    }
    else {
      return SDL_RenderCopy(get(), texture.get(), src.data(), dst.data()) == 0;
    }
  }

  /**
   * \brief Renders a texture.
   *
   * \param texture the texture that will be rendered.
   * \param src the region of the texture that will be rendered.
   * \param dst the position and size of the rendered texture.
   * \param angle the clockwise angle, in degrees, that the texture is rotated around the
   * center.
   *
   * \return `success` if the rendering was successful; `failure` otherwise.
   */
  template <typename X, typename Y>
  auto render(const basic_texture<X>& texture,
              const irect& src,
              const basic_rect<Y>& dst,
              const double angle) noexcept -> result
  {
    if constexpr (basic_rect<Y>::floating) {
      return SDL_RenderCopyExF(get(),
                               texture.get(),
                               src.data(),
                               dst.data(),
                               angle,
                               nullptr,
                               SDL_FLIP_NONE) == 0;
    }
    else {
      return SDL_RenderCopyEx(get(),
                              texture.get(),
                              src.data(),
                              dst.data(),
                              angle,
                              nullptr,
                              SDL_FLIP_NONE) == 0;
    }
  }

  /**
   * \brief Renders a texture.
   *
   * \param texture the texture that will be rendered.
   * \param src the region of the texture that will be rendered.
   * \param dst the position and size of the rendered texture.
   * \param angle the clockwise angle, in degrees, that the texture is rotated.
   * \param center the around which the texture is rotated.
   * \param flip dictates how the texture will be flipped.
   *
   * \return `success` if the rendering was successful; `failure` otherwise.
   */
  template <typename X, typename Y, typename Z>
  auto render(const basic_texture<X>& texture,
              const irect& src,
              const basic_rect<Y>& dst,
              const double angle,
              const basic_point<Z>& center,
              const renderer_flip flip) noexcept -> result
  {
    static_assert(std::is_same_v<typename basic_rect<Y>::value_type,
                                 typename basic_point<Z>::value_type>,
                  "Destination rectangle and center point must have the same "
                  "value types (int or float)!");

    if constexpr (basic_rect<Y>::floating) {
      return SDL_RenderCopyExF(get(),
                               texture.get(),
                               src.data(),
                               dst.data(),
                               angle,
                               center.data(),
                               static_cast<SDL_RendererFlip>(flip)) == 0;
    }
    else {
      return SDL_RenderCopyEx(get(),
                              texture.get(),
                              src.data(),
                              dst.data(),
                              angle,
                              center.data(),
                              static_cast<SDL_RendererFlip>(flip)) == 0;
    }
  }

  /// \} End of texture rendering functions

  /// \name Arbitrary triangle rendering functions
  /// \{

#if SDL_VERSION_ATLEAST(2, 0, 18)

  /**
   * \brief Render arbitrary triangles.
   *
   * \tparam Size the deduced amount of vertices.
   *
   * \param vertices the vertices that will be rendered.
   *
   * \return `success` if the rendering is successful; `failure` otherwise.
   *
   * \atleastsdl 2.0.18
   */
  template <std::size_t Size>
  auto render_geo(bounded_array_ref<const SDL_Vertex, Size> vertices) noexcept -> result
  {
    return SDL_RenderGeometry(mRenderer,
                              nullptr,
                              vertices,
                              static_cast<int>(Size),
                              nullptr,
                              0) == 0;
  }

  /**
   * \brief Render arbitrary triangles.
   *
   * \tparam VertexCount the deduced amount of vertices.
   * \tparam IndexCount the deduced amount of indices.
   *
   * \param vertices the vertices that will be rendered.
   * \param indices the indices of the vertices that will be rendered.
   *
   * \return `success` if the rendering is successful; `failure` otherwise.
   */
  template <std::size_t VertexCount, std::size_t IndexCount>
  auto render_geo(bounded_array_ref<const SDL_Vertex, VertexCount> vertices,
                  bounded_array_ref<const int, IndexCount> indices) noexcept -> result
  {
    static_assert(IndexCount <= VertexCount);
    return SDL_RenderGeometry(mRenderer,
                              nullptr,
                              vertices,
                              static_cast<int>(VertexCount),
                              indices,
                              static_cast<int>(IndexCount)) == 0;
  }

  /**
   * \brief Render arbitrary triangles, using a texture.
   *
   * \tparam Size the deduced amount of vertices.
   *
   * \param texture the texture that will be rendered.
   * \param vertices the vertices that will be rendered.
   *
   * \return `success` if the rendering is successful; `failure` otherwise.
   */
  template <typename X, std::size_t Size>
  auto render_geo(const basic_texture<X>& texture,
                  bounded_array_ref<const SDL_Vertex, Size> vertices) noexcept -> result
  {
    return SDL_RenderGeometry(mRenderer,
                              texture.get(),
                              vertices,
                              static_cast<int>(Size),
                              nullptr,
                              0) == 0;
  }

  /**
   * \brief Render arbitrary triangles, using a texture.
   *
   * \tparam VertexCount the deduced amount of vertices.
   * \tparam IndexCount the deduced amount of indices.
   *
   * \param texture the texture that will be rendered.
   * \param vertices the vertices that will be rendered.
   * \param indices the indices of the vertices that will be rendered.
   *
   * \return `success` if the rendering is successful; `failure` otherwise.
   */
  template <typename X, std::size_t VertexCount, std::size_t IndexCount>
  auto render_geo(const basic_texture<X>& texture,
                  bounded_array_ref<const SDL_Vertex, VertexCount>& vertices,
                  bounded_array_ref<const int, IndexCount>& indices) noexcept -> result
  {
    static_assert(IndexCount <= VertexCount);
    return SDL_RenderGeometry(mRenderer,
                              texture.get(),
                              vertices,
                              static_cast<int>(VertexCount),
                              indices,
                              static_cast<int>(IndexCount)) == 0;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

  /// \} End of arbitrary triangle rendering functions

  /// \name Render target functions
  /// \{

  /**
   * \brief Resets the rendering target to the default.
   *
   * \return `success` if the rendering target was successfully reset; `failure` otherwise.
   */
  auto reset_target() noexcept -> result { return SDL_SetRenderTarget(get(), nullptr) == 0; }

  /**
   * \brief Sets the rendering target.
   *
   * \pre `target` must support being used as a render target.
   *
   * \param target the new rendering target.
   *
   * \return `success` if the render target was set; `failure` otherwise.
   *
   * \see `reset_target()`
   */
  template <typename X>
  auto set_target(basic_texture<X>& target) noexcept -> result
  {
    assert(target.is_target());
    return SDL_SetRenderTarget(get(), target.get()) == 0;
  }

  /**
   * \brief Returns a handle to the current render target.
   *
   * \return the current render target, which is empty if using the default target.
   */
  [[nodiscard]] auto get_target() noexcept -> texture_handle
  {
    return texture_handle{SDL_GetRenderTarget(get())};
  }

  /// \} End of render target functions

  /// \name Clipping
  /// \{

  /**
   * \brief Resets the clipping area.
   *
   * \return `success` if the clip was reset; `failure` otherwise.
   */
  auto reset_clip() noexcept -> result { return SDL_RenderSetClipRect(get(), nullptr) == 0; }

  /**
   * \brief Sets the clipping area.
   *
   * \details Clipping is disabled by default.
   *
   * \param area the new clip area.
   *
   * \return `success` if the clip was set; `failure` otherwise.
   *
   * \see `reset_clip()`
   */
  auto set_clip(const irect& area) noexcept -> result
  {
    return SDL_RenderSetClipRect(get(), area.data()) == 0;
  }

  /**
   * \brief Returns the current clipping rectangle, if there is one.
   *
   * \return the current clipping rectangle; an empty optional is returned if there is none.
   *
   * \see `reset_clip()`
   * \see `set_clip()`
   */
  [[nodiscard]] auto clip() const noexcept -> std::optional<irect>
  {
    irect rect;
    SDL_RenderGetClipRect(get(), rect.data());
    if (rect.has_area()) {
      return rect;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Indicates whether clipping is currently enabled.
   *
   * \return `true` if clipping is enabled; `false` otherwise.
   */
  [[nodiscard]] auto is_clipping_enabled() const noexcept -> bool
  {
    return SDL_RenderIsClipEnabled(get());
  }

  /// \} End of clipping

  /// \name Resolution-independent rendering
  /// \{

  /**
   * \brief Sets the logical (virtual) size.
   *
   * \pre The supplied width and height must be greater than or equal to zero.
   *
   * \details This is useful to achieve resolution-independent rendering.
   *
   * \param size the logical size that will be used.
   *
   * \return `success` if the logical size was set; `failure` otherwise.
   */
  auto set_logical_size(const iarea size) noexcept -> result
  {
    assert(size.width >= 0);
    assert(size.height >= 0);
    return SDL_RenderSetLogicalSize(get(), size.width, size.height) == 0;
  }

  /**
   * \brief Sets whether integer scaling is used by the logical viewport.
   *
   * \details This function can be useful to combat visual artefacts when doing floating-point
   * rendering.
   *
   * \param enabled `true` if integer scaling should be used; `false` otherwise.
   *
   * \return `success` if the option was changed; `failure` otherwise.
   */
  auto set_logical_integer_scaling(const bool enabled) noexcept -> result
  {
    return SDL_RenderSetIntegerScale(get(), enabled ? SDL_TRUE : SDL_FALSE) == 0;
  }

  /**
   * \brief Returns the size of the logical (virtual) viewport.
   *
   * \return the logical viewport size.
   */
  [[nodiscard]] auto logical_size() const noexcept -> iarea
  {
    iarea size{};
    SDL_RenderGetLogicalSize(get(), &size.width, &size.height);
    return size;
  }

  /**
   * \brief Indicates whether the renderer uses integer scaling for logical viewports.
   *
   * \details By default, this is disabled.
   *
   * \return `true` to use integer scaling for logical viewports; `false` otherwise.
   */
  [[nodiscard]] auto using_integer_logical_scaling() const noexcept -> bool
  {
    return SDL_RenderGetIntegerScale(get());
  }

#if SDL_VERSION_ATLEAST(2, 0, 18)

  /**
   * \brief Convert real coordinates to logical coordinates.
   *
   * \param realX the real window x-coordinate.
   * \param realY the real window y-coordinate.
   *
   * \return the corresponding logical coordinate.
   *
   * \see `from_logical()`
   *
   * \see `set_scale()`
   * \see `set_logical_size()`
   * \see `scale()`
   * \see `logical_size()`
   *
   * \atleastsdl 2.0.18
   */
  [[nodiscard]] auto to_logical(const int realX, const int realY) const noexcept -> fpoint
  {
    float logicalX{};
    float logicalY{};
    SDL_RenderWindowToLogical(get(), realX, realY, &logicalX, &logicalY);
    return {logicalX, logicalY};
  }

  /**
   * \brief Convert real coordinates to logical coordinates.
   *
   * \param real the real window coordinates.
   *
   * \return the corresponding logical coordinate.
   *
   * \see `from_logical()`
   *
   * \see `set_scale()`
   * \see `set_logical_size()`
   * \see `scale()`
   * \see `logical_size()`
   *
   * \atleastsdl 2.0.18
   */
  [[nodiscard]] auto to_logical(const ipoint& real) const noexcept -> fpoint
  {
    return to_logical(real.x(), real.y());
  }

  /**
   * \brief Convert logical coordinates to real window coordinates.
   *
   * \param logicalX the logical x-coordinate.
   * \param logicalY the logical y-coordinate.
   *
   * \return the corresponding real window coordinate.
   *
   * \see `to_logical()`
   *
   * \see `set_scale()`
   * \see `set_logical_size()`
   * \see `scale()`
   * \see `logical_size()`
   *
   * \atleastsdl 2.0.18
   */
  [[nodiscard]] auto from_logical(const float logicalX, const float logicalY) const noexcept
      -> ipoint
  {
    int realX{};
    int realY{};
    SDL_RenderLogicalToWindow(get(), logicalX, logicalY, &realX, &realY);
    return {realX, realY};
  }

  /**
   * \brief Convert logical coordinates to real window coordinates.
   *
   * \param logical the logical coordinate.
   *
   * \return the corresponding real window coordinate.
   *
   * \see `to_logical()`
   *
   * \see `set_scale()`
   * \see `set_logical_size()`
   * \see `scale()`
   * \see `logical_size()`
   *
   * \atleastsdl 2.0.18
   */
  [[nodiscard]] auto from_logical(const fpoint& logical) const noexcept -> ipoint
  {
    return from_logical(logical.x(), logical.y());
  }

#endif  // #if SDL_VERSION_ATLEAST(2, 0, 18)

  /// \} End of resolution-independent rendering

  /// \name Setters
  /// \{

  /**
   * \brief Sets the color that will be used by the renderer.
   *
   * \param color the new draw color.
   *
   * \return `success` if the color was successfully set; `failure` otherwise.
   */
  auto set_color(const color& color) noexcept -> result
  {
    return SDL_SetRenderDrawColor(get(),
                                  color.red(),
                                  color.green(),
                                  color.blue(),
                                  color.alpha()) == 0;
  }

  /**
   * \brief Sets the blend mode that will be used by the renderer.
   *
   * \param mode the new blend mode.
   *
   * \return `success` if the blend mode was successfully set; `failure` otherwise.
   */
  auto set_blend_mode(const blend_mode mode) noexcept -> result
  {
    return SDL_SetRenderDrawBlendMode(get(), static_cast<SDL_BlendMode>(mode)) == 0;
  }

  /**
   * \brief Sets the viewport that will be used by the renderer.
   *
   * \param viewport the new viewport.
   *
   * \return `success` if the viewport was successfully set; `failure` otherwise.
   */
  auto set_viewport(const irect& viewport) noexcept -> result
  {
    return SDL_RenderSetViewport(get(), viewport.data()) == 0;
  }

  /**
   * \brief Sets the scaling used by the renderer.
   *
   * \pre the scaling must be greater than zero for both axes.
   *
   * \param scale the new scaling.
   *
   * \return `success` if the scaling was set; `failure` otherwise.
   */
  auto set_scale(const renderer_scale scale) noexcept -> result
  {
    assert(scale.x > 0);
    assert(scale.y > 0);
    return SDL_RenderSetScale(get(), scale.x, scale.y) == 0;
  }

#if SDL_VERSION_ATLEAST(2, 0, 18)

  /**
   * \brief Sets whether VSync is enabled.
   *
   * \param enabled `true` if VSync should be enabled; `false` otherwise.
   *
   * \return `success` if VSync was successfully enabled/disabled; `failure` otherwise.
   *
   * \atleastsdl 2.0.18
   */
  auto set_vsync(const bool enabled) noexcept -> result
  {
    return SDL_RenderSetVSync(get(), enabled ? 1 : 0) == 0;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

  /// \} End of setters

  /// \name Getters
  /// \{

  /**
   * \brief Returns the current draw color.
   *
   * \return the draw color.
   */
  [[nodiscard]] auto get_color() const noexcept -> color
  {
    uint8 red{};
    uint8 green{};
    uint8 blue{};
    uint8 alpha{};
    SDL_GetRenderDrawColor(get(), &red, &green, &blue, &alpha);
    return {red, green, blue, alpha};
  }

  /**
   * \brief Returns the current blend mode.
   *
   * \return the current blend mode.
   */
  [[nodiscard]] auto get_blend_mode() const noexcept -> blend_mode
  {
    SDL_BlendMode mode{};
    SDL_GetRenderDrawBlendMode(get(), &mode);
    return static_cast<blend_mode>(mode);
  }

  /**
   * \brief Returns the current viewport.
   *
   * \return the viewport.
   */
  [[nodiscard]] auto viewport() const noexcept -> irect
  {
    irect viewport{};
    SDL_RenderGetViewport(get(), viewport.data());
    return viewport;
  }

  /**
   * \brief Returns the scale used by the renderer.
   *
   * \return the renderer scale.
   */
  [[nodiscard]] auto scale() const noexcept -> renderer_scale
  {
    renderer_scale scale;
    SDL_RenderGetScale(get(), &scale.x, &scale.y);
    return scale;
  }

  /// \} End of getters

  /// \name Queries
  /// \{

  /**
   * \brief Captures a snapshot of the current rendering target.
   *
   * \param format the pixel format that will be used by the surface.
   *
   * \return a surface that mirrors render target.
   *
   * \throws sdl_error if something goes wrong.
   *
   * \see `basic_window::get_pixel_format()`
   */
  [[nodiscard]] auto capture(const pixel_format format) const -> surface
  {
    surface image{output_size(), format};

    if (!image.lock()) {
      throw sdl_error{};
    }

    if (const auto res =
            SDL_RenderReadPixels(get(), nullptr, 0, image.pixel_data(), image.pitch());
        res == -1) {
      throw sdl_error{};
    }

    image.unlock();
    return image;
  }

  /**
   * \brief Returns the current output size of the renderer.
   *
   * \return the output size.
   */
  [[nodiscard]] auto output_size() const noexcept -> iarea
  {
    iarea size{};
    SDL_GetRendererOutputSize(get(), &size.width, &size.height);
    return size;
  }

  /// \} End of queries

  /// \name Misc functions
  /// \{

  [[nodiscard]] auto get() const noexcept -> SDL_Renderer* { return mRenderer.get(); }

  /**
   * \brief Indicates whether a handle holds a non-null pointer.
   *
   * \return `true` if the handle holds a non-null pointer; `false` otherwise.
   */
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mRenderer != nullptr;
  }

  /// \} End of misc functions

  [[nodiscard]] constexpr static auto default_flags() noexcept -> uint32
  {
    return accelerated | vsync;
  }

 private:
  detail::pointer<T, SDL_Renderer> mRenderer;
};

/// \name Renderer functions
/// \{

template <typename T>
[[nodiscard]] auto to_string(const basic_renderer<T>& renderer) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("renderer(data: {})", detail::address_of(renderer.get()));
#else
  return "renderer(data: " + detail::address_of(renderer.get()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
auto operator<<(std::ostream& stream, const basic_renderer<T>& renderer) -> std::ostream&
{
  return stream << to_string(renderer);
}

/// \} End of renderer functions

/**
 * \brief Provides information about a renderer.
 *
 * \see `get_info(const basic_renderer&)`
 */
class renderer_info final
{
  template <typename T>
  friend auto get_info(const basic_renderer<T>& renderer) noexcept
      -> std::optional<renderer_info>;

 public:
  using size_type = std::size_t;

  /**
   * \brief Returns a mask of all of the supported renderer flags.
   *
   * \return the supported renderer flags.
   *
   * \see `basic_renderer::renderer_flags`
   */
  [[nodiscard]] auto supported_flags() const noexcept -> uint32 { return mInfo.flags; }

  /**
   * \brief Indicates whether the renderer supports VSync.
   *
   * \return `true` if the renderer has VSync support; `false` otherwise.
   */
  [[nodiscard]] auto has_vsync() const noexcept -> bool
  {
    return supported_flags() & SDL_RENDERER_PRESENTVSYNC;
  }

  /**
   * \brief Indicates whether the renderer supports target textures.
   *
   * \return `true` if the renderer has target texture support; `false` otherwise.
   */
  [[nodiscard]] auto has_target_textures() const noexcept -> bool
  {
    return supported_flags() & SDL_RENDERER_TARGETTEXTURE;
  }

  /**
   * \brief Indicates whether the renderer supports hardware acceleration.
   *
   * \return `true` if the renderer is hardware accelerated; `false` otherwise.
   */
  [[nodiscard]] auto is_accelerated() const noexcept -> bool
  {
    return supported_flags() & SDL_RENDERER_ACCELERATED;
  }

  /**
   * \brief Indicates whether or not the renderer is a software renderer.
   *
   * \return `true` if the renderer is a software renderer; `false` otherwise.
   */
  [[nodiscard]] auto is_software() const noexcept -> bool
  {
    return supported_flags() & SDL_RENDERER_SOFTWARE;
  }

  /**
   * \brief Returns the total amount of supported pixel formats.
   *
   * \return the amount of pixel formats.
   *
   * \see `get_format()`
   */
  [[nodiscard]] auto format_count() const noexcept -> size_type
  {
    return static_cast<size_type>(mInfo.num_texture_formats);
  }

  /**
   * \brief Returns a supported pixel format.
   *
   * \param index the index of the pixel format.
   *
   * \return a pixel format.
   *
   * \throws exception if the index is invalid.
   */
  [[nodiscard]] auto get_format(const size_type index) const -> pixel_format
  {
    if (index < format_count()) {
      return static_cast<pixel_format>(mInfo.texture_formats[index]);
    }
    else {
      throw exception{"Invalid pixel format index!"};
    }
  }

  /**
   * \brief Returns the maximum size of a texture for the renderer.
   *
   * \return the maximum texture size.
   */
  [[nodiscard]] auto max_texture_size() const noexcept -> iarea
  {
    return {mInfo.max_texture_width, mInfo.max_texture_height};
  }

  /**
   * \brief Returns the maximum width of a texture for the renderer.
   *
   * \return the maximum texture width.
   */
  [[nodiscard]] auto max_texture_width() const noexcept -> int
  {
    return mInfo.max_texture_width;
  }

  /**
   * \brief Returns the maximum height of a texture for the renderer.
   *
   * \return the maximum texture height.
   */
  [[nodiscard]] auto max_texture_height() const noexcept -> int
  {
    return mInfo.max_texture_height;
  }

  /**
   * \brief Returns the name of the renderer.
   *
   * \return the renderer name.
   */
  [[nodiscard]] auto name() const noexcept -> const char* { return mInfo.name; }

 private:
  SDL_RendererInfo mInfo;

  explicit renderer_info(const SDL_RendererInfo info) noexcept : mInfo{info} {}
};

/// \name Renderer info functions
/// \{

[[nodiscard]] inline auto to_string(const renderer_info& info) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("renderer_info(name: '{}')", str_or_na(info.name()));
#else
  using namespace std::string_literals;
  return "renderer_info(name: '"s + str_or_na(info.name()) + "')";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

inline auto operator<<(std::ostream& stream, const renderer_info& info) -> std::ostream&
{
  return stream << to_string(info);
}

/// \} End of renderer info functions

/// \name Renderer functions
/// \{

/**
 * \brief Returns information about a renderer.
 *
 * \param renderer the renderer to query.
 *
 * \return the renderer information.
 */
template <typename T>
[[nodiscard]] auto get_info(const basic_renderer<T>& renderer) noexcept
    -> std::optional<renderer_info>
{
  SDL_RendererInfo info{};
  if (SDL_GetRendererInfo(renderer.get(), &info) == 0) {
    return renderer_info{info};
  }
  else {
    return std::nullopt;
  }
}

/// \} End of renderer functions

/// \name Driver functions
/// \{

/**
 * \brief Returns the number of available rendering drivers.
 *
 * \note Usually there is only one available rendering driver.
 *
 * \return the amount of rendering drivers.
 */
[[nodiscard]] inline auto render_driver_count() noexcept -> int
{
  return SDL_GetNumRenderDrivers();
}

/**
 * \brief Returns the number of available video drivers compiled into SDL.
 *
 * \return the number of video drivers.
 */
[[nodiscard]] inline auto video_driver_count() noexcept -> int
{
  return SDL_GetNumVideoDrivers();
}

/// \} End of driver functions

/// \} End of group render

}  // namespace cen

#endif  // CENTURION_RENDER_HPP_
