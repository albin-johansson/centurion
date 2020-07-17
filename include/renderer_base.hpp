/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file renderer_base.hpp
 *
 * @brief Provides the `renderer_base` class, the base implementation of
 * renderers.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_RENDERER_BASE_HEADER
#define CENTURION_RENDERER_BASE_HEADER

#include "area.hpp"
#include "blend_mode.hpp"
#include "centurion_api.hpp"
#include "centurion_types.hpp"
#include "color.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "texture.hpp"

namespace centurion {

/**
 * @class renderer_base
 *
 * @brief Provides the base implementation of renderers.
 *
 * @details This class provides the general API for hardware-accelerated
 * rendering.
 *
 * @since 5.0.0
 *
 * @see `renderer`
 * @see `renderer_view`
 *
 * @headerfile graphics.hpp
 */
class renderer_base {
 public:
  /**
   * @brief Clears the rendering target with the currently selected color.
   *
   * @since 3.0.0
   */
  void clear() noexcept;

  /**
   * @brief Clears the rendering target with the specified color.
   *
   * @note This method doesn't change the currently selected color.
   *
   * @param color the color that will be used to clear the rendering target.
   *
   * @since 5.0.0
   */
  void clear_with(const color& color) noexcept;

  /**
   * @brief Applies the previous rendering calls to the rendering target.
   *
   * @since 3.0.0
   */
  void present() noexcept;

  /**
   * @brief Renders the outline of a rectangle in the currently selected color.
   *
   * @tparam T The type of the rectangle coordinates. Must be either `int` or
   * `float`.
   *
   * @param rect the rectangle that will be rendered.
   *
   * @since 4.0.0
   */
  template <typename T>
  void draw_rect(const basic_rect<T>& rect) noexcept;

  /**
   * @brief Renders a filled rectangle in the currently selected color.
   *
   * @tparam T The type of the rectangle coordinates. Must be either `int` or
   * `float`.
   *
   * @param rect the rectangle that will be rendered.
   *
   * @since 4.0.0
   */
  template <typename T>
  void fill_rect(const basic_rect<T>& rect) noexcept;

  /**
   * @brief Renders a line between the supplied points, in the currently
   * selected color.
   *
   * @tparam T The type of the point coordinates. Must be either `int` or
   * `float`.
   *
   * @param start the start point of the line.
   * @param end the end point of the line.
   *
   * @since 4.0.0
   */
  template <typename T>
  void draw_line(const basic_point<T>& start,
                 const basic_point<T>& end) noexcept;

  /**
   * @brief Renders a collection of lines.
   *
   * @warning `Container` *must* be a collection that stores its data
   * contiguously! The behaviour of this method is undefined if this condition
   * isn't met.
   *
   * @tparam Container the container type. Must store its elements
   * contiguously, such as `std::vector` or `std::array`.
   *
   * @param container the container that holds the points that will be used
   * to render the line.
   *
   * @since 5.0.0
   */
  template <typename Container>
  void draw_lines(const Container& container) noexcept;

  /**
   * @brief Renders a texture at the specified position.
   *
   * @tparam T The type of the point coordinates. Must be either `int` or
   * `float`.
   *
   * @param texture the texture that will be rendered.
   * @param position the position of the rendered texture.
   *
   * @since 4.0.0
   */
  template <typename T>
  void render(const texture& texture, const basic_point<T>& position) noexcept;

  /**
   * @brief Renders a texture according to the specified rectangle.
   *
   * @tparam T The type of the rectangle coordinates. Must be either `int` or
   * `float`.
   *
   * @param texture the texture that will be rendered.
   * @param destination the position and size of the rendered texture.
   *
   * @since 4.0.0
   */
  template <typename T>
  void render(const texture& texture,
              const basic_rect<T>& destination) noexcept;

  /**
   * @brief Renders a texture.
   *
   * @remarks This should be your preferred method of rendering textures. This
   * method is efficient and simple.
   *
   * @tparam T The type of the rectangle coordinates. Must be either `int` or
   * `float`.
   *
   * @param texture the texture that will be rendered.
   * @param source the cutout out of the texture that will be rendered.
   * @param destination the position and size of the rendered texture.
   *
   * @since 4.0.0
   */
  template <typename T>
  void render(const texture& texture,
              const rect_i& source,
              const basic_rect<T>& destination) noexcept;

