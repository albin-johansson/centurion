RAM
===

The RAM API provides information about the system memory.

General information
-------------------

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Namespace                ``::centurion::ram``
Header                   ``ram.hpp``
Since                    3.0.0
======================  =========================================

Interface
---------

.. doxygennamespace:: centurion::ram
  :outline:
  :members:

Examples
--------

.. code-block:: C++
  :linenos:
  
  #include <centurion_as_ctn.hpp>
  #include <ram.hpp>

  void foo()
  {
    // the amount of system memory, in megabytes
    const auto mb = ctn::ram::amount_mb();

    // the amount of system memory, in gigabytes
    const auto gb = ctn::ram::amount_gb();  
  }