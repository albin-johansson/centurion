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
 * @brief Provides the `renderer` and `renderer_view` classes.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_RENDERER_HEADER
#define CENTURION_RENDERER_HEADER

#include <hashed_string.hpp>

#include "centurion_api.hpp"
#include "colors.hpp"
#include "error.hpp"
#include "font.hpp"
#include "renderer_base.hpp"
#include "window.hpp"

namespace centurion {

/**
 * @class renderer
 * @brief Represents an owning renderer.
 *
 * @details This class is designed to the main class used for
 * hardware-accelerated rendering. However, there is also the
 * `renderer_view` that can be used if you don't want the renderer to claim
 * ownership of the `SDL_Renderer` pointer.
 *
 * @par Rendering textures
 * There are quite a number of methods provided for rendering `texture`
 * instances. There are two overload sets, `render` and `render_t`. These
 * methods can be used with either integer or floating-point accuracy. The
 * recommended general-purpose method for rendering textures is
 * `render(const texture&, const rect_i&, const basic_rect<T>&)`.
 *
 * @par Translation
 * Most games utilize some sort of viewport of what the player can see of the
 * game world. If you're game features some sort of movable anchor for the
 * rendering, then you need to translate the positions of the various game
 * objects when rendering. This class provides a simple API for dealing with
 * this easily. Specify the translation viewport with
 * `set_translation_viewport(const rect_f&)`, and use the rendering methods
 * that feature the `_t` suffix in their names, such as `render_t`, to
 * automatically render at translated positions.
 *
 * @par Font support
 * When rendering text, it's often needed to pass around various font
 * instances. Subsequently, this class provides an API for storing shared
 * pointers to `Font` instances. The fonts are stored in an internal map, and
 * it's possible to specify what you want to use as keys for the fonts. The
 * `renderer` alias uses `std::string` for keys.
 *
 * @par Rendering text
 * There is no method for directly rendering text. Instead, use one of the
 * `text_` methods for creating a texture that contains a rendered piece
 * of text, and render that texture when needed. Naturally, you should cache
 * these textures instead of creating and destroying them in your game loop.
 *
 * @par Examples
 * Below is an example of a typical rendering method.
 * @code{.cpp}
 * #include <centurion_as_ctn.hpp>
 * #include <graphics.hpp>
 *
 * void draw(ctn::renderer& renderer)
 * {
 *   renderer.clear_with(ctn::black); // clear rendering target
 *
 *   // Miscellaneous rendering calls...
 *
 *   renderer.present(); // apply the rendering operations to the target
 * }
 * @endcode
 *
 * @tparam FontKey the key type used when storing associated fonts in a map.
 *
 * @since 3.0.0
 *
 * @see `SDL_Renderer`
 * @see `renderer_view`
 *
 * @headerfile graphics.hpp
 */
class renderer final : public renderer_base {
 public:
  /**
   * @brief Creates a renderer based on the supplied `SDL_Renderer`.
   *
   * @param renderer a pointer to the `SDL_Renderer` that will be used by the
   * renderer.
   *
   * @throws centurion_exception if the supplied pointer is null.
   *
   * @since 3.0.0
   */
  explicit renderer(gsl::owner<SDL_Renderer*> sdlRenderer)
  {
    if (!sdlRenderer) {
      czstring msg = "Can't create renderer from null SDL_Renderer!";
      throw centurion_exception{msg};
    }
    m_renderer = sdlRenderer;

    set_color(colors::black);
    set_logical_integer_scale(false);
  }

  /**
   * @brief Creates a renderer based on the supplied window.
   *
   * @details By default, the internal renderer will be created using the
   * `SDL_RENDERER_ACCELERATED` and `SDL_RENDERER_PRESENTVSYNC` flags.
   *
   * @param window the associated window instance.
   * @param flags the renderer flags that will be used.
   *
   * @throws centurion_exception if something goes wrong when creating the
   * Renderer.
   *
   * @since 4.0.0
   */
  explicit renderer(const window& window,
                    SDL_RendererFlags flags = defaultFlags)

  {
    m_renderer = SDL_CreateRenderer(window.get(), -1, flags);
    if (!m_renderer) {
      throw detail::core_error("Failed to create Renderer!");
    }

    set_blend_mode(blend_mode::blend);
    set_color(colors::black);
    set_logical_integer_scale(false);
  }

  /**
   * @brief Creates a renderer by moving the supplied renderer into the new
   * one.
   *
   * @param other the renderer that will be moved.
   */
  renderer(renderer&& other) noexcept { move(std::move(other)); }