  /**
   * @brief Renders a texture.
   *
   * @tparam T The type of the rectangle coordinates. Must be either `int` or
   * `float`.
   *
   * @param texture the texture that will be rendered.
   * @param source the cutout out of the texture that will be rendered.
   * @param destination the position and size of the rendered texture.
   * @param angle the clockwise angle, in degrees, with which the rendered
   * texture will be rotated.
   *
   * @since 4.0.0
   */
  template <typename T>
  void render(const texture& texture,
              const rect_i& source,
              const basic_rect<T>& destination,
              double angle) noexcept;

  /**
   * @brief Renders a texture.
   *
   * @tparam T The type of the rectangle coordinates. Must be either `int` or
   * `float`.
   *
   * @param texture the texture that will be rendered.
   * @param source the cutout out of the texture that will be rendered.
   * @param destination the position and size of the rendered texture.
   * @param angle the clockwise angle, in degrees, with which the rendered
   * texture will be rotated.
   * @param center specifies the point around which the rendered texture will be
   * rotated.
   *
   * @since 4.0.0
   */
  template <typename T>
  void render(const texture& texture,
              const rect_i& source,
              const basic_rect<T>& destination,
              double angle,
              const basic_point<T>& center) noexcept;

  /**
   * @brief Renders a texture.
   *
   * @tparam T The type of the rectangle coordinates. Must be either `int` or
   * `float`.
   *
   * @param texture the texture that will be rendered.
   * @param source the cutout out of the texture that will be rendered.
   * @param destination the position and size of the rendered texture.
   * @param angle the clockwise angle, in degrees, with which the rendered
   * texture will be rotated.
   * @param center specifies the point around which the rendered texture will be
   * rotated.
   * @param flip specifies how the rendered texture will be flipped.
   *
   * @since 4.0.0
   */
  template <typename T>
  void render(const texture& texture,
              const rect_i& source,
              const basic_rect<T>& destination,
              double angle,
              const basic_point<T>& center,
              SDL_RendererFlip flip) noexcept;

  /**
   * @brief Sets the color that will be used by the renderer.
   *
   * @param color the color that will be used by the renderer.
   *
   * @since 3.0.0
   */
  void set_color(const color& color) noexcept;

  /**
   * @brief Sets the clipping area rectangle.
   *
   * @details Clipping is disabled by default.
   *
   * @param area the clip area rectangle; or `nothing` to disable clipping.
   *
   * @since 3.0.0
   */
  void set_clip(std::optional<rect_i> area) noexcept;

  /**
   * @brief Sets the viewport that will be used by the renderer.
   *
   * @param viewport the viewport that will be used by the renderer.
   *
   * @since 3.0.0
   */
  void set_viewport(const rect_i& viewport) noexcept;

  /**
   * @brief Sets the blend mode that will be used by the renderer.
   *
   * @param mode the blend mode that will be used by the renderer.
   *
   * @since 3.0.0
   */
  void set_blend_mode(blend_mode mode) noexcept;

  /**
   * @brief Sets the rendering target of the renderer.
   *
   * @details The supplied texture must support being a render target.
   * Otherwise, this method will reset the render target.
   *
   * @param texture a pointer to the new target texture; `nullptr` indicates
   * that the default rendering target should be used.
   *
   * @since 3.0.0
   */
  void set_target(const texture* texture) noexcept;

  /**
   * @brief Sets the rendering scale.
   *
   * @note This method has no effect if any of the arguments aren't
   * greater than zero.
   *
   * @param xScale the x-axis scale that will be used.
   * @param yScale the y-axis scale that will be used.
   *
   * @since 3.0.0
   */
  void set_scale(float xScale, float yScale) noexcept;

