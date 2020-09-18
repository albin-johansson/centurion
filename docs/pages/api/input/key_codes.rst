key_code constants
==================

The ``cen::keycodes`` namespace contains a large set of ``key_code`` constants. These 
can be useful when checking whether or not certain keys are being pressed when handling events,
for instance. These constants are provided in the ``key_code.hpp`` header, along with the 
``key_code`` class.

Constants
---------

.. doxygennamespace:: cen::keycodes
  :members:
  :undoc-members:
  :outline:
  :no-link:

Examples
--------

.. code-block:: C++

  #include <key_code.hpp>
  #include <event.hpp>

  void foo(cen::event& event)
  {
    if (const auto* kb = e.try_get<cen::keyboard_event>()) {
      if (kb->is_active(cen::keycodes::x)) {
        // "X" is the key code associated with the event
      } else if (kb->is_active(cen::keycodes::y)) {
        // "Y" is the key code associated with the event
      }
    }
  }