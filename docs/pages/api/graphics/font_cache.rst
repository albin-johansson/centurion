font_cache
==========

The ``font_cache`` class is used for glyph-based text rendering and for caching
rendered strings. Which enables very efficient text rendering, at the cost of 
no accurate kerning when using the glyph-based rendering. However, cached strings are 
rendered with accurate kerning.

General information
-------------------

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    No
Copyable                 No
Movable                  Yes
Implicit conversions     None
Explicit conversions     None
Overloaded operators     None
Namespace                ``::cen``
Since                    5.0.0
======================  =========================================

Interface
---------

.. doxygenclass:: cen::font_cache
  :members:
  :undoc-members:
  :outline:
  :no-link:

Examples
--------

Caching glyphs
~~~~~~~~~~~~~~

.. code-block:: c++
  
  #include <window.hpp>
  #include <renderer.hpp>
  #include <font_cache.hpp>
  
  void foo() 
  {
    cen::window window;
    cen::renderer renderer{window};
    cen::font_cache cache{"arial.ttf", 12};

    // Manually adds the glyph "R"
    cache.add_glyph(renderer, 'R'); 

    // Caches Latin-1 glyphs, provided by most fonts
    cache.add_latin1(renderer);
  }

Caching full strings
~~~~~~~~~~~~~~~~~~~~

.. code-block:: c++
  
  #include <window.hpp>
  #include <renderer.hpp>
  #include <font_cache.hpp>

  void foo() 
  {
    cen::window window;
    cen::renderer renderer{window};
    cen::font_cache cache{"arial.ttf", 12};

    renderer.set_color(cen::colors::magenta);

    // Maps hash of "foo" with rendered string "bar"
    cache.store_blended_latin1("foo"_hs, "bar", renderer);

    // Obtains reference to cached string texture
    auto& texture = cache.get_stored("foo"_hs");

    // Obtains pointer to cached string texture, doesn't throw
    if (auto* ptr = cache.try_get_stored("foo"_hs)) {
      // found cached texture!
    }
  }