  renderer(const renderer&) = delete;

  /**
   * @brief Moves the supplied renderer into this renderer.
   *
   * @param other the renderer that will be moved.
   *
   * @return the renderer that claimed the supplied renderer.
   */
  auto operator=(renderer&& other) noexcept -> renderer&
  {
    if (this != &other) {
      move(std::move(other));
    }
    return *this;
  }

  auto operator=(const renderer&) -> renderer& = delete;

  ~renderer() noexcept { destroy(); }

  /**
   * @copydoc renderer(gsl::owner<SDL_Renderer*>)
   */
  [[nodiscard]] static auto unique(gsl::owner<SDL_Renderer*> sdlRenderer)
      -> std::unique_ptr<renderer>
  {
    return std::make_unique<renderer>(sdlRenderer);
  }

  /**
   * @copydoc renderer(const window&, SDL_RendererFlags)
   */
  [[nodiscard]] static auto unique(const window& window,
                                   SDL_RendererFlags flags = defaultFlags)
      -> std::unique_ptr<renderer>
  {
    return std::make_unique<renderer>(window, flags);
  }

  /**
   * @copydoc renderer(gsl::owner<SDL_Renderer*>)
   */
  [[nodiscard]] static auto shared(gsl::owner<SDL_Renderer*> sdlRenderer)
      -> std::shared_ptr<renderer>
  {
    return std::make_shared<renderer>(sdlRenderer);
  }

  /**
   * @copydoc renderer(const window&, SDL_RendererFlags)
   */
  [[nodiscard]] static auto shared(const window& window,
                                   SDL_RendererFlags flags = defaultFlags)
      -> std::shared_ptr<renderer>
  {
    return std::make_shared<renderer>(window, flags);
  }

  /**
   * @brief Adds a font to the renderer.
   *
   * @details This method has no effect if the renderer already has a font
   * associated with the specified key or if the supplied font is null.
   *
   * @param id the key that will be associated with the font.
   * @param font the font that will be added, can safely be null.
   *
   * @since 5.0.0
   */
  void add_font(entt::id_type id, const std::shared_ptr<font>& font)
  {
    if (!m_fonts.count(id)) {
      m_fonts.emplace(id, font);
    }
  }

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
  void remove_font(entt::id_type id) { m_fonts.erase(id); }

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
  void set_translation_viewport(const rect_f& viewport) noexcept
  {
    m_translationViewport = viewport;
  }

  /**
   * @brief Renders an outlined rectangle in the currently selected color.
   *
   * @details The rendered rectangle will be translated using the current
   * translation viewport.
   *
   * @tparam T The type of the rectangle coordinates. Must be either `int` or
   * `float`.
   *
   * @param rect the rectangle that will be rendered.
   *
   * @since 4.1.0
   */
  template <typename T>
  void draw_rect_t(const basic_rect<T>& rect) noexcept
  {
    draw_rect(translate(rect));
  }

  /**
   * @brief Renders a filled rectangle in the currently selected color.
   *
   * @details The rendered rectangle will be translated using the current
   * translation viewport.
   *
   * @tparam T The type of the rectangle coordinates. Must be either `int` or
   * `float`.
   *
   * @param rect the rectangle that will be rendered.
   *
   * @since 4.1.0
   */
  template <typename T>
  void fill_rect_t(const basic_rect<T>& rect) noexcept
  {
    fill_rect(translate(rect));
  }

  /**
   * @brief Renders a texture at the specified position.
   *
   * @details The rendered texture will be translated using the translation
   * viewport.
   *
   * @tparam T The type of the point coordinates. Must be either `int` or
   * `float`.
   *
   * @param texture the texture that will be rendered.
   * @param position the position (pre-translation) of the rendered texture.
   *
   * @since 4.0.0
   */
  template <typename T>
  void render_t(const texture& texture, const basic_point<T>& position) noexcept
  {
    render(texture, translate(position));
  }

  /**
   * @brief Renders a texture according to the specified rectangle.
   *
   * @details The rendered texture will be translated using the translation
   * viewport.
   *
   * @tparam T The type of the rectangle coordinates. Must be either `int` or
   * `float`.
   *
   * @param texture the texture that will be rendered.
   * @param destination the position (pre-translation) and size of the
   * rendered texture.
   *
   * @since 4.0.0
   */
  template <typename T>
  void render_t(const texture& texture,
                const basic_rect<T>& destination) noexcept
  {
    render(texture, translate(destination));
  }

