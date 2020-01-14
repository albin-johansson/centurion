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
  /**
   * Initializes the Centurion library. Creating more than one instance of this class is never
   * necessary, but doing so is safe.
   *
   * @throws CenturionException if any of the SDL libraries can't be loaded.
   * @since 3.0.0
   */
  Centurion();

  /**
   * Closes the Centurion library.
   *
   * @since 3.0.0
   */
  ~Centurion() noexcept;

  Centurion(const Centurion&) = delete;

  Centurion(Centurion&&) = delete;

  Centurion& operator=(const Centurion&) = delete;

  Centurion& operator=(Centurion&&) = delete;
};

}
