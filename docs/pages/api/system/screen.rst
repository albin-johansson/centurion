Screen
======

The screen API provides information about the system display, such as refresh rate, 
dimensions and pixel format.

General information
-------------------

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Namespace                ``::cen::screen``
Header                   ``screen.hpp``
Since                    3.0.0
======================  =========================================

Interface
---------

.. doxygennamespace:: cen::screen
  :outline:
  :members:

Examples
--------

Querying the screen size
~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: C++
  
  #include <screen.hpp>

  void foo()
  {
    // obtains screen width
    const auto w = cen::screen::width();

    // obtains screen height
    const auto h = cen::screen::height();

    // obtains screen size
    const auto [width, height] = cen::screen::size();
  }

Controlling the screen saver
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: C++
  
  #include <screen.hpp>

  void foo()
  {
    // checks whether screen savers are enabled
    const auto enabled = cen::screen::screen_saver_enabled();

    // specifies whether or not screen savers should be enabled
    cen::screen::set_screen_saver_enabled(false);
  }

Texture using screen pixel format
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: C++
  
  #include <screen.hpp>
  #include <renderer.hpp>
  #include <texture.hpp>

  void foo(cen::renderer& renderer)
  {
    // creates a blank texture that uses the screen pixel format
    const cen::texture texture{renderer,
                               cen::screen::pixel_format(), 
                               cen::texture_access::no_lock, 
                               {100, 100}};
  }