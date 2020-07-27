Hello Centurion
===============

**Synopsis:** Demonstrates how to setup a Centurion program.

Just like SDL, Centurion needs to be initialized before it can be used. This is simply done by
creating an instance of the ``centurion_lib`` class. Under the hood, ``centurion_lib`` will
actually initialize SDL for us. So you should never initialize *both* Centurion and SDL explicitly.

The ``centurion_lib`` class can be included by including either ``centurion.hpp`` or ``centurion_as_ctn.hpp``. 
The only difference between these headers is that ``centurion_as_ctn.hpp`` provides the ``ctn`` namespace alias.
Since all Centurion entities are located in the ``centurion`` namespace, it can get tedious to qualify everything 
with ``centurion::``. As a result, it's recommended to prefer the ``ctn`` namespace alias.

Now, it's important to get the signature of ``main`` correct in order for your program to work. The signature 
of the main-method **must** be ``int main(int, char**)``! This is because SDL actually performs some setup before 
the main method is entered through some macro magic.

Standard Configuration
----------------------
By far the easiest way to initialize the Centurion library is demonstrated in the following example. The default configuration
is likely appropriate for your program. However, as demonstrated in the later example, it's possible to be more specific with
exactly what gets initialized (and how).

.. code-block:: c++

  #include <centurion_as_ctn.hpp>

  int main(int, char**)
  {
    ctn::centurion_lib c;

    // Centurion and SDL are now initialized!

    return 0;
  }

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