  /**
   * @brief Sets the logical size used by the renderer.
   *
   * @details This method is useful for resolution-independent rendering.
   *
   * @remarks This is also known as *virtual size* in other frameworks.
   *
   * @note This method has no effect if either of the supplied dimensions
   * aren't greater than zero.
   *
   * @param size the logical width and height that will be used.
   *
   * @since 3.0.0
   */
  void set_logical_size(const area_i& size) noexcept;

  /**
   * @brief Sets whether or not to force integer scaling for the logical
   * viewport.
   *
   * @details By default, this property is set to false. This method can be
   * useful to combat visual artefacts when doing floating-point rendering.
   *
   * @param useLogicalIntegerScale `true` if integer scaling should be used;
   * `false` otherwise.
   *
   * @since 3.0.0
   */
  void set_logical_integer_scale(bool useLogicalIntegerScale) noexcept;

  /**
   * @brief Returns the logical width that the renderer uses.
   *
   * @details By default, this property is set to 0.
   *
   * @return the logical width that the renderer uses.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto logical_width() const noexcept -> int;

  /**
   * @brief Returns the logical height that the renderer uses.
   *
   * @details By default, this property is set to 0.
   *
   * @return the logical height that the renderer uses.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto logical_height() const noexcept -> int;

  /**
   * @brief Returns the x-axis scale that the renderer uses.
   *
   * @return the x-axis scale that the renderer uses.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto x_scale() const noexcept -> float;

  /**
   * @brief Returns the y-axis scale that the renderer uses.
   *
   * @return the y-axis scale that the renderer uses.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto y_scale() const noexcept -> float;

  /**
   * @brief Returns the current clipping rectangle, if there is one active.
   *
   * @return the current clipping rectangle; or `nothing` if there is none.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto clip() const noexcept -> std::optional<rect_i>;

  /**
   * @brief Returns information about the renderer.
   *
   * @return information about the renderer; `nothing` if something went wrong.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto info() const noexcept -> std::optional<SDL_RendererInfo>;

  /**
   * @brief Returns the output width of the renderer.
   *
   * @return the output width of the renderer.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto output_width() const noexcept -> int;

  /**
   * @brief Returns the output height of the renderer.
   *
   * @return the output height of the renderer.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto output_height() const noexcept -> int;

  /**
   * @brief Returns the output size of the renderer.
   *
   * @return the current output size of the renderer.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto output_size() const noexcept -> area_i;

  /**
   * @brief Returns the blend mode that is being used by the renderer.
   *
   * @return the blend mode that is being used.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto blend_mode() const noexcept -> blend_mode;

  /**
   * @brief Returns a bit mask of the current renderer flags.
   *
   * @note There are multiple other methods for checking if a flag is set,
   * such as `vsync_enabled` or `accelerated`, that are nicer to use than
   * this method.
   *
   * @return a bit mask of the current renderer flags.
   *
   * @see `SDL_RendererFlags`
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto flags() const noexcept -> u32;

  /**
   * @brief Indicates whether or not the `present` method is synced with
   * the refresh rate of the screen.
   *
   * @return `true` if vsync is enabled; `false` otherwise.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto vsync_enabled() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the renderer is hardware accelerated.
   *
   * @return `true` if the renderer is hardware accelerated; `false` otherwise.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto accelerated() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the renderer is using software rendering.
   *
   * @return `true` if the renderer is software-based; `false` otherwise.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto software_based() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the renderer supports rendering to a target
   * texture.
   *
   * @return `true` if the renderer supports target texture rendering; `false`
   * otherwise.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto supports_target_textures() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the renderer uses integer scaling values
   * for logical viewports.
   *
   * @details By default, this property is set to false.
   *
   * @return `true` if the renderer uses integer scaling for logical viewports;
   * `false` otherwise.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto using_integer_logical_scaling() const noexcept -> bool;

  /**
   * @brief Indicates whether or not clipping is enabled.
   *
   * @details This is disabled by default.
   *
   * @return `true` if clipping is enabled; `false` otherwise.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto clipping_enabled() const noexcept -> bool;

  /**
   * @brief Returns the currently selected rendering color.
   *
   * @details The default color is black.
   *
   * @return the currently selected rendering color.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto get_color() const noexcept -> color;

  /**
   * @brief Returns the viewport that the renderer uses.
   *
   * @return the viewport that the renderer uses.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto viewport() const noexcept -> rect_i;

  /**
   * @brief Returns a textual representation of the renderer.
   *
   * @return a textual representation of the renderer.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto to_string() const -> std::string;

  /**
   * @brief Returns a pointer to the associated SDL_Renderer.
   *
   * @warning Use of this method is not recommended, since it purposefully
   * breaks const-correctness. However, it's useful since many SDL calls use
   * non-const pointers even when no change will be applied.
   *
   * @return a pointer to the associated SDL_Renderer.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_Renderer*;

  /**
   * @brief Converts to `SDL_Renderer*`.
   *
   * @return a pointer to the associated `SDL_Renderer` instance.
   *
   * @since 3.0.0
   */
  [[nodiscard]] explicit operator SDL_Renderer*() noexcept;

