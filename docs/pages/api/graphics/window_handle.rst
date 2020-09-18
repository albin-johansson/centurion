window_handle
=============

Unlike ``window``, the ``window_handle`` class represents a non-owning window. Which means that it
does *not* claim ownership of the associated ``SDL_Window*``. This makes this class useful for
migrating projects that make heavy use of raw pointers to SDL components. However, misuse of this
class may cause memory leaks if you're not careful. This class is a subclass of ``basic_window``.

.. note::

  You should prefer using ``window`` over ``window_handle`` wherever possible.

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
Overloaded operators     ``<<``, ``bool``
Printable                Yes
Namespace                ``::cen``
Header                   ``window_handle.hpp``
Since                    5.0.0
======================  =========================================

Interface
---------

.. doxygenclass:: cen::window_handle
  :members:
  :undoc-members:
  :outline:
  :no-link:

Example
-------
The following example demonstrates how ``window_handle`` can be used to enable use of the
user-friendly Centurion window API, without actually claiming ownership of the SDL window. 
The example assumes that we, for some reason, can't change the signature of a function that 
features a ``SDL_Window*`` parameter.

.. note::

  It's very cheap to create an instance of ``window_view``, it's just a copy of a pointer!

.. code-block:: c++

  #include <window_handle.hpp>

  void foo(SDL_Window* window)
  {
    cen::window_handle handle{window};

    handle.set_title("bar");

    if (handle.fullscreen()) {
      // ...
    }

    const auto x = handle.x();
    const auto y = handle.y();

    // ...

  } // the SDL window isn't destroyed!

See also
--------
* :doc:`Window </pages/api/graphics/window>`