Hello Centurion
===============

**Synopsis:** Demonstrates how to setup a Centurion program.

Just like SDL, Centurion needs to be initialized before it can be used. This is simply done by
creating an instance of the ``library`` class. Under the hood, ``library`` will
actually initialize SDL for us. So you should never initialize *both* Centurion and SDL explicitly.

The ``library`` class is located in the ``centurion.hpp`` header. Now, it's important to get the
signature of ``main`` correct in order for your program to work. The signature of ``main``
**must** be equivalent to ``int main(int, char**)``! This is because SDL actually performs some setup before
the main method is entered through some macro magic.

Standard Configuration
----------------------
By far the easiest way to initialize the Centurion library is demonstrated in the following example. The default configuration
is likely appropriate for your program. However, as demonstrated in the later example, it's possible to be more specific with
exactly what gets initialized (and how).

.. code-block:: c++

  #include <centurion.hpp>

  int main(int, char**)
  {
    cen::library lib;

    // Centurion and SDL are now initialized!

    return 0;
  }

Custom Configuration
--------------------
It's possible to tell Centurion how the SDL libraries should be initialized. This is done by
supplying an instance of ``config`` to the constructor of ``library``. The
following example demonstrates how you could specify that no audio components should be
initialized.

.. code-block:: c++

  #include <centurion.hpp>

  int main(int, char**)
  {
    cen::config cfg;

    cfg.coreFlags = SDL_INIT_EVERYTHING & ~SDL_INIT_AUDIO;
    cfg.initMixer = false;

    cen::library lib{cfg};

    // the library is now initialized, but no audio components are initialized!
  }

.. warning::

  You have to make sure that you don't actually use anything from SDL and/or Centurion that
  relies on a specific subsystem that you haven't initialized!