  /**
   * @brief Converts to `const SDL_Renderer*`.
   *
   * @return a pointer to the associated `SDL_Renderer` instance.
   *
   * @since 3.0.0
   */
  [[nodiscard]] explicit operator const SDL_Renderer*() const noexcept;

  /**
   * @brief Returns the number of available rendering drivers.
   *
   * @note Usually there is only one available rendering driver.
   *
   * @return the number of available rendering drivers.
   *
   * @since 4.0.0
   */
  [[nodiscard]] static auto render_drivers() noexcept -> int;

  /**
   * @brief Returns the number of available video drivers compiled into SDL.
   *
   * @return the number of available video drivers compiled into SDL.
   *
   * @since 4.0.0
   */
  [[nodiscard]] static auto video_drivers() noexcept -> int;

  /**
   * @brief Returns the information associated with a rendering driver.
   *
   * @param index the index of the rendering driver to query.
   *
   * @return information about the specified rendering driver; `nothing` if
   * something went wrong.
   *
   * @since 4.0.0
   */
  [[nodiscard]] static auto driver_info(int index) noexcept
      -> std::optional<SDL_RendererInfo>;

 protected:
  /**
   * @brief Creates a renderer base instance.
   *
   * @param renderer the renderer that will be used.
   *
   * @since 5.0.0
   */
  explicit renderer_base(gsl::not_null<SDL_Renderer*> renderer)
      : m_renderer{renderer}
  {}

