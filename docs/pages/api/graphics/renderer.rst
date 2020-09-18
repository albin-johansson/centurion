renderer
========

The ``renderer`` class represents an owning renderer. It's serves as the main
interface for hardware-accelerated rendering in the Centurion library.

Rendering textures
------------------

There are quite a number of methods provided for rendering ``texture`` instances. There are 
two "overload" sets, ``render`` and ``render_t``. These methods can be used with either integer 
or floating-point accuracy.

Translation
-----------

Most games utilize some sort of viewport of what the player can see of the game world. If 
you're game features some sort of movable anchor for the rendering, then you need to translate 
the positions of the various game objects when rendering. This class provides a simple API for 
dealing with this easily. Specify the translation viewport with ``set_translation_viewport``, 
and use the rendering methods that feature the ``_t`` suffix in their names, such as ``render_t``, 
to automatically render at translated positions.

Font support
------------

When rendering text, it's often needed to pass around fonts. As a result, this class provides 
an API for storing and managing ``font`` instances. The fonts are stored in an internal map, and
is capable of using string identifiers that are hashed at compile-time as keys!

General information
-------------------

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    No
Copyable                 No
Movable                  Yes
Implicit conversions     None
Explicit conversions     ``SDL_Renderer*``, ``const SDL_Renderer*``
Namespace                ``::cen``
Header                   ``renderer.hpp``
======================  =========================================

Interface 
---------

.. doxygenclass:: cen::renderer
  :members: 
  :undoc-members:
  :outline:
  :no-link:

Examples
--------

Typical rendering method
~~~~~~~~~~~~~~~~~~~~~~~~
The following example illustrates how a typical rendering method looks like using 
the renderer.

.. code-block:: c++
  
  #include <cen.hpp>
  #include <renderer.hpp>

  void draw(cen::renderer& renderer)
  {
    renderer.clear_with(cen::colors::black); // clear rendering target

    // Miscellaneous rendering calls...

    renderer.present(); // apply the rendering operations to the target
  }  

Font handling
~~~~~~~~~~~~~
As previously mentioned, the ``renderer`` class provides storage of ``font`` instances. The
following example demonstrates all of the various methods available for font handling.

.. code-block:: c++
  
  #include <cen.hpp>
  #include <renderer.hpp>

  void font_demo(cen::renderer& renderer)
  {
    constexpr auto id = "Comic Sans"_hs; // compile time hashed string!
    if (renderer.has_font(id)) {
      renderer.remove_font(id);
    } else {
      renderer.add_font(id, cen::font{"comic_sans.ttf", 12});
      auto& font = renderer.get_font(id);
    }
  }

See also
--------
* :doc:`renderer_handle </pages/api/graphics/renderer_handle>`