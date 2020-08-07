Renderer view
=============

Unlike ``renderer<T>``, the ``renderer_view`` class represents a non-owning renderer.
Which means that it does *not* claim ownership of the associated ``SDL_Renderer*``. This 
makes this class useful for migrating projects that make heavy use of raw pointers to SDL 
components. However, misuse of this class may cause memory leaks if you're not careful.

.. warning::

  In the vast majority of cases, you want to use the ``renderer<T>`` class instead of
  ``renderer_view``.


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
Namespace                ``::centurion``
Header                   ``renderer.hpp``
======================  =========================================

Differences with ``renderer<T>``
--------------------------------------
Since ``renderer_view`` is merely a wrapper around an ``SDL_Renderer*``, it only supports a
subset of the API provided by ``renderer<T>``. The missing features are automatic viewport
translation and font handling.

Example
-------
The following example demonstrates how ``renderer_view`` can be used to enable use of the 
Centurion rendering API, without actually claiming ownership. The example assumes that
you, for some reason, can't change the signature of a function that takes a ``SDL_Renderer*``
parameter. Which is the main use case of the ``renderer_view`` class.

.. note::

  It's very cheap to create an instance of ``renderer_view``, it's just a copy of a pointer!

.. code-block:: c++

  #include <centurion_as_ctn.hpp>
  #include <renderer.hpp>

  void draw(SDL_Renderer* renderer)
  {
    ctn::renderer_view view{renderer};

    view.clear_with(ctn::black);

    view.set_color(ctn::pink);
    view.fill_rect(ctn::rect_i{{15, 20}, {100, 100}});
 
    view.present();
  }

See also
--------
* :doc:`Renderer </pages/api/graphics/renderer>`