  SDL_Renderer* m_renderer;
};

inline void renderer_base::clear() noexcept
{
  SDL_RenderClear(m_renderer);
}

inline void renderer_base::clear_with(const color& c) noexcept
{
  const auto oldColor = get_color();

  set_color(c);
  clear();

  set_color(oldColor);
}

inline void renderer_base::present() noexcept
{
  SDL_RenderPresent(m_renderer);
}

template <typename T>
void renderer_base::draw_rect(const basic_rect<T>& rect) noexcept
{
  static_assert(std::is_same_v<T, float> || std::is_same_v<T, int>);

  if constexpr (std::is_same_v<T, int>) {
    SDL_RenderDrawRect(m_renderer, static_cast<const SDL_Rect*>(rect));
  } else {
    SDL_RenderDrawRectF(m_renderer, static_cast<const SDL_FRect*>(rect));
  }
}

template <typename T>
void renderer_base::fill_rect(const basic_rect<T>& rect) noexcept
{
  static_assert(std::is_same_v<T, float> || std::is_same_v<T, int>);

  if constexpr (std::is_same_v<T, int>) {
    SDL_RenderFillRect(m_renderer, static_cast<const SDL_Rect*>(rect));
  } else {
    SDL_RenderFillRectF(m_renderer, static_cast<const SDL_FRect*>(rect));
  }
}

template <typename T>
void renderer_base::draw_line(const basic_point<T>& start,
                              const basic_point<T>& end) noexcept
{
  static_assert(std::is_same_v<T, float> || std::is_same_v<T, int>);

  if constexpr (std::is_same_v<T, int>) {
    SDL_RenderDrawLine(m_renderer, start.x(), start.y(), end.x(), end.y());
  } else {
    SDL_RenderDrawLineF(m_renderer, start.x(), start.y(), end.x(), end.y());
  }
}

template <typename Container>
void renderer_base::draw_lines(const Container& container) noexcept
{
  // This must be a point of int or float
  using point_t = typename Container::value_type;  // TODO doc

  static_assert(std::is_same_v<point_t, basic_point<float>> ||
                std::is_same_v<point_t, basic_point<int>>);

  // This is either int or float
  using value_t = typename point_t::value_type;

  if (!container.empty()) {
    const basic_point<value_t>& front = container.front();

    if constexpr (std::is_same_v<value_t, int>) {
      const auto* first = static_cast<const SDL_Point*>(front);
      SDL_RenderDrawLines(m_renderer, first, container.size());
    } else {
      const auto* first = static_cast<const SDL_FPoint*>(front);
      SDL_RenderDrawLinesF(m_renderer, first, container.size());
    }
  }
}

template <typename T>
void renderer_base::render(const texture& texture,
                           const basic_point<T>& position) noexcept
{
  static_assert(std::is_same_v<T, float> || std::is_same_v<T, int>);

  if constexpr (std::is_same_v<T, int>) {
    const SDL_Rect dst{
        position.x(), position.y(), texture.width(), texture.height()};
    SDL_RenderCopy(m_renderer, texture.get(), nullptr, &dst);
  } else {
    const SDL_FRect dst{position.x(),
                        position.y(),
                        static_cast<float>(texture.width()),
                        static_cast<float>(texture.height())};
    SDL_RenderCopyF(m_renderer, texture.get(), nullptr, &dst);
  }
}

template <typename T>
void renderer_base::render(const texture& texture,
                           const basic_rect<T>& destination) noexcept
{
  static_assert(std::is_same_v<T, float> || std::is_same_v<T, int>);

  if constexpr (std::is_same_v<T, int>) {
    SDL_RenderCopy(m_renderer,
                   texture.get(),
                   nullptr,
                   static_cast<const SDL_Rect*>(destination));
  } else {
    SDL_RenderCopyF(m_renderer,
                    texture.get(),
                    nullptr,
                    static_cast<const SDL_FRect*>(destination));
  }
}

template <typename T>
void renderer_base::render(const texture& texture,
                           const rect_i& source,
                           const basic_rect<T>& destination) noexcept
{
  static_assert(std::is_same_v<T, float> || std::is_same_v<T, int>);

  if constexpr (std::is_same_v<T, int>) {
    SDL_RenderCopy(m_renderer,
                   texture.get(),
                   static_cast<const SDL_Rect*>(source),
                   static_cast<const SDL_Rect*>(destination));
  } else {
    SDL_RenderCopyF(m_renderer,
                    texture.get(),
                    static_cast<const SDL_Rect*>(source),
                    static_cast<const SDL_FRect*>(destination));
  }
}

template <typename T>
void renderer_base::render(const texture& texture,
                           const rect_i& source,
                           const basic_rect<T>& destination,
                           const double angle) noexcept
{
  static_assert(std::is_same_v<T, float> || std::is_same_v<T, int>);

  if constexpr (std::is_same_v<T, int>) {
    SDL_RenderCopyEx(m_renderer,
                     texture.get(),
                     static_cast<const SDL_Rect*>(source),
                     static_cast<const SDL_Rect*>(destination),
                     angle,
                     nullptr,
                     SDL_FLIP_NONE);
  } else {
    SDL_RenderCopyExF(m_renderer,
                      texture.get(),
                      static_cast<const SDL_Rect*>(source),
                      static_cast<const SDL_FRect*>(destination),
                      angle,
                      nullptr,
                      SDL_FLIP_NONE);
  }
}

template <typename T>
void renderer_base::render(const texture& texture,
                           const rect_i& source,
                           const basic_rect<T>& destination,
                           const double angle,
                           const basic_point<T>& center) noexcept
{
  static_assert(std::is_same_v<T, float> || std::is_same_v<T, int>);

  if constexpr (std::is_same_v<T, int>) {
    SDL_RenderCopyEx(m_renderer,
                     texture.get(),
                     static_cast<const SDL_Rect*>(source),
                     static_cast<const SDL_Rect*>(destination),
                     angle,
                     static_cast<const SDL_Point*>(center),
                     SDL_FLIP_NONE);
  } else {
    SDL_RenderCopyExF(m_renderer,
                      texture.get(),
                      static_cast<const SDL_Rect*>(source),
                      static_cast<const SDL_FRect*>(destination),
                      angle,
                      static_cast<const SDL_FPoint*>(center),
                      SDL_FLIP_NONE);
  }
}

template <typename T>
void renderer_base::render(const texture& texture,
                           const rect_i& source,
                           const basic_rect<T>& destination,
                           const double angle,
                           const basic_point<T>& center,
                           const SDL_RendererFlip flip) noexcept
{
  static_assert(std::is_same_v<T, float> || std::is_same_v<T, int>);

  if constexpr (std::is_same_v<T, int>) {
    SDL_RenderCopyEx(m_renderer,
                     texture.get(),
                     static_cast<const SDL_Rect*>(source),
                     static_cast<const SDL_Rect*>(destination),
                     angle,
                     static_cast<const SDL_Point*>(center),
                     flip);
  } else {
    SDL_RenderCopyExF(m_renderer,
                      texture.get(),
                      static_cast<const SDL_Rect*>(source),
                      static_cast<const SDL_FRect*>(destination),
                      angle,
                      static_cast<const SDL_FPoint*>(center),
                      flip);
  }
}

inline void renderer_base::set_color(const color& color) noexcept
{
  SDL_SetRenderDrawColor(
      m_renderer, color.red(), color.green(), color.blue(), color.alpha());
}

inline void renderer_base::set_clip(const std::optional<rect_i> area) noexcept
{
  if (area) {
    SDL_RenderSetClipRect(m_renderer, static_cast<const SDL_Rect*>(*area));
  } else {
    SDL_RenderSetClipRect(m_renderer, nullptr);
  }
}

inline void renderer_base::set_viewport(const rect_i& viewport) noexcept
{
  SDL_RenderSetViewport(m_renderer, static_cast<const SDL_Rect*>(viewport));
}

inline void renderer_base::set_blend_mode(const enum blend_mode mode) noexcept
{
  SDL_SetRenderDrawBlendMode(m_renderer, static_cast<SDL_BlendMode>(mode));
}

inline void renderer_base::set_target(const texture* texture) noexcept
{
  if (texture && texture->is_target()) {
    SDL_SetRenderTarget(m_renderer, texture->get());
  } else {
    SDL_SetRenderTarget(m_renderer, nullptr);
  }
}

inline void renderer_base::set_scale(const float xScale,
                                     const float yScale) noexcept
{
  if (xScale > 0 && yScale > 0) {
    SDL_RenderSetScale(m_renderer, xScale, yScale);
  }
}

inline void renderer_base::set_logical_size(const area_i& size) noexcept
{
  if (size.width > 0 && size.height > 0) {
    SDL_RenderSetLogicalSize(m_renderer, size.width, size.height);
  }
}

inline void renderer_base::set_logical_integer_scale(
    const bool useLogicalIntegerScale) noexcept
{
  SDL_RenderSetIntegerScale(m_renderer,
                            detail::convert_bool(useLogicalIntegerScale));
}

inline auto renderer_base::logical_width() const noexcept -> int
{
  int width = 0;
  SDL_RenderGetLogicalSize(m_renderer, &width, nullptr);
  return width;
}

inline auto renderer_base::logical_height() const noexcept -> int
{
  int height = 0;
  SDL_RenderGetLogicalSize(m_renderer, nullptr, &height);
  return height;
}

inline auto renderer_base::x_scale() const noexcept -> float
{
  float xScale = 0;
  SDL_RenderGetScale(m_renderer, &xScale, nullptr);
  return xScale;
}

inline auto renderer_base::y_scale() const noexcept -> float
{
  float yScale = 0;
  SDL_RenderGetScale(m_renderer, nullptr, &yScale);
  return yScale;
}

inline auto renderer_base::clip() const noexcept -> std::optional<rect_i>
{
  rect_i rect;
  SDL_RenderGetClipRect(m_renderer, static_cast<SDL_Rect*>(rect));
  if (!rect.has_area()) {
    return nothing;
  } else {
    return rect;
  }
}

inline auto renderer_base::info() const noexcept
    -> std::optional<SDL_RendererInfo>
{
  SDL_RendererInfo info;
  const auto result = SDL_GetRendererInfo(m_renderer, &info);
  if (result == 0) {
    return info;
  } else {
    return nothing;
  }
}

inline auto renderer_base::output_width() const noexcept -> int
{
  int width = 0;
  SDL_GetRendererOutputSize(m_renderer, &width, nullptr);
  return width;
}

inline auto renderer_base::output_height() const noexcept -> int
{
  int height = 0;
  SDL_GetRendererOutputSize(m_renderer, nullptr, &height);
  return height;
}

inline auto renderer_base::output_size() const noexcept -> area_i
{
  int width = 0;
  int height = 0;
  SDL_GetRendererOutputSize(m_renderer, &width, &height);
  return {width, height};
}

inline auto renderer_base::blend_mode() const noexcept -> enum blend_mode {
  SDL_BlendMode mode;  //
  SDL_GetRenderDrawBlendMode(m_renderer, &mode);
  return static_cast<enum blend_mode>(mode);
}

inline auto renderer_base::flags() const noexcept -> u32
{
  SDL_RendererInfo info;
  SDL_GetRendererInfo(m_renderer, &info);
  return info.flags;
}

inline auto renderer_base::vsync_enabled() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_RENDERER_PRESENTVSYNC);
}

