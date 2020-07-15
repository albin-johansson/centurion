Hello Centurion
===============

**Synopsis:** Demonstrates how to setup a Centurion program.

Just like SDL, Centurion needs to be initialized before it can be used. This is simply done by
creating an instance of the ``centurion_lib`` class. Under the hood, ``centurion_lib`` will
actually initialize SDL for us. So you should never initialize *both* Centurion and SDL explicitly.

.. hint::

   All Centurion classes, functions and aliases are located in the ``centurion``
   namespace. However, since it's tedious to qualify everything with ``centurion::``,
   it's recommended to use the ``<centurion_as_ctn.hpp>`` header to get access to
   the ``ctn`` namespace alias.

Standard Configuration
----------------------
The following example is the typical entry point for a Centurion application. More than likely
this will work just fine for your application. However, you can be more specific with what gets
initialized, as demonstrated in the next example.

.. code-block:: c++

  #include <centurion_as_ctn.hpp>

  int main(int, char**)
  {
    ctn::centurion_lib c;

    // the library (and SDL2, SDL2_image, SDL2_mixer and SDL2_ttf) is now initialized!

    return 0;
  }

.. note::

  The signature of the main-method **must** be ``int main(int, char**)``, this is because SDL
  actually performs some setup before the main method is entered through some macro magic.

Custom Configuration
--------------------
It's possible to tell Centurion how the SDL libraries should be initialized. This is done by
supplying an instance of ``centurion_config`` to the constructor of ``centurion_lib``. The
following example demonstrates how you could specify that no audio components should be
initialized.

.. code-block:: c++

  #include <centurion_as_ctn.hpp>

  int main(int, char**)
  {
    ctn::centurion_config cfg;

    cfg.coreFlags = SDL_INIT_EVERYTHING & ~SDL_INIT_AUDIO;
    cfg.initMixer = false;

    ctn::centurion_lib c{cfg};

    // the library is now initialized, but no audio components are initialized!
  }

.. warning::

  You have to make sure that you don't actually use anything from SDL and/or Centurion that
  relies on a specific subsystem that you haven't initialized!