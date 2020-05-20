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

#ifndef CENTURION_SURFACE_HEADER
#define CENTURION_SURFACE_HEADER

#include <SDL.h>

#include <type_traits>

#include "blend_mode.h"
#include "centurion_api.h"
#include "centurion_utils.h"
#include "color.h"
#include "pixel_format.h"
#include "rect.h"

namespace centurion {

class Texture;
class Renderer;

/**
 * The <code>Surface</code> class represents a non-accelerated image. In most
 * cases, it's preferable to use the <code>Texture</code> class instead.
 *
 * @since 4.0.0
 */
class Surface final {
 public:
  /**
   * @param file the file path of the image file that will be loaded.
   * @throws CenturionException if the surface cannot be created.
   * @since 4.0.0
   */
  CENTURION_API explicit Surface(CZString file);

  /**
   * @param surface a pointer to the SDL_Surface that will be used to create the
   * surface. Mustn't be null.
   * @throws CenturionException if the supplied pointer is null.
   * @since 4.0.0
   */
  CENTURION_API explicit Surface(Owner<SDL_Surface*> surface);

  /**
   * Creates a copy of the supplied surface.
   *
   * @param other the surface that will be copied.
   * @throws CenturionException if the supplied surface couldn't be copied.
   * @since 4.0.0
   */
  CENTURION_API Surface(const Surface& other);

  /**
   * Creates a surface by moving the supplied surface.
   *
   * @param other the surface that will be moved.
   * @since 4.0.0
   */
  CENTURION_API Surface(Surface&& other) noexcept;

  /**
   * Copies the supplied surface and saves the result in the invoked surface.
   *
   * @param other the surface that will be copied.
   * @throws CenturionException if the supplied surface couldn't be copied.
   * @since 4.0.0
   */
  CENTURION_API Surface& operator=(const Surface& other);

  /**
   * Moves the supplied surface into this surface.
   *
   * @param other the surface that will be moved.
   * @since 4.0.0
   */
  CENTURION_API Surface& operator=(Surface&& other) noexcept;

  CENTURION_API ~Surface() noexcept;

  /**
   * Sets the color of the pixel at the specified coordinate. This method has
   * no effect if the coordinate is out-of-bounds of if something goes wrong
   * when attempting to modify the pixel data.
   *
   * @param pixel the pixel that will be changed.
   * @param color the new color of the pixel.
   * @since 4.0.0
   */
  CENTURION_API void set_pixel(IPoint pixel, const Color& color) noexcept;

  /**
   * Sets the alpha component modulation value.
   *
   * @param alpha the new alpha component value, in the range [0, 255].
   * @since 4.0.0
   */
  CENTURION_API void set_alpha(Uint8 alpha) noexcept;

  /**
   * Sets the color modulation that will be used by the surface.
   *
   * @param color the color that represents the color modulation that will be
   * used.
   * @since 4.0.0
   */
  CENTURION_API void set_color_mod(const Color& color) noexcept;

  /**
   * Sets the blend mode that will be used by the surface.
   *
   * @param mode the blend mode that will be used.
   * @since 4.0.0
   */
  CENTURION_API void set_blend_mode(BlendMode mode) noexcept;

