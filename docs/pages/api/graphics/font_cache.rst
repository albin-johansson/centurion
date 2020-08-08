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
Printable                No
Namespace                ``::centurion``
Header                   ``font_cache.hpp``
Since                    5.0.0
======================  =========================================

Interface
---------

.. doxygenclass:: centurion::font_cache
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
  #include <centurion_as_ctn.hpp>

  void foo() 
  {
    ctn::window window;
    ctn::renderer renderer{window};
    ctn::font_cache cache{"arial.ttf", 12};

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
  #include <centurion_as_ctn.hpp>

  void foo() 
  {
    ctn::window window;
    ctn::renderer renderer{window};
    ctn::font_cache cache{"arial.ttf", 12};

    // Maps hash of "foo" with rendered string "bar"
    cache.store("foo"_hs, renderer.render_blended_latin1("bar", cache.get_font());
  }