condition
=========

Condition variables are represented by the ``condition`` class. These can be used by threads to send signals to each other.

General information
-------------------

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    Yes
Copyable                 No
Movable                  Yes
Implicit conversions     None
Explicit conversions     None
Overloaded operators     None
Namespace                ``::cen``
======================  =========================================

Interface 
---------

.. doxygenclass:: cen::condition
  :members:
  :undoc-members:
  :outline:
  :no-link:

Example
-------

The following is a typical use case of condition variables. This is adapted from the SDL example 
that can be found `here <https://wiki.libsdl.org/SDL_CreateCond>`_.

.. code-block:: c++ 

  bool condition{};

  cen::mutex m;
  cen::condition cond;

  Thread A:
    cen::scoped_lock lock{m};
    while (!condition) {
      cond.wait(m);
    }

  Thread B:
    cen::scoped_lock lock{m};
    // ...
    condition = true;
    // ...
    cond.signal();
