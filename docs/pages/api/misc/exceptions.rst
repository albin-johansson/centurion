Exceptions
==========

There are various error handling strategies utilized in the Centurion library,
depending on the situation and likelihood of failure, etc. The library will generally 
avoid throwing exceptions in ordinary functions, e.g. returning values wrapped 
in a ``std::optional`` instead of throwing. However, errors in constructors of Centurion 
classes will always utilize exceptions to signal errors. The general principle is that if 
a Centurion class is successfully constructed, the object is in a valid state. 

.. note:: 

  All of the SDL-related exception classes (i.e. ``cen::sdl_error``, ``cen::ttf_error``,
  ``cen::mix_error`` and ``cen::img_error``) inherit from ``cen::exception``. Furthermore,
  ``cen::exception`` inherits from ``std::exception``.

There are a few different exception classes present in the library, used for different 
occassions. The SDL-related exception classes will have their error message default 
to the latest error message obtained from ``SDL_GetError()``, ``IMG_GetError()``, ``TTF_GetError()``
or ``Mix_GetError()``, depending on the associated SDL library.

==================== =========================================================================
 Exception class      Usage                                    
-------------------- -------------------------------------------------------------------------
 ``cen::exception``   Used for non-SDL errors, e.g. an invalid parameter to a constructor.                 
 ``cen::sdl_error``   Used for core SDL errors, e.g. when ``cen::window`` can't be created.            
 ``cen::ttf_error``   Used for SDL_ttf errors, e.g. when ``cen::font`` can't be created.
 ``cen::mix_error``   Used for SDL_mixer errors, e.g. when ``cen::music`` can't be created.
 ``cen::img_error``   Used for SDL_image errors, e.g. when ``cen::texture`` can't be created.
==================== =========================================================================

Examples
--------

.. code:: C++

  #include <centurion.hpp>

  int main(int, char**)
  {
    try {
      // The constructor will throw if any of the SDL libraries can't be initialized
      cen::library library;

    } catch (const cen::sdl_error& sdlError) {
      // Couldn't initialize core SDL!

    } catch (const cen::img_error& imgError) {
      // Couldn't initialize SDL_image!

    } catch (const cen::ttf_error& ttfError) {
      // Couldn't initialize SDL_ttf!

    } catch (const cen::mix_error& mixError) {
      // Couldn't initialize SDL_mixer!
    }

    return 0;
  }
