key_code
========

The ``key_code`` class represents a key code, also known as a virtual key. Key codes are 
mapped depending on the layout of the system keyboard, such as QWERTY or DVORAK. Whilst 
scan codes identify the location of key presses, key codes correspond to the labels of keys.
As a result, key codes can be useful for key binds where the chosen key carries meaning. For example,
in many games "I" is used to open the player inventory. By using key codes, we can ensure that the bind 
makes sense no matter what keyboard layout is being used.

General information
-------------------
======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    Yes
Copyable                 Yes
Movable                  Yes
Implicit conversions     None
Explicit conversions     ``SDL_KeyCode``, ``SDL_Keycode``, ``SDL_Scancode``
Overloaded operators     ``<<``
Namespace                ``::cen``
======================  =========================================

Interface 
---------

.. doxygenclass:: cen::key_code
  :members:
  :undoc-members:
  :outline:
  :no-link:

Related functions
-----------------

.. doxygenfunction:: to_string(const key_code &keyCode) -> std::string
  :outline:
  :no-link:

.. doxygenfunction:: operator<<(std::ostream &stream, const key_code &keyCode) -> std::ostream&
  :outline:
  :no-link:

Examples
--------

.. code-block:: C++

  #include <key_code.hpp>

  void foo()
  {
    constexpr cen::key_code a{SDLK_a}; // compile-time key code
    cen::key_code b{"b"};              // key code from name
    cen::key_code c{SDL_SCANCODE_C};   // key code from SDL scan code
  }

See also
--------

* :doc:`key_code constants </pages/api/input/key_codes>`
* :doc:`scan_code </pages/api/input/scan_code>`