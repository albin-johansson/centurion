try_lock
========

The ``try_lock`` class represents an RAII-style non-blocking lock that automatically unlocks the associated mutex
upon destruction. It immediately returns after trying to lock a mutex.

General information
-------------------

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    No
Copyable                 No
Movable                  Yes
Implicit conversions     None
Explicit conversions     None
Overloaded operators     None
Printable                No
Namespace                ``::centurion``
Header                   ``try_lock.hpp``
======================  =========================================

Interface 
---------

.. doxygenclass:: centurion::try_lock
  :members:
  :undoc-members:
  :outline:
  :no-link:

Example
-------

The ``try_lock`` class can be used in two different ways. The terse syntax is useful if you don't care whether or not the
lock timed out.

.. code-block:: c++
  
  cen::mutex mutex;
  if (cen::try_lock lock{mutex}; lock.success()) {
    // succeeded to lock mutex
  } else if (lock.timed_out()) {
    // timed out whilst trying to lock
  } else {
    // error locking mutex
  }

  // terse syntax
  cen::try_lock lock{mutex};
  if (lock) {
    // succeeded to lock mutex
  }
