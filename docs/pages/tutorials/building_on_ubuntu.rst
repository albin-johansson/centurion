Building Centurion (Ubuntu)
===========================

**Synopsis:** Demonstrates how to build the Centurion library on Ubuntu.

Firstly, Centurion requires SDL2 to be installed. SDL2 and the required related
packages can be installed with the following commands.

.. code-block:: bash
  :name: download-sdl-development-libraries
  :caption: Installs SDL2 development libraries.
  :linenos:

  sudo apt-get install libsdl2-dev
  sudo apt-get install libsdl2-ttf-dev
  sudo apt-get install libsdl2-mixer-dev
  sudo apt-get install libsdl2-image-dev

However, at the time of writing, the Ubuntu core SDL2 library isn't recent
enough for use with Centurion. So we have to build them manually. The process is 
basically the same for all of the SDL2 libraries. The following commands should
be executed where you'd like to install your libraries, e.g. ``~/sdl2/``.

.. code-block::
  :name: manual-download-sdl-libraries
  :caption: Downloads and installs the SDL2 libraries.
  :linenos:

  wget -c https://www.libsdl.org/release/SDL2-2.0.12.tar.gz
  tar -xf SDL2-2.0.12.tar.gz
  cd SDL2-2.0.12
  ./configure
  make
  sudo make install
  cd ..

  wget -c https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.5.tar.gz
  tar -xf SDL2_image-2.0.5.tar.gz
  cd SDL2_image-2.0.5
  ./configure
  make all
  sudo make install
  cd ..

  wget -c https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.4.tar.gz
  tar -xf SDL2_mixer-2.0.4.tar.gz
  cd SDL2_mixer-2.0.4
  ./configure
  make
  sudo make install
  cd ..

  sudo apt-get install libfreetype6-dev

  wget -c https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15.tar.gz
  tar -xf SDL2_ttf-2.0.15.tar.gz
  cd SDL2_ttf-2.0.15
  ./configure
  make
  sudo make install

By this point, SDL2 should be installed and usable. The following is how you'd
download and compile the latest stable version (the main branch) of the Centurion 
library.

.. code-block::
  :name: download-compile-centurion
  :caption: Downloads and compiles the library.
  :linenos:

  git clone https://github.com/albin-johansson/Centurion.git centurion
  cd centurion
  mkdir build
  cd build
  cmake .. -GNinja
  ninja

And that's it! You've successfully built the Centurion library.