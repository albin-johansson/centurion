mutex (class)
=============

The ``mutex`` class represents a recursive mutex.

.. note:: 

  Whilst it's possible to use ``mutex`` directly, it's recommended to use 
  one of the lock types for actually locking and unlocking the mutex.

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
Header                   ``mutex.hpp``
======================  =========================================

Interface 
---------

.. doxygenclass:: centurion::mutex
  :members:
  :undoc-members:
  :outline:
  :no-link: