/**
 * \page configuration Static Configuration
 *
 * The library can be configured in various ways at compile-time using the following
 * macros. For technical reasons, these macros are used to opt-out of certain features,
 * rather than opt-in. All Centurion macros feature the `CENTURION_` prefix.
 *
 * \note  Remember, you have to define the customization macros _before_ you include the
 * Centurion header.
 *
 * \code{cpp}
 * #define CENTURION_CONFIGURATION_MACRO
 * #include <centurion.hpp>
 *
 * int main(int, char**)
 * {
 *   cen::SDL sdl;
 *   cen::IMG img;
 *   cen::Mix mix;
 *   cen::TTF ttf;
 *
 *   // ...
 *
 *   return 0;
 * }
 * \endcode
 *
 * \section no-pragma-once CENTURION_NO_PRAGMA_ONCE
 * Excludes the `#pragma once` statement in the Centurion header if defined.
 *
 * \section no-debug-log-macros CENTURION_NO_DEBUG_LOG_MACROS
 * Entirely excludes all debug-only logging macros if defined, e.g. `CENTURION_LOG_INFO`.
 *
 * \section no-sdl-image CENTURION_NO_SDL_IMAGE
 * Excludes all library components that rely on SDL_image if defined.
 *
 * \section no-sdl-mixer CENTURION_NO_SDL_MIXER
 * Excludes all library components that rely on SDL_mixer if defined.
 *
 * \section no-sdl-ttf CENTURION_NO_SDL_TTF
 * Excludes all library components that rely on SDL_ttf if defined.
 *
 * \section no-vulkan-support CENTURION_NO_VULKAN
 * Excludes all library components related to the Vulkan API if defined.
 *
 * \section no-opengl-support CENTURION_NO_OPENGL
 * Excludes all library components related to the OpenGL API if defined.
 */