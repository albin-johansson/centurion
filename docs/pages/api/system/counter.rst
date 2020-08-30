Counter
=======

The counter API provides utilities related to the system high-performance counter and the time 
that has passed since the library was initialized. This is useful for profiling and implementing
game loops, etc. This API uses the ``std::chrono`` duration types behind-the-scenes, which
makes handling time values type-safe, contrary to the raw SDL timing functions.

General information
-------------------

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Namespace                ``::centurion::counter``
Header                   ``counter.hpp``
Since                    5.0.0
======================  =========================================

Interface
---------

.. doxygennamespace:: centurion::counter
  :outline:
  :members:

Examples
--------

.. code-block:: c++
  
  #include <cen.hpp>
  #include <counter.hpp>

  void foo()
  {
    // query the high-performance counter
    const auto now = cen::counter::now();

    // query the high-performance counter in seconds
    const auto secs = cen::counter::now_sec<double>();

    // obtains the amount of milliseconds that have passed since SDL was initialized
    const auto ticks = cen::counter::ticks();

    // obtains the frequency of the high-performance counter
    const auto freq = cen::counter::high_res_freq();
  }