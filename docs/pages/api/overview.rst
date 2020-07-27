Overview
==========
This page provides an overview of the entire Centurion API, arranged by category.

Windows
-------
The window API is perhaps the most important in the library. Every game needs a window! There are
two different window classes meant for different use cases. In most cases, you want to use the
``window`` class, which represents an owning window. For the cases where you don't want the
window to claim ownership of the associated ``SDL_Window*``, you can use the ``window_view`` class.

* :doc:`Window </pages/api/window>` | Represents an owning window.
* :doc:`Window view </pages/api/window_view>` | Represents a non-owning window.

Graphics
--------
Graphics are of course also very important in every game! The primary representation for images
is the ``texture`` class, which is hardware-accelerated! The rendering API is simple and easy to
use, yet powerful.

* :doc:`Renderer </pages/api/renderer>` | Provides the rendering API, along with several extra conveniences.
* :doc:`Renderer view </pages/api/renderer_view>` | A non-owning wrapper around an ``SDL_Renderer*``.
* ``texture.hpp`` | ``texture``.
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
