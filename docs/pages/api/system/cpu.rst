CPU
===

The CPU API just wraps the SDL functions behind a nicer interface. It provides information
about the system processor such as L1-cache size, the amount of cores, endianess and whether 
or not the processor supports certain instruction sets, etc.

General information
-------------------

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Namespace                ``::cen::cpu``
Since                    3.0.0
======================  =========================================

Interface
---------

.. doxygennamespace:: cen::cpu
  :outline:
  :members:

Examples
--------

.. code-block:: c++
  
  #include <cpu.hpp>

  void foo()
  {
    if constexpr (cen::cpu::is_little_endian()) {
      // the CPU is little endian
    } else if constexpr (cen::cpu::is_big_endian()) {
      // the CPU is big endian
    }

    // obtains the amount of cores in the CPU
    const auto nCores = cen::cpu::cores();

    // obtains the L1-cache line size
    const auto cache = cen::cpu::cache_line_size();

    // indicates whether or not the CPU has the RDTSC instruction
    if (cen::cpu::has_rdtsc()) {
      // ...
    }
  }