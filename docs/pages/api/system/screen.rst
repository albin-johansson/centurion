Screen
======

The screen API provides information about the system display, such as refresh rate, 
dimensions and pixel format.

General information
-------------------

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Namespace                ``::centurion::screen``
Header                   ``screen.hpp``
Since                    3.0.0
======================  =========================================

Interface
---------

.. doxygennamespace:: centurion::screen
  :outline:
  :members:

Examples
--------

Querying the screen size
~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: C++

  #include <centurion_as_ctn.hpp>
  #include <screen.hpp>

  void foo()
  {
    // obtains screen width
    const auto w = ctn::screen::width();

    // obtains screen height
    const auto h = ctn::screen::height();

    // obtains screen size
    const auto [width, height] = ctn::screen::size();
  }

Controlling the screen saver
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: C++

  #include <centurion_as_ctn.hpp>
  #include <screen.hpp>

  void foo()
  {
    // checks whether screen savers are enabled
    const auto enabled = ctn::screen::screen_saver_enabled();

    // specifies whether or not screen savers should be enabled
    ctn::screen::set_screen_saver_enabled(false);
  }

Texture using screen pixel format
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: C++

  #include <centurion_as_ctn.hpp>
  #include <screen.hpp>
  #include <texture.hpp>

  void foo()
  {
    // creates a blank texture that uses the screen pixel format
    const ctn::texture texture{ctn::screen::pixel_format(), 
                               ctn::texture_access::no_lock, 
                               {100, 100}};
  }