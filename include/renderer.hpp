///*
// * MIT License
// *
// * Copyright (c) 2019-2020 Albin Johansson
// *
// * Permission is hereby granted, free of charge, to any person obtaining a
// copy
// * of this software and associated documentation files (the "Software"), to
// deal
// * in the Software without restriction, including without limitation the
// rights
// * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// * copies of the Software, and to permit persons to whom the Software is
// * furnished to do so, subject to the following conditions:
// *
// * The above copyright notice and this permission notice shall be included in
// * all copies or substantial portions of the Software.
// *
// * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM,
// * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE
// * SOFTWARE.
// */
//
///**
// * @brief Provides the rendering API.
// *
// * @file renderer.hpp
// * @author Albin Johansson
// * @copyright MIT License
// * @date 2019-2020
// */
//
//#ifndef CENTURION_RENDERER_HEADER
//#define CENTURION_RENDERER_HEADER
//
//#include <SDL.h>
//#include <SDL_image.h>
//
//#include <string_view>
//#include <unordered_map>
//#include <vector>
//
//#include "area.hpp"
//#include "blend_mode.hpp"
//#include "centurion_api.hpp"
//#include "centurion_exception.hpp"
//#include "centurion_fwd.hpp"
//#include "centurion_utils.hpp"
//#include "color.hpp"
//#include "colors.hpp"
//#include "error.hpp"
//#include "font.hpp"
//#include "point.hpp"
//#include "rect.hpp"
//#include "texture.hpp"
//#include "window.hpp"
//
// namespace centurion {
//
///**
// * @class Renderer
// * @brief Responsible for providing the rendering API.
// *
// * @tparam FontKey the key type used when storing associated fonts in a map.
// *
// *
// * @since 3.0.0
// *
// * @see `SDL_Renderer`
// *
// * @headerfile renderer.hpp
// */
// template <typename FontKey = std::string>
// class Renderer final {  // TODO rename and provide aliases
// public:
//  /**
//   * Creates a renderer based on the supplied SDL_Renderer.
//   *
//   * @param renderer a pointer to the SDL_Renderer that will be used by the
//   * renderer.
//   * @throws CenturionException if the supplied pointer is null.
//   * @since 3.0.0
//   */
//  explicit Renderer(gsl::owner<SDL_Renderer*> renderer)
//  {
//    if (!renderer) {
//      throw CenturionException{"Can't create renderer from null
//      SDL_Renderer!"};
//    }
//    this->m_renderer = renderer;
//
//    set_color(color::black);
//    set_logical_integer_scale(false);
//  }
//
//  /**
//   * Creates a renderer based on the supplied window. By default, the
//   * internal renderer will be created using the SDL_RENDERER_ACCELERATED and
//   * SDL_RENDERER_PRESENTVSYNC flags.
//   *
//   * @param window the associated window instance.
//   * @param flags the renderer flags that will be used.
//   * @throws CenturionException if something goes wrong when creating the
//   * Renderer.
//   * @since 4.0.0
//   */
//  explicit Renderer(const Window& window,
//                    SDL_RendererFlags flags = defaultFlags)
//  {
//    m_renderer = SDL_CreateRenderer(window.get(), -1, flags);
//    if (!m_renderer) {
//      throw detail::Error::from_core("Failed to create Renderer!");
//    }
//
//    set_blend_mode(BlendMode::Blend);
//    set_color(color::black);
//    set_logical_integer_scale(false);
//  }
//
//  Renderer(Renderer&& other) noexcept { move(std::move(other)); }
//
//  Renderer(const Renderer&) noexcept = delete;
//
//  auto operator=(Renderer&& other) noexcept -> Renderer&
//  {
//    if (this != &other) {
//      move(std::move(other));
//    }
//    return *this;
//  }
//
//  auto operator=(const Renderer&) noexcept -> Renderer& = delete;
//
//  ~Renderer() noexcept { destroy(); }
//
//  /**
//   * Creates and returns a unique pointer to a renderer.
//   *
//   * @param renderer a raw pointer to the SDL_Renderer that the created
//   renderer
//   * will be based on, may not be null.
//   * @return a unique pointer to a renderer.
//   * @throws CenturionException if the supplied renderer is null.
//   * @since 3.0.0
//   */
//  [[nodiscard]] static auto unique(gsl::owner<SDL_Renderer*> renderer)
//      -> std::unique_ptr<Renderer>
//  {
//    return std::make_unique<Renderer>(renderer);
//  }
//
//  /**
//   * Creates and returns a unique pointer to a renderer instance.
//   *
//   * @param window the associated window instance.
//   * @param flags the renderer flags that will be used.
//   * @return a unique pointer to a renderer instance.
//   * @throws CenturionException if something goes wrong when creating the
//   * Renderer.
//   * @since 4.0.0
//   */
//  [[nodiscard]] static auto unique(const Window& window,
//                                   SDL_RendererFlags flags = defaultFlags)
//      -> std::unique_ptr<Renderer>
//  {
//    return std::make_unique<Renderer>(window, flags);
//  }
//
//  /**
//   * Creates and returns a shared pointer to a renderer.
//   *
//   * @param renderer a raw pointer to the SDL_Renderer that the created
//   * renderer will be based on, may not be null.
//   * @return a shared pointer to a renderer.
//   * @throws CenturionException if the supplied renderer is null.
//   * @since 3.0.0
//   */
//  [[nodiscard]] static auto shared(gsl::owner<SDL_Renderer*> renderer)
//      -> std::shared_ptr<Renderer>
//  {
//    return std::make_shared<Renderer>(renderer);
//  }
//
//  /**
//   * Creates and returns a shared pointer to a renderer instance.
//   *
//   * @param window the associated window instance.
//   * @param flags the renderer flags that will be used.
//   * @return a shared pointer to a renderer instance.
//   * @throws CenturionException if something goes wrong when creating the
//   * Renderer.
//   * @since 4.0.0
//   */
//  [[nodiscard]] static auto shared(const Window& window,
//                                   SDL_RendererFlags flags = defaultFlags)
//      -> std::shared_ptr<Renderer>
//  {
//    return std::make_shared<Renderer>(window, flags);
//  }
//
//  /**
//   * Clears the rendering target with the currently selected color.
//   *
//   * @since 3.0.0
//   */
//  void clear() noexcept { SDL_RenderClear(m_renderer); }
//
//  /**
//   * Applies the previous rendering calls to the rendering target.
//   *
//   * @since 3.0.0
//   */
//  void present() noexcept { SDL_RenderPresent(m_renderer); }
//
//  void add_font(FontKey&& key, const std::shared_ptr<Font>& font)
//  {
//    if (!m_fonts.count(key)) {
//      m_fonts.emplace(key, font);
//    }
//  }
//
//  void remove_font(FontKey&& key) { m_fonts.erase(key); }
//
//  template <typename T>
//  void draw_rect(const Rect<T>& rect) noexcept
//  {
//    static_assert(std::is_same_v<T, float> || std::is_same_v<T, int>);
//
//    if constexpr (std::is_same_v<T, int>) {
//      SDL_RenderDrawRect(m_renderer, static_cast<const SDL_Rect*>(rect));
//    } else {
//      SDL_RenderDrawRectF(m_renderer, static_cast<const SDL_FRect*>(rect));
//    }
//  }
//
//  template <typename T>
//  void fill_rect(const Rect<T>& rect) noexcept
//  {
//    static_assert(std::is_same_v<T, float> || std::is_same_v<T, int>);
//
//    if constexpr (std::is_same_v<T, int>) {
//      SDL_RenderFillRect(m_renderer, static_cast<const SDL_Rect*>(rect));
//    } else {
//      SDL_RenderFillRectF(m_renderer, static_cast<const SDL_FRect*>(rect));
//    }
//  }
//
//  template <typename T>
//  void draw_rect_t(const Rect<T>& rect) noexcept
//  {
//    draw_rect(translate(rect));
//  }
//
//  template <typename T>
//  void fill_rect_t(const Rect<T>& rect) noexcept
//  {
//    fill_rect(translate(rect));
//  }
//
//  template <typename T>
//  void draw_line(const Point<T>& start, const Point<T>& end) noexcept
//  {
//    static_assert(std::is_same_v<T, float> || std::is_same_v<T, int>);
//
//    if constexpr (std::is_same_v<T, int>) {
//      SDL_RenderDrawLine(m_renderer, start.x(), start.y(), end.x(), end.y());
//    } else {
//      SDL_RenderDrawLineF(m_renderer, start.x(), start.y(), end.x(), end.y());
//    }
//  }
//
//  /**
//   * @brief Renders a collection of lines.
//   *
//   * @warning `Container` *must* be a collection that stores its data
//   * contiguously! The behaviour of this method is undefined if this condition
//   * isn't met.
//   *
//   * @tparam Container the container type. Must store its elements
//   * contiguously, such as `std::vector` or `std::array`.
//   * @tparam T the type of the point coordinates. Must be either `int` or
//   * `float`.
//   *
//   * @param container the container that holds the points that will be used
//   * to render the line.
//   *
//   * @since 5.0.0
//   */
//  template <typename Container, typename T>
//  void draw_lines(Container&& container) noexcept
//  {
//    static_assert(std::is_same_v<T, float> || std::is_same_v<T, int>);
//
//    if (!container.empty()) {
//      const Point<T>& front = container.front();
//
//      if constexpr (std::is_same_v<T, int>) {
//        const auto* first = static_cast<const SDL_Point*>(front);
//        SDL_RenderDrawLines(m_renderer, first, container.size());
//      } else {
//        const auto* first = static_cast<const SDL_FPoint*>(front);
//        SDL_RenderDrawLinesF(m_renderer, first, container.size());
//      }
//    }
//  }
//
//  template <typename T>
//  void render(const Texture& texture, const Point<T>& position) noexcept
//  {
//    static_assert(std::is_same_v<T, float> || std::is_same_v<T, int>);
//
//    if constexpr (std::is_same_v<T, int>) {
//      const SDL_Rect dst{
//          position.x(), position.y(), texture.width(), texture.height()};
//      SDL_RenderCopy(m_renderer, texture.get(), nullptr, &dst);
//    } else {
//      const SDL_FRect dst{
//          position.x(), position.y(), texture.width(), texture.height()};
//      SDL_RenderCopyF(m_renderer, texture.get(), nullptr, &dst);
//    }
//  }
//
//  template <typename T>
//  void render(const Texture& texture, const Rect<T>& destination) noexcept
//  {
//    static_assert(std::is_same_v<T, float> || std::is_same_v<T, int>);
//
//    if constexpr (std::is_same_v<T, int>) {
//      SDL_RenderCopy(m_renderer,
//                     texture.get(),
//                     nullptr,
//                     static_cast<const SDL_Rect*>(destination));
//    } else {
//      SDL_RenderCopyF(m_renderer,
//                      texture.get(),
//                      nullptr,
//                      static_cast<const SDL_FRect*>(destination));
//    }
//  }
//
//  template <typename T>
//  void render(const Texture& texture,
//              const IRect& source,
//              const Rect<T>& destination) noexcept
//  {
//    static_assert(std::is_same_v<T, float> || std::is_same_v<T, int>);
//
//    if constexpr (std::is_same_v<T, int>) {
//      SDL_RenderCopy(m_renderer,
//                     texture.get(),
//                     static_cast<const SDL_Rect*>(source),
//                     static_cast<const SDL_Rect*>(destination));
//    } else {
//      SDL_RenderCopyF(m_renderer,
//                      texture.get(),
//                      static_cast<const SDL_Rect*>(source),
//                      static_cast<const SDL_FRect*>(destination));
//    }
//  }
//
//  template <typename T>
//  void render(const Texture& texture,
//              const IRect& source,
//              const Rect<T>& destination,
//              const double angle) noexcept
//  {
//    static_assert(std::is_same_v<T, float> || std::is_same_v<T, int>);
//
//    if constexpr (std::is_same_v<T, int>) {
//      SDL_RenderCopyEx(m_renderer,
//                       texture.get(),
//                       static_cast<const SDL_Rect*>(source),
//                       static_cast<const SDL_Rect*>(destination),
//                       angle,
//                       nullptr,
//                       SDL_FLIP_NONE);
//    } else {
//      SDL_RenderCopyExF(m_renderer,
//                        texture.get(),
//                        static_cast<const SDL_Rect*>(source),
//                        static_cast<const SDL_FRect*>(destination),
//                        angle,
//                        nullptr,
//                        SDL_FLIP_NONE);
//    }
//  }
//
//  template <typename T>
//  void render(const Texture& texture,
//              const IRect& source,
//              const Rect<T>& destination,
//              const double angle,
//              const Point<T>& center) noexcept
//  {
//    static_assert(std::is_same_v<T, float> || std::is_same_v<T, int>);
//
//    if constexpr (std::is_same_v<T, int>) {
//      SDL_RenderCopyEx(m_renderer,
//                       texture.get(),
//                       static_cast<const SDL_Rect*>(source),
//                       static_cast<const SDL_Rect*>(destination),
//                       angle,
//                       static_cast<const SDL_Point*>(center),
//                       SDL_FLIP_NONE);
//    } else {
//      SDL_RenderCopyExF(m_renderer,
//                        texture.get(),
//                        static_cast<const SDL_Rect*>(source),
//                        static_cast<const SDL_FRect*>(destination),
//                        angle,
//                        static_cast<const SDL_FPoint*>(center),
//                        SDL_FLIP_NONE);
//    }
//  }
//
//  template <typename T>
//  void render(const Texture& texture,
//              const IRect& source,
//              const Rect<T>& destination,
//              const double angle,
//              const Point<T>& center,
//              const SDL_RendererFlip flip) noexcept
//  {
//    static_assert(std::is_same_v<T, float> || std::is_same_v<T, int>);
//
//    if constexpr (std::is_same_v<T, int>) {
//      SDL_RenderCopyEx(m_renderer,
//                       texture.get(),
//                       static_cast<const SDL_Rect*>(source),
//                       static_cast<const SDL_Rect*>(destination),
//                       angle,
//                       static_cast<const SDL_Point*>(center),
//                       flip);
//    } else {
//      SDL_RenderCopyExF(m_renderer,
//                        texture.get(),
//                        static_cast<const SDL_Rect*>(source),
//                        static_cast<const SDL_FRect*>(destination),
//                        angle,
//                        static_cast<const SDL_FPoint*>(center),
//                        flip);
//    }
//  }
//
//  template <typename T>
//  void render_t(const Texture& texture, const Point<T>& position) noexcept
//  {
//    render(texture, {tx(position.x()), ty(position.y())});
//  }
//
//  template <typename T>
//  void render_t(const Texture& texture, const Rect<T>& destination) noexcept
//  {
//    render(texture, translate(destination));
//  }
//
//  template <typename T>
//  void render_t(const Texture& texture,
//                const IRect& source,
//                const Rect<T>& destination) noexcept
//  {
//    render(texture, source, translate(destination));
//  }
//
//  template <typename T>
//  void render_t(const Texture& texture,
//                const IRect& source,
//                const Rect<T>& destination,
//                const double angle) noexcept
//  {
//    render(texture, source, translate(destination), angle);
//  }
//
//  template <typename T>
//  void render_t(const Texture& texture,
//                const IRect& source,
//                const Rect<T>& destination,
//                const double angle,
//                const Point<T>& center) noexcept
//  {
//    render(texture, source, translate(destination), angle, center);
//  }
//
//  template <typename T>
//  void render_t(const Texture& texture,
//                const IRect& source,
//                const Rect<T>& destination,
//                const double angle,
//                const Point<T>& center,
//                const SDL_RendererFlip flip) noexcept
//  {
//    render(texture, source, translate(destination), angle, center, flip);
//  }
//
//  /**
//   * Sets the color that will be used by the renderer.
//   *
//   * @param color the color that will be used by the renderer.
//   * @since 3.0.0
//   */
//  void set_color(const Color& color) noexcept
//  {
//    SDL_SetRenderDrawColor(
//        m_renderer, color.red(), color.green(), color.blue(), color.alpha());
//  }
//
//  /**
//   * Sets the clipping area rectangle. Clipping is disabled by default.
//   *
//   * @param area the clip area rectangle; or nothing to disable clipping.
//   * @since 3.0.0
//   */
//  void set_clip(Optional<IRect> area) noexcept
//  {
//    if (area) {
//      SDL_RenderSetClipRect(m_renderer, static_cast<const SDL_Rect*>(*area));
//    } else {
//      SDL_RenderSetClipRect(m_renderer, nullptr);
//    }
//  }
//
//  /**
//   * Sets the viewport that will be used by the renderer.
//   *
//   * @param viewport the viewport that will be used by the renderer.
//   * @since 3.0.0
//   */
//  void set_viewport(const IRect& viewport) noexcept
//  {
//    SDL_RenderSetViewport(m_renderer, static_cast<const SDL_Rect*>(viewport));
//  }
//
//  /**
//   * Sets the translation viewport that will be used by the renderer. This
//   * method can be used in order to be able to use the various
//   * X_translated-methods.
//   *
//   * @param viewport the rectangle that will be used as the translation
//   * viewport.
//   * @since 3.0.0
//   */
//  void set_translation_viewport(const FRect& viewport) noexcept
//  {
//    m_translationViewport = viewport;
//  }
//
//  /**
//   * Sets the blend mode that will be used by the renderer.
//   *
//   * @param mode the blend mode that will be used by the renderer.
//   * @since 3.0.0
//   */
//  void set_blend_mode(BlendMode mode) noexcept
//  {
//    SDL_SetRenderDrawBlendMode(m_renderer, static_cast<SDL_BlendMode>(mode));
//  }
//
//  /**
//   * Sets the rendering target of the renderer. The supplied image must
//   * support being a render target. Otherwise, this method will reset the
//   * render target.
//   *
//   * @param texture a pointer to the new target texture, can safely be null to
//   * indicate that the default rendering target should be used.
//   * @since 3.0.0
//   */
//  void set_target(const Texture* texture) noexcept
//  {
//    if (texture && texture->is_target()) {
//      SDL_SetRenderTarget(m_renderer, texture->get());
//    } else {
//      SDL_SetRenderTarget(m_renderer, nullptr);
//    }
//  }
//
//  /**
//   * Sets the viewport that will be used by the renderer. This method has no
//   * effect if any of the arguments are less than or equal to zero.
//   *
//   * @param xScale the x-axis scale that will be used.
//   * @param yScale the y-axis scale that will be used.
//   * @since 3.0.0
//   */
//  void set_scale(float xScale, float yScale) noexcept
//  {
//    if (xScale > 0 && yScale > 0) {
//      SDL_RenderSetScale(m_renderer, xScale, yScale);
//    }
//  }
//
//  /**
//   * Sets the logical dimensions of the renderer, which is useful for
//   * achieving resolution-independent rendering. This method has no effect if
//   * either of the supplied dimensions aren't greater than zero.
//   *
//   * @param size the logical width and height that will be used.
//   * @since 3.0.0
//   */
//  void set_logical_size(area_i size) noexcept
//  {
//    if (size.width > 0 && size.height > 0) {
//      SDL_RenderSetLogicalSize(m_renderer, size.width, size.height);
//    }
//  }
//
//  /**
//   * Sets whether or not to force integer scaling for the logical viewport. By
//   * default, this property is set to false.
//   *
//   * @param useLogicalIntegerScale true if integer scaling should be used;
//   * false otherwise.
//   * @since 3.0.0
//   */
//  void set_logical_integer_scale(bool useLogicalIntegerScale) noexcept
//  {
//    SDL_RenderSetIntegerScale(m_renderer,
//                              detail::convert_bool(useLogicalIntegerScale));
//  }
//
//  /**
//   * Returns the logical width that the renderer uses. By default, this
//   * property is set to 0.
//   *
//   * @return the logical width that the renderer uses.
//   * @since 3.0.0
//   */
//  [[nodiscard]] auto logical_width() const noexcept -> int
//  {
//    int width = 0;
//    SDL_RenderGetLogicalSize(m_renderer, &width, nullptr);
//    return width;
//  }
//
//  /**
//   * Returns the logical height that the renderer uses. By default, this
//   * property is set to 0.
//   *
//   * @return the logical height that the renderer uses.
//   * @since 3.0.0
//   */
//  [[nodiscard]] auto logical_height() const noexcept -> int
//  {
//    int height = 0;
//    SDL_RenderGetLogicalSize(m_renderer, nullptr, &height);
//    return height;
//  }
//
//  /**
//   * Returns the x-axis scale that the renderer uses.
//   *
//   * @return the x-axis scale that the renderer uses.
//   * @since 3.0.0
//   */
//  [[nodiscard]] auto x_scale() const noexcept -> float
//  {
//    float xScale = 0;
//    SDL_RenderGetScale(m_renderer, &xScale, nullptr);
//    return xScale;
//  }
//
//  /**
//   * Returns the y-axis scale that the renderer uses.
//   *
//   * @return the y-axis scale that the renderer uses.
//   * @since 3.0.0
//   */
//  [[nodiscard]] auto y_scale() const noexcept -> float
//  {
//    float yScale = 0;
//    SDL_RenderGetScale(m_renderer, nullptr, &yScale);
//    return yScale;
//  }
//
//  /**
//   * Returns the current clipping rectangle, if there is one active.
//   *
//   * @return the current clipping rectangle; or nothing if there is none.
//   * @since 3.0.0
//   */
//  [[nodiscard]] auto clip() const noexcept -> Optional<IRect>
//  {
//    IRect rect;
//    SDL_RenderGetClipRect(m_renderer, static_cast<SDL_Rect*>(rect));
//    if (!rect.has_area()) {
//      return nothing;
//    } else {
//      return rect;
//    }
//  }
//
//  /**
//   * Returns information about the renderer.
//   *
//   * @return information about the renderer; nothing if something went wrong.
//   * @since 3.0.0
//   */
//  [[nodiscard]] auto info() const noexcept -> Optional<SDL_RendererInfo>
//  {
//    SDL_RendererInfo info;
//    const auto result = SDL_GetRendererInfo(m_renderer, &info);
//    if (result == 0) {
//      return info;
//    } else {
//      return nothing;
//    }
//  }
//
//  /**
//   * Returns the output width of the renderer.
//   *
//   * @return the output width of the renderer.
//   * @since 3.0.0
//   */
//  [[nodiscard]] auto output_width() const noexcept -> int
//  {
//    int width = 0;
//    SDL_GetRendererOutputSize(m_renderer, &width, nullptr);
//    return width;
//  }
//
//  /**
//   * Returns the output height of the renderer.
//   *
//   * @return the output height of the renderer.
//   * @since 3.0.0
//   */
//  [[nodiscard]] auto output_height() const noexcept -> int
//  {
//    int height = 0;
//    SDL_GetRendererOutputSize(m_renderer, nullptr, &height);
//    return height;
//  }
//
//  /**
//   * Returns the output size of the renderer.
//   *
//   * @return the output size of the renderer, in the format (width, height).
//   * @since 3.0.0
//   */
//  [[nodiscard]] auto output_size() const noexcept -> area_i
//  {
//    int width = 0;
//    int height = 0;
//    SDL_GetRendererOutputSize(m_renderer, &width, &height);
//    return {width, height};
//  }
//
//  /**
//   * Returns the blend mode that is being used by the renderer.
//   *
//   * @return the blend mode that is being used.
//   * @since 4.0.0
//   */
//  [[nodiscard]] auto blend_mode() const noexcept -> BlendMode
//  {
//    SDL_BlendMode mode;
//    SDL_GetRenderDrawBlendMode(m_renderer, &mode);
//    return static_cast<BlendMode>(mode);
//  }
//
//  /**
//   * Returns a bit mask that represents all of flags used when creating the
//   * renderer. The possible values are <ul> <li>a</li>
//   * </ul>
//   *
//   * @return a bit mask that represents all of flags used when creating the
//   * renderer.
//   * @since 3.0.0
//   */
//  [[nodiscard]] auto flags() const noexcept -> Uint32
//  {
//    SDL_RendererInfo info;
//    SDL_GetRendererInfo(m_renderer, &info);
//    return info.flags;
//  }
//
//  /**
//   * Indicates whether or not the <code>present()</code> method is synced with
//   * the refresh rate of the screen.
//   *
//   * @return true if vsync is enabled; false otherwise.
//   * @since 3.0.0
//   */
//  [[nodiscard]] auto vsync_enabled() const noexcept -> bool
//  {
//    return flags() & SDL_RENDERER_PRESENTVSYNC;
//  }
//
//  /**
//   * Indicates whether or not the renderer is hardware accelerated.
//   *
//   * @return true if the renderer is hardware accelerated; false otherwise.
//   * @since 3.0.0
//   */
//  [[nodiscard]] auto accelerated() const noexcept -> bool
//  {
//    return flags() & SDL_RENDERER_PRESENTVSYNC;
//  }
//
//  /**
//   * Indicates whether or not the renderer is using software rendering.
//   *
//   * @return true if the renderer is software-based; false otherwise.
//   * @since 3.0.0
//   */
//  [[nodiscard]] auto software_based() const noexcept -> bool
//  {
//    return flags() & SDL_RENDERER_SOFTWARE;
//  }
//
//  /**
//   * Indicates whether or not the renderer supports rendering to a target
//   * texture.
//   *
//   * @return true if the renderer supports target texture rendering; false
//   * otherwise.
//   * @since 3.0.0
//   */
//  [[nodiscard]] auto supports_target_textures() const noexcept -> bool
//  {
//    return flags() & SDL_RENDERER_TARGETTEXTURE;
//  }
//
//  /**
//   * Indicates whether or not the renderer uses integer scaling values for
//   * logical viewports. By default, this property is set to false.
//   *
//   * @return true if the renderer uses integer scaling for logical viewports;
//   * false otherwise.
//   * @since 3.0.0
//   */
//  [[nodiscard]] auto using_integer_logical_scaling() const noexcept -> bool
//  {
//    return SDL_RenderGetIntegerScale(m_renderer);
//  }
//
//  /**
//   * Indicates whether or not clipping is enabled. This is disabled by
//   * default.
//   *
//   * @return true if clipping is enabled; false otherwise.
//   * @since 3.0.0
//   */
//  [[nodiscard]] auto clipping_enabled() const noexcept -> bool
//  {
//    return SDL_RenderIsClipEnabled(m_renderer);
//  }
//
//  /**
//   * Returns the currently selected rendering color. Set to black by default.
//   *
//   * @return the currently selected rendering color.
//   * @since 3.0.0
//   */
//  [[nodiscard]] auto color() const noexcept -> Color
//  {
//    Uint8 red = 0, green = 0, blue = 0, alpha = 0;
//    SDL_GetRenderDrawColor(m_renderer, &red, &green, &blue, &alpha);
//    return {red, green, blue, alpha};
//  }
//
//  /**
//   * Attempts to render the specified text in the supplied font using the
//   * currently selected color and return the texture that contains the result.
//   * Use the returned texture to actually render the text to the screen. This
//   * method doesn't throw but might return null if something goes wrong.
//   *
//   * <p> This method renders the text at the highest quality and uses
//   * anti-aliasing. Use this when you want high quality text, but beware that
//   * this is the slowest alternative.
//   *
//   * @param text the text that will be rendered, can safely be null.
//   * @param font the font that the text will be rendered in.
//   * @return a unique pointer to a texture that contains the rendered text;
//   * null if something went wrong.
//   * @since 4.0.0
//   */
//  [[nodiscard]] auto text_blended(CZString text,
//                                  const Font& font) const noexcept
//      -> std::unique_ptr<Texture>
//  {
//    return render_text(text, [this, &font](CZString text) noexcept {
//      return TTF_RenderText_Blended(
//          font.get(), text, static_cast<SDL_Color>(color()));
//    });
//  }
//
//  /**
//   * Attempts to render the specified text in the supplied font using the
//   * currently selected color and return the texture that contains the result.
//   * Use the returned texture to actually render the text to the screen. This
//   * method doesn't throw but might return null if something goes wrong.
//   *
//   * <p> This method renders the text at the highest quality and uses
//   * anti-aliasing. Use this when you want high quality text, but beware that
//   * this is the slowest alternative. This method will wrap the supplied text
//   * to fit the specified width. Furthermore, you can also manually control
//   * the line breaks by inserting newline characters at the desired
//   * breakpoints.
//   *
//   * @param text the text that will be rendered. You can insert newline
//   * characters in the string to indicate breakpoints, can safely be null.
//   * @param wrap the width in pixels which marks the point that the text will
//   * be wrapped after.
//   * @param font the font that the text will be rendered in.
//   * @return a unique pointer to a texture that contains the rendered text;
//   * null if something went wrong.
//   * @since 4.0.0
//   */
//  [[nodiscard]] auto text_blended_wrapped(CZString text,
//                                          Uint32 wrap,
//                                          const Font& font) const noexcept
//      -> std::unique_ptr<Texture>
//  {
//    return render_text(text, [this, &font, wrap](CZString text) noexcept {
//      return TTF_RenderText_Blended_Wrapped(
//          font.get(), text, static_cast<SDL_Color>(color()), wrap);
//    });
//  }
//
//  /**
//   * Attempts to render the specified text in the supplied font using the
//   * currently selected color and return the texture that contains the result.
//   * Use the returned texture to actually render the text to the screen. This
//   * method doesn't throw but might return null if something goes wrong.
//   *
//   * <p> This method renders the text using anti-aliasing and with a box
//   * behind the text. This alternative is probably a bit slower than
//   * rendering solid text but about as fast as blended text. Use this
//   * method when you want nice text, and can live with a box around it.
//   *
//   * @param text the text that will be rendered, can safely be null.
//   * @param bg the background color used for the box.
//   * @param font the font that the text will be rendered in.
//   * @return a unique pointer to a texture that contains the rendered text;
//   * null if something went wrong.
//   * @since 4.0.0
//   */
//  [[nodiscard]] auto text_shaded(CZString text,
//                                 const Color& bg,
//                                 const Font& font) const noexcept
//      -> std::unique_ptr<Texture>
//  {
//    return render_text(text, [this, &font, &bg](CZString text) noexcept {
//      return TTF_RenderText_Shaded(font.get(),
//                                   text,
//                                   static_cast<SDL_Color>(color()),
//                                   static_cast<SDL_Color>(bg));
//    });
//  }
//
//  /**
//   * Attempts to render the specified text in the supplied font using the
//   * currently selected color and return the texture that contains the result.
//   * Use the returned texture to actually render the text to the screen. This
//   * method doesn't throw but might return null if something goes wrong.
//   *
//   * <p> This method is the fastest at rendering text to a texture. It
//   * doesn't use anti-aliasing so the text isn't very smooth. Use this method
//   * when quality isn't as big of a concern and speed is important.
//   *
//   * @param text the text that will be rendered, can safely be null.
//   * @param font the font that the text will be rendered in.
//   * @return a unique pointer to a texture that contains the rendered text;
//   * null if something went wrong.
//   * @since 4.0.0
//   */
//  [[nodiscard]] auto text_solid(CZString text, const Font& font) const
//  noexcept
//      -> std::unique_ptr<Texture>
//  {
//    return render_text(text, [this, &font](CZString text) noexcept {
//      return TTF_RenderText_Solid(
//          font.get(), text, static_cast<SDL_Color>(color()));
//    });
//  }
//
//  /**
//   * Returns the font associated with the specified name. This method returns
//   * null if there is no font associated with the specified name.
//   *
//   * @param name the name associated with the desired font.
//   * @return the font associated with the specified name; null if there is no
//   * such font.
//   * @since 4.1.0
//   */
//  [[nodiscard]] auto font(const std::string& name) noexcept
//      -> std::shared_ptr<Font>
//  {
//    if (m_fonts.count(name)) {
//      return m_fonts.at(name);
//    } else {
//      return nullptr;
//    }
//  }
//
//  /**
//   * Indicates whether or not the renderer has a font associated with the
//   * specified name.
//   *
//   * @param name the name that will be checked.
//   * @return true if the renderer has a font associated with the specified
//   * name; false otherwise.
//   * @since 4.1.0
//   */
//  [[nodiscard]] auto has_font(const std::string& name) const noexcept -> bool
//  {
//    return m_fonts.count(name);
//  }
//
//  /**
//   * Returns the viewport that the renderer uses.
//   *
//   * @return the viewport that the renderer uses.
//   * @since 3.0.0
//   */
//  [[nodiscard]] auto viewport() const noexcept -> IRect
//  {
//    IRect viewport;
//    SDL_RenderGetViewport(m_renderer, static_cast<SDL_Rect*>(viewport));
//    return viewport;
//  }
//
//  /**
//   * Returns a textual representation of the renderer.
//   *
//   * @return a textual representation of the renderer.
//   * @since 3.0.0
//   */
//  [[nodiscard]] auto to_string() const -> std::string
//  {
//    const auto address = detail::address_of(this);
//    const auto owidth = std::to_string(output_width());
//    const auto oheight = std::to_string(output_height());
//    return "[Renderer@" + address + " | Output width: " + owidth +
//           ", Output height: " + oheight + "]";
//  }
//
//  /**
//   * Returns the translation viewport that is currently being used. Set to (0,
//   * 0, 0, 0) by default.
//   *
//   * @return the translation viewport that is currently being used.
//   * @since 3.0.0
//   */
//  [[nodiscard]] auto translation_viewport() const noexcept -> const FRect&
//  {
//    return m_translationViewport;
//  }
//
//  /**
//   * Returns a pointer to the internal SDL_Renderer. Use of this method is
//   * not recommended, since it purposefully breaks const-correctness. However
//   * it is useful since many SDL calls use non-const pointers even when no
//   * change will be applied.
//   *
//   * @return a pointer to the internal SDL_Renderer.
//   * @since 4.0.0
//   */
//  [[nodiscard]] auto get() const noexcept -> SDL_Renderer*
//  {
//    return m_renderer;
//  }
//
//  /**
//   * Converts to SDL_Renderer*.
//   *
//   * @return a pointer to the internal SDL_Renderer instance.
//   * @since 3.0.0
//   */
//  [[nodiscard]] operator SDL_Renderer*() noexcept { return m_renderer; }
//
//  /**
//   * Converts to SDL_Renderer*.
//   *
//   * @return a pointer to the internal SDL_Renderer instance.
//   * @since 3.0.0
//   */
//  [[nodiscard]] operator const SDL_Renderer*() const noexcept
//  {
//    return m_renderer;
//  }
//
//  /**
//   * Returns the number of available rendering drivers. Usually there is only
//   * 1 available rendering driver.
//   *
//   * @return the number of available rendering drivers.
//   * @since 4.0.0
//   */
//  [[nodiscard]] static auto render_drivers() noexcept -> int
//  {
//    return SDL_GetNumRenderDrivers();
//  }
//
//  /**
//   * Returns the number of available video drivers compiled into SDL.
//   *
//   * @return the number of available video drivers compiled into SDL.
//   * @since 4.0.0
//   */
//  [[nodiscard]] static auto video_drivers() noexcept -> int
//  {
//    return SDL_GetNumVideoDrivers();
//  }
//
//  /**
//   * Returns the information associated with a rendering driver.
//   *
//   * @param index the index of the rendering driver to query.
//   * @return information about the specified rendering driver; nothing if
//   * something went wrong.
//   * @since 4.0.0
//   */
//  [[nodiscard]] static auto driver_info(int index) noexcept
//      -> Optional<SDL_RendererInfo>
//  {
//    SDL_RendererInfo info;
//    const auto result = SDL_GetRenderDriverInfo(index, &info);
//    if (result == 0) {
//      return info;
//    } else {
//      return nothing;
//    }
//  }
//
// private:
//  SDL_Renderer* m_renderer = nullptr;
//  FRect m_translationViewport;
//  std::unordered_map<FontKey, SharedPtr<Font>> m_fonts;
//
//  static constexpr SDL_RendererFlags defaultFlags =
//      static_cast<SDL_RendererFlags>(SDL_RENDERER_ACCELERATED |
//                                     SDL_RENDERER_PRESENTVSYNC);
//
//  /**
//   * Destroys the resources associated with the renderer.
//   *
//   * @since 4.0.0
//   */
//  void destroy() noexcept
//  {
//    if (m_renderer) {
//      SDL_DestroyRenderer(m_renderer);
//    }
//  }
//
//  /**
//   * Moves the contents of the supplied renderer instance into this instance.
//   *
//   * @param other the instance that will be moved.
//   * @since 4.0.0
//   */
//  void move(Renderer&& other) noexcept
//  {
//    destroy();
//
//    m_renderer = other.m_renderer;
//    m_translationViewport = other.m_translationViewport;
//
//    other.m_renderer = nullptr;
//  }
//
//  /**
//   * A helper method used by text rendering methods to create surfaces based
//   * on the text and then convert it to fast textures.
//   *
//   * @param text the text that will be rendered.
//   * @param render a lambda that creates a <code>SDL_Surface*</code> and
//   * takes a <code>CZString</code> as its parameter.
//   * @return a unique pointer to a texture; null if something went wrong.
//   * @since 4.0.0
//   */
//  template <typename Lambda>
//  [[nodiscard]] auto render_text(CZString text, Lambda&& render) const
//  noexcept
//      -> std::unique_ptr<Texture>
//  {
//    if (!text) {
//      return nullptr;
//    }
//
//    SDL_Surface* surface = render(text);
//    if (!surface) {
//      return nullptr;
//    }
//
//    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
//    SDL_FreeSurface(surface);
//
//    if (texture) {
//      return std::make_unique<Texture>(texture);
//    } else {
//      return nullptr;
//    }
//  }
//
//  /**
//   * Returns the translated x-coordinate that corresponds to the supplied
//   * x-coordinate.
//   *
//   * @param x the x-coordinate that will be translated.
//   * @return the translated x-coordinate that corresponds to the supplied
//   * x-coordinate.
//   * @since 4.1.0
//   */
//  template <typename T>
//  [[nodiscard]] auto tx(T x) const noexcept -> T
//  {
//    if constexpr (std::is_same_v<T, int>) {
//      return x - static_cast<T>(m_translationViewport.x());
//    } else {
//      return x - m_translationViewport.x();
//    }
//  }
//
//  /**
//   * Returns the translated y-coordinate that corresponds to the supplied
//   * y-coordinate.
//   *
//   * @param y the y-coordinate that will be translated.
//   * @return the translated y-coordinate that corresponds to the supplied
//   * y-coordinate.
//   * @since 4.1.0
//   */
//  template <typename T>
//  [[nodiscard]] auto ty(T y) const noexcept -> T
//  {
//    if constexpr (std::is_same_v<T, int>) {
//      return y - static_cast<T>(m_translationViewport.y());
//    } else {
//      return y - m_translationViewport.y();
//    }
//  }
//
//  template <typename T>
//  [[nodiscard]] auto translate(const Rect<T>& rect) const noexcept -> Rect<T>
//  {
//    return {tx(rect.x()), tx(rect.y()), rect.size()};
//  }
//};
//
// static_assert(std::is_final_v<Renderer>);
// static_assert(std::is_nothrow_move_constructible_v<Renderer>);
// static_assert(std::is_nothrow_move_assignable_v<Renderer>);
// static_assert(!std::is_nothrow_copy_constructible_v<Renderer>);
// static_assert(!std::is_nothrow_copy_assignable_v<Renderer>);
// static_assert(std::is_convertible_v<Renderer, SDL_Renderer*>);
//
//}  // namespace centurion
//
//#ifdef CENTURION_HEADER_ONLY
//#include "renderer.cpp"
//#endif
//
//#endif  // CENTURION_RENDERER_HEADER