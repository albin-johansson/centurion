Renderer
========

The primary class for rendering is ``basic_renderer<T>``. Which represents an owning renderer.
The template parameter is the type of the keys used to lookup fonts stored in an internal map. 
Don't worry, you don't have to (and shouldn't) type ``basic_renderer<T>`` all the time. The 
library provides the ``renderer`` and ``renderer_i`` aliases, that correspond to 
``basic_renderer<std::string>`` and ``basic_renderer<int>`` respectively. 

.. tip::

  Use either one of the ``renderer`` or ``renderer_i`` aliases, or define your own alias instead
  of using ``basic_renderer<T>`` everywhere.

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
an API for storing shared pointers to ``font`` instances. The fonts are stored in an internal map, and
it's possible to specify what you want to use as keys for the fonts. The ``renderer`` alias uses 
``std::string`` as the key type.

Rendering text
--------------
There is no method for directly rendering text. Instead, use one of the ``text_`` methods for creating 
textures that contain a rendered piece of text, and subsequently render the textures when needed. 
Naturally, you should cache these textures instead of repeatedly creating and destroying them in 
your game loop.

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
Namespace                ``::centurion``
Header                   ``graphics.hpp``
======================  =========================================

Examples
--------

Initialization
~~~~~~~~~~~~~~
A renderer is always created based on a window. The following displays how easy it
is to create a window and an associated renderer with Centurion.

.. code-block:: c++

  #include <centurion_as_ctn.hpp>
  #include <graphics.hpp>
  #include <window.hpp>

  void setup()
  {
    ctn::window window;
    ctn::renderer renderer{window};

    // That's it! Now we have our window and renderer
  }

Rendering method
~~~~~~~~~~~~~~~~
The following example illustrates how a typical rendering method looks like using 
the renderer.

.. code-block:: c++

  #include <centurion_as_ctn.hpp>
  #include <graphics.hpp>

  void draw(ctn::renderer& renderer)
  {
    renderer.clear_with(ctn::black); // clear rendering target

    // Miscellaneous rendering calls...

    renderer.present(); // apply the rendering operations to the target
  }  

Font handling
~~~~~~~~~~~~~
As previously mentioned, the ``basic_renderer`` class provides storage of ``font`` instances.
The following example demonstrates all of the various methods available for font handling.

.. code-block:: c++

  #include <centurion_as_ctn.hpp>
  #include <graphics.hpp>

  void font_demo(ctn::renderer& renderer)
  {
    if (renderer.has_font("Comic Sans")) {
      renderer.remove_font("Comic Sans");
    } else {
      renderer.add_font("Comic Sans", ctn::font::shared("comic_sans.ttf", 12));
      auto font = renderer.font("Comic Sans");
    }
  }

Text rendering
~~~~~~~~~~~~~~
There are four options when rendering text. You can render text that is "blended",
"shaded", "solid" and "blended and wrapped". The following image displays a piece of text
rendered with the various options.

.. image:: ../../meta/text_rendering.png

* **Blended**: The best looking option but also the slowest. Uses anti-aliasing.
* **Blended and wrapped**: Same as blended, but the text will be wrapped to fit a specified width.
* **Solid**: The fastest option. Doesn't use anti-aliasing so it will look a bit harsh.
* **Shaded**: The same as blended, but with a colored rectangle behind it.

.. code-block:: c++
 
  #include <centurion_as_ctn.hpp>
  #include <graphics.hpp>
   
  void text_rendering_demo(ctn::renderer& renderer)
  {
    renderer.set_color(ctn::white);

    auto font = renderer.font("Arial");

    auto blended = renderer.text_blended("Never", *font);
    auto wrapped = renderer.text_blended_wrapped("Gonna", 100, *font);
    auto shaded = renderer.text_shaded("Give", ctn::pink, *font);
    auto solid = renderer.text_solid("You", *font);
  }

See also
--------
* :doc:`Renderer view </pages/renderer_view>`