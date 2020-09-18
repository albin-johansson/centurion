Window
======

The ``window`` class is the main representation of a window in the library. It's a subclass of 
``basic_window`` that features owning semantics. Every window instance can have at most one associated 
renderer. For a window with non-owning semantics, see ``window_handle``.

General information
-------------------
======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    Yes
Copyable                 No
Movable                  Yes
Implicit conversions     None
Explicit conversions     ``SDL_Window*``, ``const SDL_Window*``
Namespace                ``::cen``
Printable                Yes
Namespace                ``::cen``
Header                   ``window.hpp``
======================  =========================================

Interface 
---------

.. doxygenclass:: cen::window
  :members:
  :undoc-members:
  :outline:
  :no-link:

Example
-------
The following example illustrates a typical setup for a responsive window.

.. code-block:: c++

  #include <cen.hpp>
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

      const cen::rect_i rect{{100, 100}, {150, 80}};
      renderer.set_color(cen::colors::pink);
      renderer.fill_rect(rect);

      renderer.present();
    }

    window.hide();
  }

See also
--------
* :doc:`Window view </pages/api/graphics/window_handle>`