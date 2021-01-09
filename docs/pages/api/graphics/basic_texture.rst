basic_texture
=============

Represents a hardware-accelerated image, which is intended to be rendered 
using ``basic_renderer``. There are both owning and non-owning versions 
of this class, see ``texture`` and ``texture_handle``, respectively.

General information
-------------------

======================  ==========================================
  Property               Value
----------------------  ------------------------------------------
Default constructible    No
Copyable                 Only ``texture_handle``
Movable                  Both ``texture`` and ``texture_handle``
Implicit conversions     None
Explicit conversions     ``SDL_Texture*``, ``const SDL_Texture*``
Overloaded operators     ``<<``
Printable                Yes
Namespace                ``::cen``
Header                   ``texture.hpp``
Since                    3.0.0
======================  ==========================================

Interface
---------

.. doxygenclass:: cen::basic_texture
  :members:
  :undoc-members:
  :outline:
  :no-link:
