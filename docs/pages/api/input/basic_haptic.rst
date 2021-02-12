basic_haptic
============

Represents a haptic (force feedback) device. This class has both owning and non-owning versions, 
``haptic`` and ``haptic_handle``, respectively.

General information
-------------------

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    Only ``haptic``
Copyable                 Only ``haptic_handle``
Movable                  Yes
Implicit conversions     None
Explicit conversions     None
Overloaded operators     ``<<``, ``bool`` (only ``haptic_handle``)
Namespace                ``::cen``
Header                   ``haptic.hpp``
Since                    5.2.0
======================  =========================================

Interface 
---------

.. doxygenclass:: cen::basic_haptic
  :members:
  :undoc-members:
  :outline:
  :no-link:

Examples
--------

Utilising a haptic mouse device
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code:: C++

  #include <haptic.hpp>

  void foo() 
  {
    if (cen::haptic::is_mouse_haptic()) {
      auto haptic = cen::haptic::from_mouse();
      // Haptic device ready to be used!
    }
  }

Utilising a haptic joystick device
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code:: C++

  #include <joystick.hpp>
  #include <haptic.hpp>

  void foo() 
  {
    if (cen::joystick::count() == 0) {
      return;
    }

    cen::joystick joystick;
    if (cen::haptic::is_joystick_haptic(joystick)) {
      auto haptic = cen::haptic::from_joystick(joystick);
      // Haptic device ready to be used!
    }
  }