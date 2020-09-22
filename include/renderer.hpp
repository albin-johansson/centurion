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
 * @file renderer.hpp
 *
 * @brief Provides the `renderer` class.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

/**
 * @defgroup graphics Graphics
 *
 * @brief Contains components related to rendering, visuals and windows.
 */

#ifndef CENTURION_RENDERER_HEADER
#define CENTURION_RENDERER_HEADER

#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <utility>

#include "basic_renderer.hpp"
#include "centurion_api.hpp"
#include "colors.hpp"
#include "font.hpp"
#include "window.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * @class renderer
 *
 * @ingroup graphics
 *
 * @brief Represents an owning renderer.
 *
 * @details This class is designed to the main class used for
 * hardware-accelerated rendering. However, there is also the
 * `renderer_handle` that can be used if you don't want the renderer to claim
 * ownership of the `SDL_Renderer` pointer.
 *
 * @par Rendering textures
 * There are quite a number of methods provided for rendering `texture`
 * instances. There are two "overload" sets, `render` and `render_t`. These
 * methods can be used with either integer or floating-point accuracy.
 *
 * @par Translation
 * Most games utilize some sort of viewport of what the player can see of the
 * game world. If you're game features some sort of movable anchor for the
 * rendering, then you need to translate the positions of the various game
 * objects when rendering. This class provides a simple API for dealing with
 * this easily. Specify the translation viewport with
 * `set_translation_viewport(const frect&)`, and use the rendering methods
 * that feature the `_t` suffix in their names, such as `render_t`, to
 * automatically render at translated positions.
 *
 * @par Font support
 * When rendering text, it's often needed to pass around various font
 * instances. Subsequently, this class provides an API for managing `font`
 * instances. The fonts are stored in an internal map, using integers as keys.
 *
 * @par Rendering text
 * There is no method for directly rendering text. Instead, use one of the
 * `text_` methods for creating a texture that contains a rendered piece
 * of text, and render that texture when needed. Naturally, you should cache
 * these textures instead of creating and destroying them in your game loop.
 *
 * @tparam FontKey the key type used when storing associated fonts in a map.
 *
 * @since 3.0.0
 *
 * @see `SDL_Renderer`
 * @see `renderer_handle`
 *
 * @headerfile renderer.hpp
 */
class renderer final : public basic_renderer<renderer>
{
 public:
  /**
   * @brief Creates a renderer based on the supplied `SDL_Renderer`.
   *
   * @note This constructor doesn't change any of the state associated
   * with the supplied SDL renderer.
   *
   * @param sdlRenderer a pointer to the `SDL_Renderer` that will be used by the
   * renderer, can't be null.
   *
   * @throws exception if the supplied pointer is null.
   *
   * @since 3.0.0
   */
  CENTURION_API
  explicit renderer(owner<SDL_Renderer*> sdlRenderer);

  /**
   * @brief Creates a renderer based on the supplied window.
   *
   * @details By default, the internal renderer will be created using the
   * `SDL_RENDERER_ACCELERATED` and `SDL_RENDERER_PRESENTVSYNC` flags.
   *
   * @param window the associated window instance.
   * @param flags the renderer flags that will be used.
   *
   * @throws sdl_error if something goes wrong when creating the renderer.
   *
   * @since 4.0.0
   */
  CENTURION_API
  explicit renderer(const window& window,
                    SDL_RendererFlags flags = default_flags());

  /**
   * @name Translated rendering
   * @brief Functions related to translated rendering.
   */
  ///@{

  /**
   * @brief Sets the translation viewport that will be used by the renderer.
   *
   * @details This method should be called before calling any of the `_t`
   * rendering methods, for automatic translation.
   *
   * @param viewport the rectangle that will be used as the translation
   * viewport.
   *
   * @since 3.0.0
   */
  void set_translation_viewport(const frect& viewport) noexcept
  {
    m_translationViewport = viewport;
  }

