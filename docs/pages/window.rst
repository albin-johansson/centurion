Window
======

The ``window`` class is the main representation of a window in the library. Every window instance
can have at most one associated renderer. The class is a wrapper around a ``SDL_Window*``, which
it will manage the lifetime of automatically. If you don't want the owning RAII semantics,
there's the ``window_view`` class.

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
Header                   ``window.hpp``
======================  =========================================

Example
-------
The following example illustrates a typical setup for a responsive window. Of course, the example
assumes that the library has been initialized.

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

      renderer.clear_with(ctn::black);

      const ctn::rect_i rect{{100, 100}, {150, 80}};
      renderer.set_color(ctn::pink);
      renderer.fill_rect(rect);

      renderer.present();
    }

    window.hide();
  }

See also
--------
* :doc:`Window view </pages/window_view>`