  /**
   * Returns the alpha component modulation of the surface.
   *
   * @return the alpha modulation value, in the range [0, 255].
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Uint8 alpha() const noexcept;

  /**
   * Returns the color modulation of the surface.
   *
   * @return a color that represents the color modulation of the surface.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Color color_mod() const noexcept;

  /**
   * Returns the blend mode that is being used by the surface.
   *
   * @return the blend mode that the surface uses.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API BlendMode blend_mode() const noexcept;

  /**
   * Converts the surface into its texture equivalent.
   *
   * @param renderer the renderer that will be used to create the
   * texture.
   * @return a texture that is equivalent to the surface.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Texture to_texture(const Renderer& renderer) const noexcept;

  /**
   * Creates and returns a surface based on this surface with the specified
   * pixel format.
   *
   * @param format the pixel format that will be used by the new surface.
   * @return a surface based on this surface with the specified
   * pixel format.
   * @throws CenturionException if the surface cannot be created.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Surface convert(PixelFormat format) const;

  /**
   * Returns the width of the surface.
   *
   * @return the width of the surface.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  int width() const noexcept { return m_surface->w; }

  /**
   * Returns the height of the surface.
   *
   * @return the height of the surface.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  int height() const noexcept { return m_surface->h; }

  /**
   * Returns the pitch (the length of a row of pixels in bytes) of the surface.
   *
   * @return the pitch of the surface.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  int pitch() const noexcept { return m_surface->pitch; }

  /**
   * Returns a pointer to the pixel data of the surface. It's possible to
   * modify the surface through this pointer.
   *
   * @return a pointer to the pixel data of the surface.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  void* pixels() noexcept { return m_surface->pixels; }

  /**
   * Returns a const pointer to the pixel data of the surface.
   *
   * @return a const pointer to the pixel data of the surface.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  const void* pixels() const noexcept { return m_surface->pixels; }

  /**
   * Returns the clipping information associated with the surface.
   *
   * @return the clipping information associated with the surface.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  IRect clip() const noexcept
  {
    const auto rect = m_surface->clip_rect;
    return {rect.x, rect.y, rect.w, rect.h};
  }

  /**
   * Returns a pointer to the internal SDL_Surface. Use of this method is
   * not recommended, since it purposefully breaks const-correctness. However
   * it is useful since many SDL calls use non-const pointers even when no
   * change will be applied. Don't take ownership of the returned pointer, or
   * bad things will happen.
   *
   * @return a pointer to the internal SDL_Surface.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  SDL_Surface* get() const noexcept { return m_surface; }

  /**
   * Implicitly converts to SDL_Surface*.
   *
   * @return a pointer to the internal SDL_Surface.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  operator SDL_Surface*() noexcept { return m_surface; }

  /**
   * Implicitly converts to SDL_Surface*.
   *
   * @return a pointer to the internal SDL_Surface.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  operator const SDL_Surface*() const noexcept { return m_surface; }

 private:
  SDL_Surface* m_surface = nullptr;

  /**
   * Destroys the associated SDL_Surface. This method has no effect if the
   * associated surface is null.
   *
   * @since 4.0.0
   */
  void destroy() noexcept;

  /**
   * Moves the contents of the supplied Surface instance into this instance.
   *
   * @param other the instance that will be moved.
   * @since 4.0.0
   */
  void move(Surface&& other) noexcept;

  /**
   * Copies the contents of the supplied Surface instance into this instance.
   *
   * @param other the instance that will be copied.
   * @since 4.0.0
   */
  void copy(const Surface& other) noexcept;

  /**
   * Indicates whether or not the supplied point is within the bounds of the
   * surface.
   *
   * @param point the point that will be checked.
   * @return true if the point is within the bounds of the surface; false
   * otherwise.
   * @since 4.0.0
   */
  bool in_bounds(IPoint point) const noexcept;

  /**
   * Indicates whether or not the surface must be locked before modifying the
   * pixel data associated with the surface.
   *
   * @return true if the surface must be locked before modification; false
   * otherwise.
   * @since 4.0.0
   */
  bool must_lock() const noexcept;

  /**
   * Attempts to lock the surface, so that the associated pixel data can be
   * modified. This method has no effect if <code>must_lock()</code> returns
   * false.
   *
   * @return true if the locking of the surface was successful or if locking
   * isn't required for modifying the surface; false if something went wrong.
   * @since 4.0.0
   */
  bool lock() noexcept;

  /**
   * Unlocks the surface. This method has no effect if <code>must_lock()
   * </code> returns false.
   *
   * @since 4.0.0
   */
  void unlock() noexcept;

  /**
   * Creates a copy of the internal SDL_Surface, and returns a pointer to it.
   *
   * @return a copy of the internal SDL_Surface, the returned pointer won't be
   * null.
   * @throws CenturionException if the copy couldn't be created.
   * @since 4.0.0
   */
  CENTURION_NODISCARD SDL_Surface* copy_surface() const;
};

static_assert(!std::is_nothrow_copy_constructible<Surface>::value,
              "Surface isn't nothrow copy constructible!");

static_assert(!std::is_nothrow_copy_assignable<Surface>::value,
              "Surface isn't nothrow copy assignable!");

static_assert(std::is_nothrow_move_constructible<Surface>::value,
              "Surface isn't nothrow move constructible!");

static_assert(std::is_nothrow_move_assignable<Surface>::value,
              "Surface isn't nothrow move assignable!");

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "surface.cpp"
#endif

#endif  // CENTURION_SURFACE_HEADER