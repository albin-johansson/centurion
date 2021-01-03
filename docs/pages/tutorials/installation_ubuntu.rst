Installation (Ubuntu)
=====================

**Synopsis:** Demonstrates how install SDL2 and Centurion on Ubuntu.

Firstly, Centurion is of course dependent on SDL2. So we need to install the 
SDL libraries. SDL2 and the required related packages can be installed with the
following commands.

.. code-block:: bash

  sudo apt-get install libsdl2-dev
  sudo apt-get install libsdl2-ttf-dev
  sudo apt-get install libsdl2-mixer-dev
  sudo apt-get install libsdl2-image-dev

However, at the time of writing, the Ubuntu core SDL2 library isn't recent
enough for use with Centurion. So we have to build them manually. The process is 
basically the same for all of the SDL2 libraries. The following commands should
be executed where you'd like to install your libraries, e.g. ``~/sdl2/``.

.. code-block::

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
  make
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

By this point, SDL2 should be installed and usable. Since Centurion is header-only, we
only need to download the latest available headers and add them to our project. Just 
grab the ``include`` folder and include its contents and you should be ready to go!