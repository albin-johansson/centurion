FAQ
===

This document provides answers to some of the common questions and thoughts
that you might have about the Centurion library.

What versions of C++ can I use Centurion with?
----------------------------------------------
Centurion 5.0.0 and later targets C++17. However, earlier versions (the
latest being version 4.3.0) support C++11, C++14 and C++17.

What is Centurion meant to be used for?
---------------------------------------
Since Centurion is a wrapper for SDL2. You can basically use it for
anything that SDL2 is used for.

What am I allowed to do with Centurion?
---------------------------------------
Pretty much anything as long as the license is kept with the source code.
Centurion uses the MIT license.

Why is X from SDL2 not covered in Centurion?
--------------------------------------------
The most likely reason is that it would be *redundant*. The C++ standard
library is huge and provides nicer abstractions than what SDL2 can provide in
C. However, if you feel like this isn't the case, feel free to request a
feature!

Can Centurion be used for GUI programming?
------------------------------------------
Neither SDL2 nor Centurion are GUI-libraries, so there are no built-in GUI
components such as buttons or toolbars. If you're looking for a good GUI
library then you'd probably want to use something like Qt.

Can I contribute to Centurion?
------------------------------
Yes. Anyone can make pull requests and suggest improvements, new features
and/or bug fixes.