  /**
   * @brief Returns the translation viewport that is currently being used.
   *
   * @details Set to (0, 0, 0, 0) by default.
   *
   * @return the translation viewport that is currently being used.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto translation_viewport() const noexcept -> const frect&
  {
    return m_translationViewport;
  }

  /**
   * @brief Renders an outlined rectangle in the currently selected color.
   *
   * @details The rendered rectangle will be translated using the current
   * translation viewport.
   *
   * @tparam T the representation type used by the rectangle.
   *
   * @param rect the rectangle that will be rendered.
   *
   * @since 4.1.0
   */
  template <typename T>
  void draw_rect_t(const basic_rect<T>& rect) noexcept;

  /**
   * @brief Renders a filled rectangle in the currently selected color.
   *
   * @details The rendered rectangle will be translated using the current
   * translation viewport.
   *
   * @tparam T the representation type used by the rectangle.
   *
   * @param rect the rectangle that will be rendered.
   *
   * @since 4.1.0
   */
  template <typename T>
  void fill_rect_t(const basic_rect<T>& rect) noexcept;

  /**
   * @brief Renders a texture at the specified position.
   *
   * @details The rendered texture will be translated using the translation
   * viewport.
   *
   * @tparam T The representation type used by the point.
   *
   * @param texture the texture that will be rendered.
   * @param position the position (pre-translation) of the rendered texture.
   *
   * @since 4.0.0
   */
  template <typename T>
  void render_t(const texture& texture,
                const basic_point<T>& position) noexcept;

  /**
   * @brief Renders a texture according to the specified rectangle.
   *
   * @details The rendered texture will be translated using the translation
   * viewport.
   *
   * @tparam T the representation type used by the destination rectangle.
   *
   * @param texture the texture that will be rendered.
   * @param destination the position (pre-translation) and size of the
   * rendered texture.
   *
   * @since 4.0.0
   */
  template <typename T>
  void render_t(const texture& texture,
                const basic_rect<T>& destination) noexcept;

  /**
   * @brief Renders a texture.
   *
   * @details The rendered texture will be translated using the translation
   * viewport.
   *
   * @remarks This should be your preferred method of rendering textures. This
   * method is efficient and simple.
   *
   * @tparam T the representation type used by the destination rectangle.
   *
   * @param texture the texture that will be rendered.
   * @param source the cutout out of the texture that will be rendered.
   * @param destination the position (pre-translation) and size of the
   * rendered texture.
   *
   * @since 4.0.0
   */
  template <typename T>
  void render_t(const texture& texture,
                const irect& source,
                const basic_rect<T>& destination) noexcept;

  /**
   * @brief Renders a texture.
   *
   * @details The rendered texture will be translated using the translation
   * viewport.
   *
   * @tparam T the representation type used by the destination rectangle.
   *
   * @param texture the texture that will be rendered.
   * @param source the cutout out of the texture that will be rendered.
   * @param destination the position (pre-translation) and size of the
   * rendered texture.
   * @param angle the clockwise angle, in degrees, with which the rendered
   * texture will be rotated.
   *
   * @since 4.0.0
   */
  template <typename T>
  void render_t(const texture& texture,
                const irect& source,
                const basic_rect<T>& destination,
                double angle) noexcept;

  /**
   * @brief Renders a texture.
   *
   * @details The rendered texture will be translated using the translation
   * viewport.
   *
   * @tparam R the representation type used by the destination rectangle.
   * @tparam P the representation type used by the center-of-rotation point.
   *
   * @param texture the texture that will be rendered.
   * @param source the cutout out of the texture that will be rendered.
   * @param destination the position (pre-translation) and size of the
   * rendered texture.
   * @param angle the clockwise angle, in degrees, with which the rendered
   * texture will be rotated.
   * @param center specifies the point around which the rendered texture will
   * be rotated.
   *
   * @since 4.0.0
   */
  template <typename R, typename P>
  void render_t(const texture& texture,
                const irect& source,
                const basic_rect<R>& destination,
                double angle,
                const basic_point<P>& center) noexcept;

