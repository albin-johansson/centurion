RAM
===

The RAM API provides information about the system memory.

General information
-------------------

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Namespace                ``::cen::ram``
Since                    3.0.0
======================  =========================================

Interface
---------

.. doxygennamespace:: cen::ram
  :outline:
  :members:

Examples
--------

.. code-block:: C++
  
  #include <ram.hpp>

  void foo()
  {
    // the amount of system memory, in megabytes
    const auto mb = cen::ram::amount_mb();

    // the amount of system memory, in gigabytes
    const auto gb = cen::ram::amount_gb();  
  }