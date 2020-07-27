Point
=====

A simple ``constexpr``-enabled two-dimensional point. The point class
is designed to act as a wrapper around either of the SDL point types, 
i.e. ``SDL_Point`` and ``SDL_FPoint``. The underlying representation is 
the ``basic_point<Traits>`` class. However, you should use the ``ipoint`` 
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
Namespace                ``::centurion``
Header                   ``point.hpp``
======================  =======================================================

Member types
------------
The ``basic_point<Traits>`` class provides two public member
types that are useful when working with generic code. 

``point_type``
~~~~~~~~~~~~~~
This is the actual point representation, i.e. ``SDL_Point`` or ``SDL_FPoint``. 

``value_type``
~~~~~~~~~~~~~~
This is the type of the coordinates of the point. In other words, ``int`` or ``float``.

Examples
--------

Distance between points
~~~~~~~~~~~~~~~~~~~~~~~

You can easily obtain the distance between two points using the 
``distance`` function, it's templated so it works on both point types.

.. code-block:: c++

  #include <centurion_as_ctn.hpp>
  #include <point.hpp>

  void demo() 
  {
    const ctn::fpoint a{1.2f, 3.4f};
    const ctn::fpoint b{5.6f, 7.8f};

    const auto dist = ctn::distance(a, b);
  }

Create points by specifying desired coordinate type
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you want to create an ``ipoint`` or ``fpoint`` by specifying the
type of the coordinates (``int`` or ``float``), then you can use the
``make_point<T>`` function. The type parameter is the desired type of
the coordinates.

.. code-block:: c++

  #include <centurion_as_ctn.hpp>
  #include <point.hpp>

  void demo() 
  {
    // a and b are ipoint's
    const auto a = ctn::make_point<int>();
    const auto b = ctn::make_point<int>(5, 8);
    
    // c and d are fpoint's
    const auto c = ctn::make_point<float>();
    const auto d = ctn::make_point<float>(93.3f, 12.3f);
  }
