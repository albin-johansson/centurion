renderer_handle
===============

Unlike ``renderer``, the ``renderer_handle`` class represents a non-owning renderer.
Which means that it does *not* claim ownership of the associated ``SDL_Renderer*``. This 
makes this class useful for migrating projects that make heavy use of raw pointers to SDL 
components.

.. warning::

  In the vast majority of cases, you want to use the ``renderer`` class instead of
  ``renderer_handle``.

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
Header                   ``renderer_handle.hpp``
======================  =========================================

Differences with ``renderer``
-----------------------------

Since ``renderer_handle`` is merely a wrapper around an ``SDL_Renderer*``, it only supports a
subset of the API provided by ``renderer``. The missing features are automatic viewport
translation and font handling.

Example
-------

The following example demonstrates how ``renderer_handle`` can be used to enable use of the 
Centurion rendering API, without actually claiming ownership. The example assumes that
you, for some reason, can't change the signature of a function that takes a ``SDL_Renderer*``
parameter.

.. note::

  It's very cheap to create an instance of ``renderer_handle``, it's just a copy of a pointer!

.. code-block:: c++

  #include <centurion_as_ctn.hpp>
  #include <renderer_handle.hpp>

  void draw(SDL_Renderer* renderer)
  {
    cen::renderer_handle handle{renderer};

    handle.clear_with(cen::colors::black);

    handle.set_color(cen::colors::pink);
    handle.fill_rect(cen::irect{{15, 20}, {100, 100}});
 
    handle.present();
  }

See also
--------
* :doc:`renderer </pages/api/graphics/renderer>`