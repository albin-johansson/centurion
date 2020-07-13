Overview
==========
This page provides an overview of the entire Centurion API, arranged by category.

Windows
-------
The window API is perhaps the most important in the library. Every game needs a window! There are
two different window classes meant for different use cases. In most cases, you want to use the
``window`` class, which represents an owning window. For the cases where you don't want the
window to claim ownership of the associated ``SDL_Window*``, you can use the ``window_view`` class.

* :doc:`Window documentation </pages/window>`
* ``window_view``

Graphics
---------
* ``graphics.hpp`` | ``basic_renderer``, ``renderer_view``, ``texture``.
* ``surface.hpp`` | ``surface``
* ``color.hpp`` | ``color``
* ``colors.hpp``
* ``font.hpp`` | ``font``
* ``cursor``

Events
------
* ``Event`` class
* Other miscellaneous events

Input
-----
* ``mouse_state``
* ``key_state``
* ``scan_code``
* ``key_code``
* ``joystick``
* Game controllers
* Touch

Geometry
--------
* ``rect``
* ``point``
* ``area``

Audio
-----
* ``SoundEffect``
* ``Music``

Logging
-------
* ``log.hpp``

Files
-----
* ``paths.hpp``

System
------
* ``counter.hpp``
* ``platform.hpp``
* ``ram.hpp``
* ``cpu.hpp``
* ``screen.hpp``
* ``battery.hpp``
