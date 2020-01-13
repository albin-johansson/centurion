#pragma once

namespace centurion {

/**
 * The Centurion class is used to initialize and de-initialize the Centurion library.
 *
 * @since 3.0.0
 */
class Centurion final {
 private:
  static bool wasInit;

  /**
   * Initializes the core SDL2 library.
   *
   * @since 3.0.0
   */
  static void init_sdl();

  /**
   * Initializes the SDL2_ttf library.
   *
   * @since 3.0.0
   */
  static void init_ttf();

  /**
   * Initializes the SDL2_image library.
   *
   * @since 3.0.0
   */
  static void init_img();

  /**
   * Initializes the SDL2_mixer library.
   *
   * @since 3.0.0
   */
  static void init_mix();

 public:
  Centurion() = delete;

  /**
   * Initializes the Centurion library. This method will throw if any of the required SDL
   * libraries cannot be loaded. Subsequent calls to this method will have no effect.
   *
   * @throws CenturionException if any of the SDL libraries can't be loaded.
   * @since 3.0.0
   */
  static void init();

  /**
   * Closes the Centurion library. This method has no effect if the library hasn't been initialized.
   *
   * @since 3.0.0
   */
  static void quit() noexcept;

};

}
