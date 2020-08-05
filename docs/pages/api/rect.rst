Rect
====

A simple ``constexpr``-enabled rectangle. Supports ``int`` and ``float`` variants. This class is
designed to mirror the use of the SDL rectangle representations, i.e. ``SDL_Rect`` and
``SDL_FRect``. The underlying representation is the ``basic_rect<T>`` class. However, you should
use the ``irect`` and ``frect`` aliases in your projects, unless you have to write code that
deals with generic rectangles.

General information
-------------------
======================  =======================================================
  Property               Value
----------------------  -------------------------------------------------------
Default constructible    Yes
Copyable                 Yes
Movable                  Yes
Implicit conversions     None
Explicit conversions     ``rect_type*``, ``const rect_type*``
Overloaded operators     ``<<``, ``==``, ``!=``
Namespace                ``::centurion``
Header                   ``rect.hpp``
======================  =======================================================

Public member types/constants
-----------------------------
The ``basic_rect<T>`` class provides several public members that are useful when working
with generic code.

``rect_type``
~~~~~~~~~~~~~
This is the actual rectangle representation, i.e. ``SDL_Rect`` or ``SDL_FRect``. 

``point_type``
~~~~~~~~~~~~~~
The associated point type, i.e. ``ipoint`` or ``fpoint``. 

``area_type``
~~~~~~~~~~~~~
The associated area type, i.e. ``iarea`` or ``farea``. 

``value_type``
~~~~~~~~~~~~~~
The type of the components of the rectangle, i.e. ``int`` or ``float``.

``isIntegral``
~~~~~~~~~~~~~~
Indicates whether or not the rectangle is based on an integral type, e.g. ``true`` for ``irect``.

``isFloating``
~~~~~~~~~~~~~~
Indicates whether or not the rectangle is based on a floating-point type, e.g. ``true`` for
``frect``.

Examples
--------

Casting between rectangle types
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: c++

  #include <centurion_as_ctn.hpp>
  #include <rect.hpp>

  void demo()
  {
    const ctn::irect rect{{10, 15}, {100, 150}};

    // from irect to frect
    auto fr = ctn::cast<ctn::frect>(rect);

    // from frect to irect
    auto ir = ctn::cast<ctn::irect>(fr);
  }

Intersection checking
~~~~~~~~~~~~~~~~~~~~~
Two rectangles are considered to be intersecting if they overlap each other.

.. code-block:: c++

  #include <centurion_as_ctn.hpp>
  #include <rect.hpp>

  void demo()
  {
    const ctn::irect a{{0, 0}, {10, 10}};
    const ctn::irect b{{5, 0}, {10, 10}};

    const ctn::irect c{{100, 100}, {10, 10}};

    // returns true
    if (ctn::intersects(a, b))) { ... }

    // returns false
    if (ctn::intersects(a, c)) { ... }
  }

Collision checking
~~~~~~~~~~~~~~~~~~
Two rectangles are considered to be colliding if the overlap *or* if they share a common border.

.. code-block:: c++

  #include <centurion_as_ctn.hpp>
  #include <rect.hpp>

  void demo()
  {
    const ctn::irect a{{0, 0}, {10, 10}};
    const ctn::irect b{{10, 0}, {10, 10}};
    const ctn::irect c{{100, 100}, {10, 10}};
  
    // returns true
    if (ctn::collides(a, b)) { ... }

    // returns false
    if (ctn::collides(a, c)) { ... }
  }

Calculate union of two rectangles
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
You can easily obtain the union of two rectangles using the ``get_union`` function. Note, unlike
the function provided by SDL, this also works with floating-point rectangles.

.. code-block:: c++

  #include <centurion_as_ctn.hpp>
  #include <rect.hpp>

  void demo()
  {
    constexpr ctn::irect fst{{0, 0}, {10, 10}};
    constexpr ctn::irect snd{{10, 0}, {10, 10}};
  
    constexpr auto result = ctn::get_union(fst, snd);
  }