  /**
   * @brief Renders a texture.
   *
   * @tparam R the representation type used by the destination rectangle.
   * @tparam P the representation type used by the center-of-rotation point.
   *
   * @param texture the texture that will be rendered.
   * @param source the cutout out of the texture that will be rendered.
   * @param destination the position (pre-translation) and size of the
   * rendered texture.
   * @param angle the clockwise angle, in degrees, with which the rendered
   * texture will be rotated.
   * @param center specifies the point around which the rendered texture will
   * be rotated.
   * @param flip specifies how the rendered texture will be flipped.
   *
   * @since 4.0.0
   */
  template <typename R, typename P>
  void render_t(const texture& texture,
                const irect& source,
                const basic_rect<R>& destination,
                double angle,
                const basic_point<P>& center,
                SDL_RendererFlip flip) noexcept;

  ///@} // end of translated rendering

  /**
   * @name Font handling
   * @brief Methods related to managing `font` instances.
   */
  ///@{

  /**
   * @brief Adds a font to the renderer.
   *
   * @note This function overwrites any previously stored font associated
   * with the specified ID.
   *
   * @param id the key that will be associated with the font.
   * @param font the font that will be added.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void add_font(font_id id, font&& font);

  /**
   * @brief Creates a font and adds it to the renderer.
   *
   * @note This function overwrites any previously stored font associated
   * with the specified ID.
   *
   * @tparam Args the types of the arguments that will be forwarded.
   *
   * @param id the key that will be associated with the font.
   * @param args the arguments that will be forwarded to the `font` constructor.
   *
   * @since 5.0.0
   */
  template <typename... Args>
  void emplace_font(font_id id, Args&&... args);

  /**
   * @brief Removes the font associated with the specified key.
   *
   * @details This method has no effect if there is no font associated with
   * the specified key.
   *
   * @param id the key associated with the font that will be removed.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void remove_font(font_id id);

  /**
   * @brief Returns the font associated with the specified name.
   *
   * @pre There must be a font associated with the specified ID.
   *
   * @param id the key associated with the desired font.
   *
   * @return the font associated with the specified name.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto get_font(font_id id) -> font& { return m_fonts.at(id); }

  /**
   * @copydoc get_font
   */
  [[nodiscard]] auto get_font(font_id id) const -> const font&
  {
    return m_fonts.at(id);
  }

  /**
   * @brief Indicates whether or not the renderer has a font associated with
   * the specified key.
   *
   * @param id the key that will be checked.
   *
   * @return `true` if the renderer has a font associated with the key;
   * `false` otherwise.
   *
   * @since 4.1.0
   */
  [[nodiscard]] auto has_font(font_id id) const noexcept -> bool
  {
    return static_cast<bool>(m_fonts.count(id));
  }

  ///@} // end of font handling

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
  [[nodiscard]] auto get() const noexcept -> SDL_Renderer*
  {
    return m_renderer.get();
  }

  /**
   * @brief Converts to `SDL_Renderer*`.
   *
   * @return a pointer to the associated `SDL_Renderer` instance.
   *
   * @since 3.0.0
   */
  [[nodiscard]] explicit operator SDL_Renderer*() noexcept
  {
    return m_renderer.get();
  }

  /**
   * @brief Converts to `const SDL_Renderer*`.
   *
   * @return a pointer to the associated `SDL_Renderer` instance.
   *
   * @since 3.0.0
   */
  [[nodiscard]] explicit operator const SDL_Renderer*() const noexcept
  {
    return m_renderer.get();
  }

 private:
  class deleter final
  {
   public:
    void operator()(SDL_Renderer* renderer) noexcept
    {
      SDL_DestroyRenderer(renderer);
    }
  };

