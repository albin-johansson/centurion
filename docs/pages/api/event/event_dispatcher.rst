event_dispatcher
================

This class is designed to simplify event handling in applications. A common 
pattern is that in your game loop you'd have an inner event loop, in which 
you'd check for the events that you're interested in dealing with. With 
Centurion this could look something like the following.

.. code:: c++

  cen::event event;
  while (running) {
    while (event.poll()) {
      if (const auto* qe = event.try_get<cen::quit_event>()) {
        running = false;
        break;
      } else if (const auto* we = event.try_get<cen::window_event>()) {
        // handle window event
      } else if (const auto* kbe = event.try_get<cen::keyboard_event>()) {
        // handle keyboard event
      } // likely a lot more if statements in most games...
    }

    // update game logic...

    // render game...
  }

Now this isn't exactly terrible, but it can get annoying and hard to read due 
to long lines and obscure variable names (e.g. ``qe``, ``we``, ``kbe``). It would 
be nicer if we could have designated functions that handled different events, so that 
in our hypothetical game class ``Game``, we could have a member function
``Game::on_quit_event(const cen::quit_event& event)``. This would be quite nice since it would 
be easy to separate different event handlers and it leads to much nicer to read code. The 
``event_dispatcher`` class makes this possible.

To use the ``event_dispatcher`` class, we supply the events that we are interested in
handling as template parameters, which are referred to as the "subscribed" events. So for the
previous example we would supply ``cen::quit_event``, ``cen::window_event`` and ``cen::keyboard_event``
as template parameters. By connecting event handlers to these subscribe events, all we need to do
in our game loop is to call the ``poll()`` function of ``event_dispatcher``, see the examples for
how to set event handlers. The game loop from the previous example could look like the
following using an event dispatcher instance.

.. code:: c++

  while (running) {
    m_dispatcher.poll(); 

    // update game logic...

    // render game...
  }

.. note::

  Since it is common to handle quite a number of events, it is recommended to define an alias 
  for the event dispatcher in your applications, since the type name will become quite long.

General information
-------------------

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    Yes
Copyable                 Yes
Movable                  Yes
Implicit conversions     None
Explicit conversions     None
Overloaded operators     ``<<``
Printable                Yes
Namespace                ``::cen``
Header                   ``event_dispatcher.hpp``
Since                    5.1.0
======================  =========================================

Interface 
---------

.. doxygenclass:: cen::experimental::event_dispatcher
  :members:
  :undoc-members:
  :outline:
  :no-link:

Examples
--------

Free functions as event handlers
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code:: C++

  #include <event_dispatcher.hpp>

  using dispatcher_t = cen::event_dispatcher<cen::window_event>;

  void on_window_event(const cen::window_event& event) {
    // handle window event
  }

  void foo() 
  {
    dispatcher_t dispatcher;

    // Obtain desired event sink and supply function pointer
    dispatcher.bind<cen::window_event>().to<&on_window_event>();

    // Alternatively, you could use the callable overload directly
    dispatcher.bind<cen::window_event>().to(&on_window_event);
  }

Member functions as event handlers
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Using member functions as event handlers is probably the most elegant approach. This 
approach is especially nice since it's so easy to access the necessary game state 
since we're able to access member data.

.. code:: C++

  #include <event_dispatcher.hpp>

  using dispatcher_t = cen::event_dispatcher<cen::quit_event, cen::keyboard_event>;

  class Game {
   public:
    Game() {
      // Obtain event sink and supply function pointer and object pointer
      m_dispatcher.bind<cen::quit_event>().to<&Game::on_quit_event>(this);
      m_dispatcher.bind<cen::keyboard_event>().to<&Game::on_keyboard_event>(this);
    }

    void run() 
    {
      while (m_running) {
        m_dispatcher.poll();
        // ...
      }
    }

   private:
    dispatcher_t m_dispatcher;
    bool m_running{true};

    void on_quit_event(const cen::quit_event& event) {
      m_running = false;
    }

    void on_keyboard_event(const cen::keyboard_event& event) {
      // handle keyboard events...
    }
  };

Callables as event handlers
~~~~~~~~~~~~~~~~~~~~~~~~~~~

It is possible to use any kind of callable as event handlers, such as lambdas. It is 
possible to use lambdas with captures, but as always, be careful of lifetimes when
capturing by reference (i.e. when using ``[&]``).

.. code:: C++ 

  #include <event_dispatcher.hpp>

  using dispatcher_t = cen::event_dispatcher<cen::quit_event, cen::keyboard_event>;

  void foo() 
  {
    dispatcher_t dispatcher;

    // Obtain event sink and supply callable
    dispatcher.bind<cen::keyboard_event>().to([](const cen::keyboard_event& event) {
      // handle keyboard event
    });
  }

See also
--------
* :doc:`Event </pages/api/event/event>`
