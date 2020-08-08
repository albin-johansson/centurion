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
Namespace                ``::centurion``
Printable                Yes
Namespace                ``::centurion``
Header                   ``window.hpp``
======================  =========================================

Interface 
---------

.. doxygenclass:: centurion::window
  :members:
  :undoc-members:
  :outline:
  :no-link:

Example
-------
The following example illustrates a typical setup for a responsive window.

.. code-block:: c++

  #include <centurion_as_ctn.hpp>
  #include <window.hpp>
  #include <renderer.hpp>
  #include <event.hpp>
  #include <rect.hpp>

  void demo()
  {
    ctn::window window;
    ctn::renderer renderer{window};

    window.set_title("Window demo");

    ctn::event event;
    bool running = true;

    window.show();
    while (running) {
      while (event.poll()) {
        if (event.is<ctn::quit_event>()) {
          running = false;
          break;
        }
      }

      renderer.clear_with(ctn::colors::black);

      const ctn::rect_i rect{{100, 100}, {150, 80}};
      renderer.set_color(ctn::colors::pink);
      renderer.fill_rect(rect);

      renderer.present();
    }

    window.hide();
  }

See also
--------
* :doc:`Window view </pages/api/graphics/window_handle>`