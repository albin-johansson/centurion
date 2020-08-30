Battery
=======

The battery API can be used to obtain information about the system battery, if there 
is one available. The battery API heavily utilizes ``std::optional`` as the return 
type for battery queries for the cases where the system isn't running on a battery. Which 
means that it's safe to call battery functions no matter the system.

General information
-------------------

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Namespace                ``::centurion::battery``
Header                   ``battery.hpp``
Since                    3.0.0
======================  =========================================

Interface
---------

.. doxygennamespace:: centurion::battery
  :outline:
  :members:

Examples
--------

.. code-block:: c++
  
  #include <cen.hpp>
  #include <battery.hpp>

  void foo()
  {
    // Check if the system is running on a battery
    const auto exists = cen::battery::exists();

    if (const auto percentage = cen::battery::percentage(); percentage) {
      // obtained the battery percentage
    }

    if (const auto minutes = cen::battery::minutes_left(); minutes) {
      // obtained the minutes of battery life left
    }

    if (const auto seconds = cen::battery::seconds_left(); seconds) {
      // obtained the seconds of battery life left
    }

    // query detailed status of battery
    switch (cen::battery::state()) {
      case cen::battery::power_state::unknown:
        // unknown power state
        break;
      case cen::battery::power_state::on_battery:
        // running on battery
        break;
      case cen::battery::power_state::no_battery:
        // no available battery
        break;
      case cen::battery::power_state::charging:
        // currently charging
        break;
      case cen::battery::power_state::charged: 
        // battery is charged
        break;
    }
  }