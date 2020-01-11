#pragma once
#include <string>
#include <cstdint>
#include <gsl>
#include <SDL_render.h>

namespace centurion {

/**
 * The Image class represents an image that is hardware-accelerated. Instances of the Image class
 * can be converted to std::string (explicitly using static_cast) and SDL_Texture* (implicitly).
 *
 * @see SDL_Texture
 * @since 3.0.0
 */
class Image final {
 private:
  SDL_Texture* texture = nullptr;

 public:
  /**
   * Creates an image from a pre-existing SDL texture. The created image WILL claim ownership of
   * the supplied pointer!
   *
   * @param texture a pointer to the SDL_Texture that will be claimed, may not be null.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 3.0.0
   */
  explicit Image(gsl::owner<SDL_Texture*> texture);

  /**
   * Creates an image by loading it from a file.
   *
   * @param renderer a pointer to the SDL_Renderer used to create the image, must not be null.
   * @param path the file path of the image that will be loaded.
   * @throws CenturionException if the image cannot be loaded.
   * @since 3.0.0
   */
  Image(gsl::not_null<SDL_Renderer*> renderer, const std::string& path);

  /**
   * Creates an image that is a copy of the supplied SDL surface.
   *
   * @param renderer the associated renderer instance, may not be null.
   * @param surface the SDL surface that the image will be based on, may not be null
   * @throws CenturionException if the image cannot be loaded.
   * @since 3.0.0
   */
  Image(gsl::not_null<SDL_Renderer*> renderer, gsl::not_null<SDL_Surface*> surface);

  /**
   * Creates an image by moving the supplied image.
   *
   * @param other the image that will be moved.
   * @since 3.0.0
   */
  Image(Image&& other) noexcept;

  Image(const Image&) noexcept = delete;

  ~Image() noexcept;

  Image& operator=(const Image&) noexcept = delete;

  /**
   * Moves the supplied image into this image.
   *
   * @param other the image that will be moved.
   * @return the changed image.
   * @since 3.0.0
   */
  [[nodiscard]]
  Image& operator=(Image&& other) noexcept;

  /**
   * Sets the alpha value of the image.
   *
   * @param alpha the alpha value, in the range [0, 255].
   * @since 3.0.0
   */
  void set_alpha(uint8_t alpha) noexcept;

  /**
   * Returns the format of the internal SDL_Texture.
   *
   * @return the format of the internal SDL_Texture.
   * @since 3.0.0
   */
  [[nodiscard]]
  uint32_t get_format() const noexcept;

  /**
   * Returns the texture access of the internal SDL_Texture.
   *
   * @return the texture access of the internal SDL_Texture.
   * @since 3.0.0
   */
  [[nodiscard]]
  int get_access() const noexcept;

  /**
   * Returns the width of the image.
   *
   * @return the width of the image.
   * @since 3.0.0
   */
  [[nodiscard]]
  int get_width() const noexcept;

  /**
   * Returns the height of the image.
   *
   * @return the height of the image.
   * @since 3.0.0
   */
  [[nodiscard]]
  int get_height() const noexcept;

  /**
   * Returns a pointer to the internal SDL_Texture of the image.
   *
   * @return a pointer to the internal SDL_Texture of the image.
   * @since 3.0.0
   */
  [[nodiscard]]
  SDL_Texture* get_texture() noexcept;

  /**
   * Returns a string representation of the image.
   *
   * @return a string representation of the image.
   * @since 3.0.0
   */
  [[nodiscard]]
  std::string to_string() const;

  /**
   * Returns a string representation of the image.
   *
   * @return a string representation of the image.
   * @since 3.0.0
   */
  explicit operator std::string();

  /**
   * Returns a pointer to the internal SDL_Texture.
   *
   * @return a pointer to the internal SDL_Texture.
   * @since 3.0.0
   */
  operator SDL_Texture*() const noexcept;
};

}
