event
=====

The ``event`` class serves as the main interface for dealing with events. This class handles 
events and can be queried to obtain concrete event representations.

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
Overloaded operators     None
Namespace                ``::cen``
======================  =========================================

Interface 
---------

.. doxygenclass:: cen::event
  :members:
  :undoc-members:
  :outline:
  :no-link:

Related functions 
-----------------

.. doxygenfunction:: as_sdl_event(const common_event<T> &event) -> SDL_Event
  :outline:
  :no-link:

Event types
-----------

All event types are defined in the ``event.hpp`` header, for more 
details about any specific event, refer to the Doxygen or in-source 
documentation.

.. note:: 

  All event classes in the Centurion library inherit from ``cen::common_event<T>``.

=============================  ===============================
 Event class                    SDL counterpart
-----------------------------  -------------------------------
 ``audio_device_event``         ``SDL_AudioDeviceEvent``
 ``controller_axis_event``      ``SDL_ControllerAxisEvent``
 ``controller_button_event``    ``SDL_ControllerButtonEvent``
 ``controller_device_event``    ``SDL_ControllerDeviceEvent``
 ``dollar_gesture_event``       ``SDL_DollarGestureEvent``
 ``drop_event``                 ``SDL_DropEvent``
 ``event``                      ``SDL_Event``
 ``joy_axis_event``             ``SDL_JoyAxisEvent``
 ``joy_ball_event``             ``SDL_JoyBallEvent``
 ``joy_button_event``           ``SDL_JoyButtonEvent``
 ``joy_device_event``           ``SDL_JoyDeviceEvent``
 ``joy_hat_event``              ``SDL_JoyHatEvent``
 ``keyboard_event``             ``SDL_KeyboardEvent``
 ``mouse_button_event``         ``SDL_MouseButtonEvent``
 ``mouse_motion_event``         ``SDL_MouseMotionEvent``
 ``mouse_wheel_event``          ``SDL_MouseWheelEvent``
 ``multi_gesture_event``        ``SDL_MultiGestureEvent``
 ``quit_event``                 ``SDL_QuitEvent``
 ``text_editing_event``         ``SDL_TextEditingEvent``
 ``text_input_event``           ``SDL_TextInputEvent``
 ``touch_finger_event``         ``SDL_TouchFingerEvent``
 ``window_event``               ``SDL_WindowEvent``
=============================  ===============================

Examples
--------

Typical usage
~~~~~~~~~~~~~

.. code-block:: C++

  #include <event.hpp>

  void foo()
  {
    cen::event event;
    bool running{true};

    while (running) {
      while (event.poll()) {
        if (event.is<cen::quit_event>()) {
          running = false;
          break;
        }
        // handle more events...
      }
      // handle miscellaneous logic and rendering here
    }
  }

Querying the event representation by pointer
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following code snippet demonstrates an idiomatic way to use the ``event`` 
class to check for a set of events that you are interested in handling. The ``try_get`` 
function simply returns a null pointer if the internal event type doesn't match the desired
event.

.. code-block:: C++

  #include <event.hpp>

  void foo(cen::event& event)
  {
    if (const auto* kbe = event.try_get<cen::keyboard_event>()) {
      // keyboard event
    } else if (const auto* mbe = event.try_get<cen::mouse_button_event>()) {
      // mouse button event
    } else if (const auto* mme = event.try_get<cen::mouse_motion_event>()) {
      // mouse motion event
    }
    // ...
  }

Querying the event representation by reference
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It's also possible to obtain a reference the internal event representation using the 
``get`` function. However, unlike ``try_get``, it will throw an exception if the desired 
event type doesn't match the internal event representation.

.. code-block:: C++

  #include <event.hpp>

  void foo(cen::event& event)
  {
    const auto& kbe = event.get<cen::keyboard_event>(); // throws upon type mismatch
    // use the event...
  } 

Checking whether or not the event is of a specific type
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Sometimes, it's not necessary to obtain a reference or pointer to the event representation 
instance. In that case, it sufficient to check whether the internal event is of some specific 
type. This can be accomplished with the ``is`` function.

.. code-block:: C++

  #include <event.hpp>

  void foo(cen::event& event)
  {
    // no need to handle quit event instance, just need to know that it is a quit event
    if (event.is<cen::quit_event>()) {
      // quit application...
    }
  } 

See also
--------
* :doc:`event_dispatcher </pages/api/event/event_dispatcher>`
