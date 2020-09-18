scan_code constants
===================

The ``cen::scancodes`` namespace contains a large set of ``scan_code`` constants. These 
can be useful when checking whether or not certain keys are being pressed when handling events,
for instance. These constants are provided in the ``scan_code.hpp`` header, along with the 
``scan_code`` class.

Constants
---------

.. doxygennamespace:: cen::scancodes
  :members:
  :undoc-members:
  :outline:
  :no-link:

Examples
--------

.. code-block:: C++

  #include <scan_code.hpp>
  #include <event.hpp>

  void foo(cen::event& event)
  {
    if (const auto* kb = e.try_get<cen::keyboard_event>()) {
      if (kb->is_active(cen::scancodes::w)) {
        // key at the position of "W" is active
      } else if (kb->is_active(cen::keycodes::s)) {
        // key at the position of "S" is active
      }
    }
  }