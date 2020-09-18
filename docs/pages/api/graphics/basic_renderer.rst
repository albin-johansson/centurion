basic_renderer
==============

The ``basic_renderer`` class provides the base implementation for the 
renderers in the library. Both ``renderer`` and ``renderer_handle`` are
subclasses of ``basic_renderer``.

General information
-------------------

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    No
Copyable                 Yes
Movable                  Yes
Implicit conversions     None
Explicit conversions     None
Namespace                ``::cen``
Header                   ``basic_renderer.hpp``
======================  =========================================

Interface 
---------

.. doxygenclass:: cen::basic_renderer
  :members: 
  :undoc-members:
  :outline:
  :no-link:

Examples
--------

Text rendering
~~~~~~~~~~~~~~

Three different text encodings are supported: UTF-8, Latin-1 and Unicode. Each of these
encodings can be rendered in four different styles: "blended", "shaded", "solid" and 
"blended and wrapped". The following image displays a piece of text rendered with the 
various options.

.. image:: ../../../../meta/text_rendering.png
  :alt: Differences between the four text rendering styles.

* **Blended**: The best looking option but also the slowest. Uses anti-aliasing.
* **Blended and wrapped**: Same as blended, but the text will be wrapped to fit a specified width.
* **Solid**: The fastest option. Doesn't use anti-aliasing so it will look a bit harsh.
* **Shaded**: The same as blended, but with a colored rectangle behind it.

All of the text rendering functions feature the same names except for a distinguishing suffix,
i.e. ``_utf8``, ``_latin1`` or ``_unicode``.

.. code-block:: c++
  
  #include <renderer.hpp>
   
  void demo(cen::renderer& renderer, cen::font& font)
  {
    renderer.set_color(cen::colors::white);

    auto blended = renderer.render_blended_utf8("Never", font);
    auto wrapped = renderer.render_blended_wrapped_utf8("Gonna", 100, font);
    auto shaded = renderer.render_shaded_utf8("Give", cen::colors::pink, font);
    auto solid = renderer.render_solid_utf8("You", font);
  }

See also
--------
* :doc:`renderer </pages/api/graphics/renderer>`
* :doc:`renderer_handle </pages/api/graphics/renderer_handle>`