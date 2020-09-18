scan_code
=========

The ``scan_code`` class represents a key at a specific location, no matter what keyboard 
layout is being used. Scan codes are layout independent, but the locations are based on 
a QWERTY keyboard. For example, the key associated with the scan code "A" will feature different labels on keyboards
using other layouts than QWERTY, such as DVORAK. However, the location of the keys will be 
the same. As a result, this makes scan codes useful for key binds that are chosen based on their
position and ergonomics, rather than their meaning. An example is the fact that the WASD are ubiquitously 
used as movement keys in games.

General information
-------------------
======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    Yes
Copyable                 Yes
Movable                  Yes
Implicit conversions     None
Explicit conversions     ``SDL_Scancode``, ``SDL_KeyCode``
Overloaded operators     ``<<``
Namespace                ``::cen``
Header                   ``scan_code.hpp``
======================  =========================================

Interface 
---------

.. doxygenclass:: cen::scan_code
  :members:
  :undoc-members:
  :outline:
  :no-link:

Related functions
-----------------

.. doxygenfunction:: to_string(const scan_code &scanCode) -> std::string
  :outline:
  :no-link:

.. doxygenfunction:: operator<<(std::ostream &stream, const scan_code &scanCode) -> std::ostream&
  :outline:
  :no-link:

See also
--------

* :doc:`scan_code constants </pages/api/input/scan_codes>`
* :doc:`key_code </pages/api/input/key_code>`