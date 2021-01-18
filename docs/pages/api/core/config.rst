config
======

The ``config`` struct is used to, as the name suggests, to configure 
the initialization of the SDL libraries. You can supply and 
instance of the ``config`` struct to the ``library`` constructor to 
override the default configuration. Keep in mind that this is an 
advanced feature and should not be needed by most users.

.. note::

  All members of the ``config`` struct are initially set to the 
  default values used when the default constructor of ``library`` 
  is used to initialize the Centurion library.

General information
-------------------

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    Yes
Copyable                 Yes
Movable                  Yes
Implicit conversions     None
Explicit conversions     None
Overloaded operators     None
Namespace                ``::cen``
Header                   ``centurion.hpp``
Since                    4.0.0
======================  =========================================

Interface 
---------

.. doxygenstruct:: cen::config
  :members:
  :undoc-members:
  :outline:
  :no-link: 

Examples
--------

.. warning::

  It is your responsibility to make sure to not use any Centurion/SDL APIs 
  that depend on a subsystem that you might have disabled.

Typical usage 
~~~~~~~~~~~~~

.. code:: C++ 

  #include <centurion.hpp>

  namespace {

  void run()
  {
    // Run application, can't use anything that depends on SDL_mixer...
  }
  
  }

  int main(int, char**) 
  {
    cen::config cfg;

    // Don't initialize SDL_mixer library
    cfg.initMixer = false; 

    // Only initialize SDL_image with support for PNG and JPG files
    cfg.imageFlags = IMG_INIT_PNG | IMG_INIT_JPG;

    const cen::library library{cfg};
    run();

    return 0;
  }