  std::unique_ptr<SDL_Renderer, deleter> m_renderer;
  frect m_translationViewport;
  std::map<std::size_t, font> m_fonts;

  [[nodiscard]] static constexpr auto default_flags() noexcept
      -> SDL_RendererFlags
  {
    return static_cast<SDL_RendererFlags>(SDL_RENDERER_ACCELERATED |
                                          SDL_RENDERER_PRESENTVSYNC);
  }

  template <typename T>
  [[nodiscard]] auto translate(const basic_point<T>& point) const noexcept
      -> basic_point<T>;

  template <typename T>
  [[nodiscard]] auto translate(const basic_rect<T>& rect) const noexcept
      -> basic_rect<T>;
};

template <typename T>
auto renderer::translate(const basic_point<T>& point) const noexcept
    -> basic_point<T>
{
  const auto rect = viewport();

  using value_type = typename basic_point<T>::value_type;

  const auto x = point.x() - static_cast<value_type>(rect.x());
  const auto y = point.y() - static_cast<value_type>(rect.y());

  return basic_point<T>{x, y};
}

template <typename T>
auto renderer::translate(const basic_rect<T>& rect) const noexcept
    -> basic_rect<T>
{
  return basic_rect<T>{translate(rect.position()), rect.size()};
}

template <typename T>
void renderer::draw_rect_t(const basic_rect<T>& rect) noexcept
{
  draw_rect(translate(rect));
}

template <typename T>
void renderer::fill_rect_t(const basic_rect<T>& rect) noexcept
{
  fill_rect(translate(rect));
}

template <typename T>
void renderer::render_t(const texture& texture,
                        const basic_point<T>& position) noexcept
{
  render(texture, translate(position));
}

template <typename T>
void renderer::render_t(const texture& texture,
                        const basic_rect<T>& destination) noexcept
{
  render(texture, translate(destination));
}

template <typename T>
void renderer::render_t(const texture& texture,
                        const irect& source,
                        const basic_rect<T>& destination) noexcept
{
  render(texture, source, translate(destination));
}

template <typename T>
void renderer::render_t(const texture& texture,
                        const irect& source,
                        const basic_rect<T>& destination,
                        double angle) noexcept
{
  render(texture, source, translate(destination), angle);
}

template <typename R, typename P>
void renderer::render_t(const texture& texture,
                        const irect& source,
                        const basic_rect<R>& destination,
                        double angle,
                        const basic_point<P>& center) noexcept
{
  render(texture, source, translate(destination), angle, center);
}

template <typename R, typename P>
void renderer::render_t(const texture& texture,
                        const irect& source,
                        const basic_rect<R>& destination,
                        double angle,
                        const basic_point<P>& center,
                        SDL_RendererFlip flip) noexcept
{
  render(texture, source, translate(destination), angle, center, flip);
}

template <typename... Args>
void renderer::emplace_font(font_id id, Args&&... args)
{
  if (m_fonts.find(id) != m_fonts.end()) {
    remove_font(id);
  }
  m_fonts.emplace(id, font{std::forward<Args>(args)...});
}

/**
 * @brief Returns a textual representation of a renderer.
 *
 * @ingroup graphics
 *
 * @param renderer the renderer that will be converted.
 *
 * @return a textual representation of the renderer.
 *
 * @since 5.0.0
 */
CENTURION_QUERY
auto to_string(const renderer& renderer) -> std::string;

/**
 * @brief Prints a textual representation of a renderer.
 *
 * @ingroup graphics
 *
 * @param stream the stream that will be used.
 * @param renderer the renderer that will be printed.
 *
 * @return the used stream.
 *
 * @since 5.0.0
 */
CENTURION_QUERY
auto operator<<(std::ostream& stream, const renderer& renderer)
    -> std::ostream&;

}  // namespace cen

#endif  // CENTURION_RENDERER_HEADER