basic_window
============

The ``basic_window`` class represents an operating system window. The aliases ``window`` and ``window_handle`` represent 
owning and non-owning versions windows, respectively.

General information
-------------------
======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    No
Copyable                 Only ``window_handle``
Movable                  Both ``window`` and ``window_handle``
Implicit conversions     None
Explicit conversions     None
Overloaded operators     None
Namespace                ``::cen``
Header                   ``window.hpp``
======================  =========================================

Interface 
---------

.. doxygenclass:: cen::basic_window
  :members:
  :undoc-members:
  :outline:
  :no-link:

Related functions
-----------------

.. doxygenfunction:: get_renderer(const basic_window<T> &window) noexcept -> renderer_handle
  :outline:
  :no-link:

.. doxygenfunction:: get_grabbed_window() noexcept -> window_handle
  :outline:
  :no-link:

.. doxygenfunction:: get_window_from_id(u32 id) noexcept -> window_handle
  :outline:
  :no-link:

Examples
--------

Typical setup of responsive window
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: c++

  #include <window.hpp>
  #include <renderer.hpp>
  #include <event.hpp>
  #include <rect.hpp>

  void demo()
  {
    cen::window window;
    cen::renderer renderer{window};

    window.set_title("Window demo");

    cen::event event;
    bool running = true;

    window.show();
    while (running) {
      while (event.poll()) {
        if (event.is<cen::quit_event>()) {
          running = false;
          break;
        }
      }

      renderer.clear_with(cen::colors::black);

      const cen::irect rect{{100, 100}, {150, 80}};
      renderer.set_color(cen::colors::pink);
      renderer.fill_rect(rect);

      renderer.present();
    }

    window.hide();
  }

Typical use case for ``window_handle``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following example demonstrates how ``window_handle`` can be used to enable use of the
user-friendly Centurion window API, without actually claiming ownership of the SDL window. 
The example assumes that we, for some reason, can't change the signature of a function that 
features a ``SDL_Window*`` parameter.

.. note::

  It's very cheap to create an instance of ``window_view``, it's just a copy of a pointer!

.. code-block:: c++

  #include <window.hpp>

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
