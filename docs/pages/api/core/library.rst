library
=======

The ``library`` class is responsible for initializing and subsequently 
closing the SDL libraries. You should always create an instance of this 
class in your ``main``-function, which outlives all lifetimes of 
other Centurion components in your application. See the examples for 
typical usage of this class.

It is possible to override the default configuration using the 
:doc:`config </pages/api/core/config>` struct, which is also defined 
in the ``centurion.hpp`` header.

.. warning:: 

  Never mix usage of the ``library`` class with explicit calls to 
  ``SDL_Init()``, ``SDL_Quit()``, etc.

General information
-------------------

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    Yes
Copyable                 No
Movable                  No
Implicit conversions     None
Explicit conversions     None
Overloaded operators     None
Printable                No
Namespace                ``::cen``
Header                   ``centurion.hpp``
Since                    3.0.0
======================  =========================================

Interface 
---------

.. doxygenclass:: cen::library
  :members:
  :undoc-members:
  :outline:
  :no-link:

Examples 
--------

Typical usage 
~~~~~~~~~~~~~

.. code:: C++

  #include <centurion.hpp>

  namespace {

  void run() 
  {
    // run your application...
  }
  
  }  // namespace

  int main(int, char**)
  {
    // Make sure to create a local variable, it isn't enough to just call the constructor!
    const cen::library library; 

    run();
    return 0;
  }

See also
--------
* :doc:`config </pages/api/core/config>`