  /**
   * @brief Renders a texture.
   *
   * @details The rendered texture will be translated using the translation
   * viewport.
   *
   * @remarks This should be your preferred method of rendering textures. This
   * method is efficient and simple.
   *
   * @tparam T The type of the rectangle coordinates. Must be either `int` or
   * `float`.
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
                const rect_i& source,
                const basic_rect<T>& destination) noexcept
  {
    render(texture, source, translate(destination));
  }

  /**
   * @brief Renders a texture.
   *
   * @details The rendered texture will be translated using the translation
   * viewport.
   *
   * @tparam T The type of the rectangle coordinates. Must be either `int` or
   * `float`.
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
                const rect_i& source,
                const basic_rect<T>& destination,
                double angle) noexcept
  {
    render(texture, source, translate(destination), angle);
  }

  /**
   * @brief Renders a texture.
   *
   * @details The rendered texture will be translated using the translation
   * viewport.
   *
   * @tparam T The type of the rectangle coordinates. Must be either `int` or
   * `float`.
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
  template <typename T>
  void render_t(const texture& texture,
                const rect_i& source,
                const basic_rect<T>& destination,
                double angle,
                const basic_point<T>& center) noexcept
  {
    render(texture, source, translate(destination), angle, center);
  }

  /**
   * @brief Renders a texture.
   *
   * @tparam T The type of the rectangle coordinates. Must be either `int` or
   * `float`.
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
  template <typename T>
  void render_t(const texture& texture,
                const rect_i& source,
                const basic_rect<T>& destination,
                double angle,
                const basic_point<T>& center,
                SDL_RendererFlip flip) noexcept
  {
    render(texture, source, translate(destination), angle, center, flip);
  }

  /**
   * @brief Returns the font associated with the specified name.
   *
   * @details This method returns null if there is no font associated with
   * the specified name.
   *
   * @param id the key associated with the desired font.
   *
   * @return the font associated with the specified name; `nullptr` if there
   * is no such font.
   *
   * @since 4.1.0
   */
  [[nodiscard]] auto font(entt::id_type id) noexcept -> std::shared_ptr<font>
  {
    // TODO throw if no font is found

    if (m_fonts.count(id)) {
      return m_fonts.at(id);
    } else {
      return nullptr;
    }
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
  [[nodiscard]] auto has_font(entt::id_type id) const noexcept -> bool
  {
    return static_cast<bool>(m_fonts.count(id));
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
  [[nodiscard]] auto translation_viewport() const noexcept -> const rect_f&
  {
    return m_translationViewport;
  }

  /**
   * @brief Creates and returns a texture of blended text.
   *
   * @details Attempts to render the specified text in the supplied font using
   * the currently selected color and return the texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen. This method doesn't throw but might return null if something
   * goes wrong.
   *
   * This method renders the text at the highest quality and uses
   * anti-aliasing. Use this when you want high quality text, but beware that
   * this is the slowest alternative.
   *
   * @param text the text that will be rendered, can safely be null.
   * @param font the font that the text will be rendered in.
   *
   * @return a unique pointer to a texture that contains the rendered text;
   * `nullptr` if something went wrong.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto text_blended(czstring text,
                                  const centurion::font& font) const noexcept
      -> std::unique_ptr<texture>;

  /**
   * @brief Creates and returns a texture of blended and wrapped text.
   *
   * @details Attempts to render the specified text in the supplied font using
   * the currently selected color and return the texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen. This method doesn't throw but might return null if something
   * goes wrong.
   *
   * This method renders the text at the highest quality and uses
   * anti-aliasing. Use this when you want high quality text, but beware that
   * this is the slowest alternative. This method will wrap the supplied text
   * to fit the specified width. Furthermore, you can also manually control
   * the line breaks by inserting newline characters at the desired
   * breakpoints.
   *
   * @param text the text that will be rendered. You can insert newline
   * characters in the string to indicate breakpoints, can safely be null.
   * @param wrap the width in pixels which marks the point that the text will
   * be wrapped after.
   * @param font the font that the text will be rendered in.
   *
   * @return a unique pointer to a texture that contains the rendered text;
   * `nullptr` if something went wrong.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto text_blended_wrapped(
      czstring text,
      u32 wrap,
      const centurion::font& font) const noexcept -> std::unique_ptr<texture>;

  /**
   * @brief Creates and returns a texture of shaded text.
   *
   * @details Attempts to render the specified text in the supplied font using
   * the currently selected color and return the texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen. This method doesn't throw but might return null if something
   * goes wrong.
   *
   * This method renders the text using anti-aliasing and with a box
   * behind the text. This alternative is probably a bit slower than
   * rendering solid text but about as fast as blended text. Use this
   * method when you want nice text, and can live with a box around it.
   *
   * @param text the text that will be rendered, can safely be null.
   * @param bg the background color used for the box.
   * @param font the font that the text will be rendered in.
   *
   * @return a unique pointer to a texture that contains the rendered text;
   * `nullptr` if something went wrong.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto text_shaded(czstring text,
                                 const color& bg,
                                 const centurion::font& font) const noexcept
      -> std::unique_ptr<texture>;

  /**
   * @brief Creates and returns a texture of solid text.
   *
   * @details Attempts to render the specified text in the supplied font using
   * the currently selected color and return the texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen. This method doesn't throw but might return null if something goes
   * wrong.
   *
   * This method is the fastest at rendering text to a texture. It
   * doesn't use anti-aliasing so the text isn't very smooth. Use this method
   * when quality isn't as big of a concern and speed is important.
   *
   * @param text the text that will be rendered, can safely be null.
   * @param font the font that the text will be rendered in.
   *
   * @return a unique pointer to a texture that contains the rendered text;
   * `nullptr` if something went wrong.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto text_solid(czstring text,
                                const centurion::font& font) const noexcept
      -> std::unique_ptr<texture>;

 private:
  rect_f m_translationViewport;
  std::unordered_map<entt::id_type, std::shared_ptr<class font>> m_fonts;

  static inline constexpr auto defaultFlags = static_cast<SDL_RendererFlags>(
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  /**
   * @brief Destroys the resources associated with the renderer.
   *
   * @since 4.0.0
   */
  void destroy() noexcept
  {
    auto* renderer = this->get();
    if (renderer) {
      SDL_DestroyRenderer(renderer);
    }
  }

  /**
   * @brief Moves the contents of the supplied renderer instance into this
   * instance.
   *
   * @param other the instance that will be moved.
   *
   * @since 4.0.0
   */
  void move(renderer&& other) noexcept
  {
    destroy();

    renderer_base::m_renderer = other.m_renderer;
    m_translationViewport = other.m_translationViewport;

    other.m_renderer = nullptr;
  }

  /**
   * @brief A helper method used by text rendering methods to create surfaces
   * based on the text and then convert it to fast textures.
   *
   * @param text the text that will be rendered.
   * @param render a lambda with `void(SDL_Surface*, czstring)` as its
   * signature.
   *
   * @return a unique pointer to a texture; `nullptr` if something went wrong.
   *
   * @since 4.0.0
   */
  template <typename Lambda>
  [[nodiscard]] auto render_text(czstring text, Lambda&& render) const noexcept
      -> std::unique_ptr<texture>
  {
    if (!text) {
      return nullptr;
    }

    SDL_Surface* surface = render(text);
    if (!surface) {
      return nullptr;
    }

    auto* sdlTexture = SDL_CreateTextureFromSurface(this->get(), surface);
    SDL_FreeSurface(surface);

    if (sdlTexture) {
      return std::make_unique<texture>(sdlTexture);
    } else {
      return nullptr;
    }
  }

  /**
   * @brief Returns the translated x-coordinate that corresponds to the
   * supplied x-coordinate.
   *
   * @param x the x-coordinate that will be translated.
   *
   * @return the translated x-coordinate that corresponds to the supplied
   * x-coordinate.
   *
   * @since 4.1.0
   */
  template <typename T>
  [[nodiscard]] auto tx(T x) const noexcept -> T
  {
    SDL_Rect vp{};
    SDL_RenderGetViewport(m_renderer, &vp);

    if constexpr (std::is_same_v<T, int>) {
      return x - static_cast<T>(vp.x);
    } else {
      return x - vp.x;
    }
  }

  /**
   * @brief Returns the translated y-coordinate that corresponds to the
   * supplied y-coordinate.
   *
   * @param y the y-coordinate that will be translated.
   *
   * @return the translated y-coordinate that corresponds to the supplied
   * y-coordinate.
   *
   * @since 4.1.0
   */
  template <typename T>
  [[nodiscard]] auto ty(T y) const noexcept -> T
  {
    SDL_Rect vp{};
    SDL_RenderGetViewport(m_renderer, &vp);

    if constexpr (std::is_same_v<T, int>) {
      return y - static_cast<T>(vp.y);
    } else {
      return y - vp.y;
    }
  }

  template <typename T>
  [[nodiscard]] auto translate(const basic_point<T>& point) const noexcept
      -> basic_point<T>
  {
    return basic_point<T>{tx(point.x()), ty(point.y())};
  }

  template <typename T>
  [[nodiscard]] auto translate(const basic_rect<T>& rect) const noexcept
      -> basic_rect<T>
  {
    return {translate(rect.position()), rect.size()};
  }
};

/**
 * @class renderer_view
 *
 * @brief Represents a non-owning renderer.
 *
 * @details This class is meant to be used when you want to utilize the same
 * rendering API as with the the `renderer` class, but you don't want the
 * renderer to claim ownership of the SDL renderer. In a nutshell, this class
 * is merely a wrapper around an `SDL_Renderer*`.
 *
 * However, there are some differences in functionality compared to the
 * `renderer` class. Firstly, renderer views don't support storing
 * fonts. Secondly, the translation viewport API isn't available with views.
 *
 * @note Naturally, since instances of this class don't own the associated
 * SDL renderer, you'll have to manually manage the lifetime of the
 * SDL renderer. In general, prefer `renderer` unless you absolutely cannot
 * claim ownership of the SDL renderer.
 *
 * @par Examples
 * The following example displays how one could utilize this class to take
 * advantage of the Centurion rendering API, that wouldn't be possible with
 * `renderer`.
 * @code{.cpp}
 *   #include <centurion_as_ctn.hpp>
 *   #include <graphics.hpp>
 *
 *   // Assume that we can't change the parameter of this method
 *   void draw(SDL_Renderer* renderer)
 *   {
 *     ctn::renderer_view view{renderer};
 *
 *     view.clear_with(ctn::black);
 *
 *     view.set_color(ctn::pink);
 *     view.fill_rect(ctn::rect_i{{15, 20}, {100, 100}});
 *
 *     view.present();
 *   }
 * @endcode
 *
 * @since 5.0.0
 *
 * @see `renderer`
 *
 * @headerfile graphics.hpp
 */
class renderer_view final : public renderer_base {
 public:
  /**
   * @brief Creates a renderer view instance.
   *
   * @param renderer a pointer to the SDL renderer that will be used, mustn't
   * be null.
   *
   * @since 5.0.0
   */
  explicit renderer_view(gsl::not_null<SDL_Renderer*> renderer) noexcept
      : renderer_base{renderer}
  {}

  /**
   * @brief Creates a view based on an existing `renderer`.
   *
   * @tparam FontKey the type of the font keys used by the renderer.
   *
   * @param renderer the renderer that will be viewed.
   *
   * @since 5.0.0
   */
  explicit renderer_view(const renderer& renderer) noexcept
      : renderer_base{renderer.get()}
  {}
};

inline auto renderer::text_blended(czstring text,
                                   const centurion::font& font) const noexcept
    -> std::unique_ptr<texture>
{
  return render_text(text, [this, &font](czstring text) noexcept {
    return TTF_RenderText_Blended(
        font.get(), text, static_cast<SDL_Color>(get_color()));
  });
}

inline auto renderer::text_blended_wrapped(
    czstring text,
    const u32 wrap,
    const centurion::font& font) const noexcept -> std::unique_ptr<texture>
{
  return render_text(text, [this, &font, wrap](czstring text) noexcept {
    return TTF_RenderText_Blended_Wrapped(
        font.get(), text, static_cast<SDL_Color>(get_color()), wrap);
  });
}

inline auto renderer::text_shaded(czstring text,
                                  const color& bg,
                                  const centurion::font& font) const noexcept
    -> std::unique_ptr<texture>
{
  return render_text(text, [this, &font, &bg](czstring text) noexcept {
    return TTF_RenderText_Shaded(font.get(),
                                 text,
                                 static_cast<SDL_Color>(get_color()),
                                 static_cast<SDL_Color>(bg));
  });
}

inline auto renderer::text_solid(czstring text,
                                 const centurion::font& font) const noexcept
    -> std::unique_ptr<texture>
{
  return render_text(text, [this, &font](czstring text) noexcept {
    return TTF_RenderText_Solid(
        font.get(), text, static_cast<SDL_Color>(get_color()));
  });
}

}  // namespace centurion

#endif  // CENTURION_RENDERER_HEADER