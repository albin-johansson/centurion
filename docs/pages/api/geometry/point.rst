Point
=====

A simple ``constexpr``-enabled two-dimensional point. The point class
is designed to act as a wrapper around either of the SDL point types, 
i.e. ``SDL_Point`` and ``SDL_FPoint``. The underlying representation is 
the ``basic_point<T>`` class. However, you should use the ``ipoint``
and ``fpoint`` aliases in your project, unless you have to write code that
deals with generic points.

General information
-------------------

======================  =======================================================
  Property               Value
----------------------  -------------------------------------------------------
Default constructible    Yes
Copyable                 Yes
Movable                  Yes
Implicit conversions     None
Explicit conversions     ``point_type``, ``point_type*``, ``const point_type*``
Overloaded operators     ``<<``, ``+``, ``-``, ``==``, ``!=``
Namespace                ``::cen``
Header                   ``point.hpp``
======================  =======================================================

Public member types/constants
-----------------------------

The ``basic_point<T>`` class provides a few useful public members that are useful when working
with generic code.

point_type
~~~~~~~~~~

This is the actual point representation, i.e. ``SDL_Point`` or ``SDL_FPoint``. 

value_type
~~~~~~~~~~

This is the type of the coordinates of the point. In other words, ``int`` or ``float``.

isIntegral
~~~~~~~~~~

Indicates whether or not the point is based on an integral type, e.g. ``true`` for ``ipoint``.

isFloating
~~~~~~~~~~

Indicates whether or not the point is based on a floating-point type, e.g. ``true`` for ``fpoint``.

Interface 
---------

.. doxygenclass:: cen::basic_point
  :members:
  :undoc-members:
  :outline:
  :no-link:

Examples
--------

Distance between points
~~~~~~~~~~~~~~~~~~~~~~~

You can easily obtain the distance between two points using the 
``distance`` function, it's templated so it works on both point types.

.. code-block:: c++

  #include <cen.hpp>
  #include <point.hpp>

  void demo() 
  {
    const cen::fpoint a{1.2f, 3.4f};
    const cen::fpoint b{5.6f, 7.8f};

    const auto dist = cen::distance(a, b);
  }
