Window view
===========

Unlike ``window``, the ``window_view`` class represents a non-owning window. Which means that it
does *not* claim ownership of the associated ``SDL_Window*``. This makes this class useful for
migrating projects that make heavy use of raw pointers to SDL components. However, misuse of this
class may cause memory leaks if you're not careful.

.. warning::

  In the vast majority of cases, you want to use the ``window`` class instead of ``window_view``.

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
Header                   ``window.hpp``
======================  =========================================

Example
-------
The following example demonstrates how ``window_view`` can be used to enable use of the
user-friendly Centurion window API, without actually claiming ownership. The example assumes that
you, for some reason, can't change the signature of a function that takes a ``SDL_Window*``
parameter. Which is the main use case of the ``window_view`` class.

.. note::

  It's very cheap to create an instance of ``window_view``, it's just a copy of a pointer!

.. code-block:: c++

  #include <centurion_as_ctn.hpp>
  #include <window.hpp>

  void foo(SDL_Window* window)
  {
    ctn::window_view view{window};

    view.set_title("bar");

    if (view.fullscreen()) {
      // ...
    }

    const auto x = view.x();
    const auto y = view.y();
  }

See also
--------
* :doc:`Window </pages/api/graphics/window>`