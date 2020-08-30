Font
====

The ``font`` class represents a TrueType font. You can use instances
of this class for querying information about fonts and rendering
text to the screen.

General information
-------------------
======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    No
Copyable                 No
Movable                  Yes
Implicit conversions     None
Explicit conversions     ``TTF_Font*``, ``const TTF_Font*``
Overloaded operators     ``<<``
Printable                Yes
Namespace                ``::centurion``
Header                   ``font.hpp``
======================  =========================================

Interface 
---------

.. doxygenclass:: centurion::font
  :members:
  :undoc-members:
  :outline:
  :no-link:

Examples
--------

Styling
~~~~~~~

.. code-block:: c++
  :linenos:
  
  #include <centurion_as_ctn.hpp>
  #include <font.hpp>

  void styling_demo() 
  {
    cen::font font{"arial.ttf", 12}; 

    // set style
    font.set_bold(true);
    font.set_italic(true);
    font.set_strikethrough(true);
    font.set_underlined(true);
    font.set_outlined(true);

    // query current style
    if (font.is_bold()) { ... }
    if (font.is_italic()) { ... }
    if (font.is_strikethrough()) { ... }
    if (font.is_underlined()) { ... }
    if (font.is_outlined()) { ... }

    // reset style to the default style
    font.reset();
  }

Font information
~~~~~~~~~~~~~~~~

Unsurprisingly, the ``font`` class provides many functions that can 
be used to obtain various information about the font face.

.. code-block:: c++
  :linenos:
  
  #include <centurion_as_ctn.hpp>
  #include <font.hpp>

  void font_info_demo() 
  {
    cen::font font{"arial.ttf", 12}; 

    // The size of the font (12 in this example)
    int size = font.size();

    // The maximum height of a glyph in the font
    int height = font.height();

    // Detailed information about the font
    int descent = font.descent();
    int ascent = font.ascent();
    bool kerning = font.kerning();
    auto hinting = font.font_hinting();
    auto style = font.style_name();
    auto family = font.family_name();

    // The height of a line skip using the font
    int lineSkip = font.line_skip();

    // The number of font faces provided with the font
    int nFontFaces = font.font_faces();
  }

Glyph information
~~~~~~~~~~~~~~~~~

The ``font`` class provides various functions for obtaining information
about glyphs in the font. This is utilized extensively by the ``font_cache``
class, in order to enable fast text rendering.

.. code-block:: c++
  :linenos:
   
  #include <centurion_as_ctn.hpp>
  #include <font.hpp>

  void glyph_info_demo() 
  {
    cen::font font{"arial.ttf", 12}; 

    // Obtain the kerning amount between to glyphs
    int kerning = font.kerning_amount('a', 'V');

    // Check whether or not a glyph is provided in the font
    bool provided = font.is_glyph_provided('x');

    // Obtain detailed metrics for a glyph in the font
    if (auto metrics = font.get_metrics('x'); metrics) {
      ...
    }
  }

String information
~~~~~~~~~~~~~~~~~~

It's possible to determine the size of a rendered string, without 
actually having to render the string. 

.. code-block:: c++
  :linenos:
  
  #include <centurion_as_ctn.hpp>
  #include <font.hpp>

  void string_info_demo() 
  {
    cen::font font{"arial.ttf", 12}; 

    /* Obtains the dimensions of a string, if it were to be rendered
       using the font. */
    const auto [width, height] = font.string_size("foobar");

    // Only obtains the width of a string
    const auto w = font.string_width("hello");

    // Only obtains the height of a string
    const auto h = font.string_height("world");
  }

See also
--------
* :doc:`Font cache </pages/api/graphics/font_cache>`