inline auto renderer_base::accelerated() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_RENDERER_ACCELERATED);
}

inline auto renderer_base::software_based() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_RENDERER_SOFTWARE);
}

inline auto renderer_base::supports_target_textures() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_RENDERER_TARGETTEXTURE);
}

inline auto renderer_base::using_integer_logical_scaling() const noexcept
    -> bool
{
  return SDL_RenderGetIntegerScale(m_renderer);
}

inline auto renderer_base::clipping_enabled() const noexcept -> bool
{
  return SDL_RenderIsClipEnabled(m_renderer);
}

inline auto renderer_base::get_color() const noexcept -> color
{
  u8 red = 0, green = 0, blue = 0, alpha = 0;
  SDL_GetRenderDrawColor(m_renderer, &red, &green, &blue, &alpha);
  return {red, green, blue, alpha};
}

inline auto renderer_base::viewport() const noexcept -> rect_i
{
  rect_i viewport;
  SDL_RenderGetViewport(m_renderer, static_cast<SDL_Rect*>(viewport));
  return viewport;
}

inline auto renderer_base::to_string() const -> std::string
{
  const auto address = detail::address_of(this);
  const auto owidth = std::to_string(output_width());
  const auto oheight = std::to_string(output_height());
  return "[Renderer@" + address + " | Output width: " + owidth +
         ", Output height: " + oheight + "]";
}

inline auto renderer_base::get() const noexcept -> SDL_Renderer*
{
  return m_renderer;
}

inline renderer_base::operator SDL_Renderer*() noexcept
{
  return m_renderer;
}

inline renderer_base::operator const SDL_Renderer*() const noexcept
{
  return m_renderer;
}

inline auto renderer_base::render_drivers() noexcept -> int
{
  return SDL_GetNumRenderDrivers();
}

inline auto renderer_base::video_drivers() noexcept -> int
{
  return SDL_GetNumVideoDrivers();
}

inline auto renderer_base::driver_info(int index) noexcept
    -> std::optional<SDL_RendererInfo>
{
  SDL_RendererInfo info;
  const auto result = SDL_GetRenderDriverInfo(index, &info);
  if (result == 0) {
    return info;
  } else {
    return nothing;
  }
}

}  // namespace centurion

#endif  // CENTURION_RENDERER_BASE_HEADER