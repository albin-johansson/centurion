/**
 * \page page-custom-configuration Dynamic Configuration
 *
 * This example demonstrates how to dynamically tell Centurion how the SDL libraries should be
 * initialized. The example will show how to initialize SDL without any audio support, but
 * the basic principles are the same no matter what you want to disable.
 *
 * In order to tell Centurion to use a custom configuration, you need to supply an
 * instance of the `config` class to the constructor of `library`. Remember, when
 * disabling SDL subsystems, it's your responsibility to make sure that you don't then
 * actually make use of any APIs that rely on said subsystem.
 *
 * \note It's also possible to exclude extension libraries and components that rely on
 * them at compile-time by defining any of the `CENTURION_NO_SDL_IMAGE`,
 * `CENTURION_NO_SDL_MIXER` or `CENTURION_NO_SDL_TTF` macros.
 *
 * \include dynamic-configuration/dynamic_configuration.cpp
 */