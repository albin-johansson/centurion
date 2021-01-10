Installation (Windows)
======================

**Synopsis:** Demonstrates how install SDL2 and Centurion on Windows.

On Windows, its common to let build systems find SDL through environment variables.
If you don't currently have SDL2 installed on your system, then you need to download 
the appropriate runtime binaries, see the following links.

======================  ====================== ===================================================
  Variable               Example                Download
----------------------  ---------------------- ---------------------------------------------------
 SDL2DIR                ``C:\dev\sdl2``         `<https://www.libsdl.org/download-2.0.php>`_
 SDL2TTFDIR             ``C:\dev\sdl2_ttf``     `<https://www.libsdl.org/projects/SDL_ttf/>`_
 SDL2IMAGEDIR           ``C:\dev\sdl2_image``   `<https://www.libsdl.org/projects/SDL_image/>`_
 SDL2MIXERDIR           ``C:\dev\sdl2_mixer``   `<https://www.libsdl.org/projects/SDL_mixer/>`_
======================  ====================== ===================================================

After setting up the environment variables, we need to grab the Centurion source files. 
Centurion is header-only so we only need the files located in the ``include`` folder. It is 
recommended to download the latest release of Centurion and include the header files from 
the downloaded archive (view releases `here <https://github.com/albin-johansson/Centurion/releases>`_. 

There are openly available CMake scripts for finding SDL2 available, which enable the 
use of the following commands. For a real world example of this, see `this <https://github.com/albin-johansson/wanderer>`_
project.

.. code:: cmake

  find_package(SDL2 REQUIRED)
  find_package(SDL2_image REQUIRED)
  find_package(SDL2_mixer REQUIRED)
  find_package(SDL2_ttf REQUIRED)

In the end you should end up with something along the lines of the following in your build scripts.

.. code:: cmake

  target_include_directories(YourTarget
    SYSTEM PUBLIC ${SDL2_INCLUDE_DIR}
    SYSTEM PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS}
    SYSTEM PUBLIC ${SDL2_MIXER_INCLUDE_DIRS}
    SYSTEM PUBLIC ${SDL2_TTF_INCLUDE_DIRS}
    SYSTEM PUBLIC ${CENTURION_INCLUDE_DIR})

  target_link_libraries(YourTarget
    PUBLIC ${SDL2_IMAGE_LIBRARIES}
    PUBLIC ${SDL2_MIXER_LIBRARIES}
    PUBLIC ${SDL2_TTF_LIBRARIES}
    PUBLIC ${SDL2_LIBRARY})

.. note::

  You'll need to make sure that the SDL runtime binaries are available to your 
  generated executable. This can be automated, refer to the aforementioned
  example to see it in action.