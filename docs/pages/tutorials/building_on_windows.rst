Building Centurion (Windows)
============================

**Synopsis:** Demonstrates how to build the Centurion library on Windows.

For Windows systems, the library expects to be able to find the SDL2 libraries
with the help of environment variables. If you don't have SDL2 installed on your 
system, then you need to download the runtime binaries, see the following links.

======================  ====================== ===================================================
  Variable               Example                Download
----------------------  ---------------------- ---------------------------------------------------
 SDL2DIR                ``C:\dev\sdl2``         `<https://www.libsdl.org/download-2.0.php>`_
 SDL2TTFDIR             ``C:\dev\sdl2_ttf``     `<https://www.libsdl.org/projects/SDL_ttf/>`_
 SDL2IMAGEDIR           ``C:\dev\sdl2_image``   `<https://www.libsdl.org/projects/SDL_image/>`_
 SDL2MIXERDIR           ``C:\dev\sdl2_mixer``   `<https://www.libsdl.org/projects/SDL_mixer/>`_
======================  ====================== ===================================================

After installing the runtime binaries, you're almost ready to compile the library. Download the 
latest stable version of the repository using the following command.

.. code-block::
  

  git clone https://github.com/albin-johansson/Centurion.git centurion

The CMake scripts expect to find the SDL runtime binaries in a directory called ``bin`` in the root 
directory. Copy all ``.dll`` files from the ``bin`` directories in the previously installed SDL libraries to 
the ``bin`` directory in the Centurion root directory.

Lastly, all that remains is to compile the project. 

.. code-block::
  :name: compile-the-library

  mkdir build
  cd build
  cmake .. -DCMAKE_BUILD_TYPE=Release -GNinja
  ninja

And that's it! You've successfully built the Centurion library.