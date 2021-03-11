color
=====

An 8-bit accuracy RGBA color. It is designed to be work well with 
both of the SDL colors, ``SDL_Color`` and ``SDL_MessageBoxColor``. Furthermore,
there are approximately 140 color constants provided in the ``cen::colors`` namespace,
defined in the ``colors.hpp`` header.

General information
-------------------

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    Yes
Copyable                 Yes
Movable                  Yes
Implicit conversions     None
Explicit conversions     ``SDL_Color``, ``SDL_MessageBoxColor``, ``SDL_Color*``, ``const SDL_Color*``
Overloaded operators     ``<<``, ``==``, ``!=``
Namespace                ``::cen``
Since                    3.0.0
======================  =========================================

Interface 
---------

.. doxygenclass:: cen::color
  :members:
  :undoc-members:
  :outline:
  :no-link:

Color constants
---------------

The following are all of the color constants defined in the 
``cen::colors`` namespace.

.. doxygennamespace:: cen::colors
  :members:
  :undoc-members:
  :outline:
  :no-link:

Examples
--------

Compile-time color creation
~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code:: C++

  #include <color.hpp>
  #include <colors.hpp>
  #include <renderer.hpp>

  void draw(cen::renderer& renderer)
  {
    // Create a color that is identical to magenta except for different alpha
    constexpr auto customMagenta = cen::colors::magenta.with_alpha(182);  

    // Explicit RGB components, alpha defaults to 0xFF (255)
    constexpr cen::color color{0xED, 0xA3, 0x3F};

    renderer.set_color(customMagenta);
    renderer.fill_rect<int>({{12, 34}, {120, 80}});
    // ...
  }
