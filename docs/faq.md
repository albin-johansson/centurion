# FAQ

This document provides answers to some of the common questions and thoughts that you might have about the Centurion library.

- [FAQ](#faq)
  - [What versions of C++ can I use Centurion with?](#what-versions-of-c-can-i-use-centurion-with)
  - [What is Centurion meant to be used for?](#what-is-centurion-meant-to-be-used-for)
  - [What am I allowed to use Centurion for?](#what-am-i-allowed-to-use-centurion-for)
  - [Why is *X/Y/Z* from SDL2 not covered in Centurion?](#why-is-xyz-from-sdl2-not-covered-in-centurion)
  - [Can Centurion be used for GUI programming?](#can-centurion-be-used-for-gui-programming)
  - [Can I contribute to Centurion?](#can-i-contribute-to-centurion)

## What versions of C++ can I use Centurion with?

Centurion is compatible with C++11, C++14 and C++17 (and will be usable with C++20).

## What is Centurion meant to be used for?

The library is mainly designed to be used for 2D games, similarily to SDL2. However, you could create 3D games with Centurion if you want to write your own renderer (e.g. with OpenGL). Basically, Centurion can be used for anything that SDL2 is used for.

## What am I allowed to use Centurion for?

Pretty much anything as long as the license is kept with the source code. Centurion uses the MIT license.

## Why is *X/Y/Z* from SDL2 not covered in Centurion?

The most likely reason is that it would be *redundant*. The C++ standard library is huge and provides nicer abstractions than what SDL2 can provide in C. However, if you feel like this isn't the case, feel free to request a feature!

## Can Centurion be used for GUI programming?

Neither SDL2 nor Centurion are GUI-libraries, so there are no built-in GUI components such as buttons or toolbars. If you're looking for a good GUI library then you'd probably want to use something like Qt.

## Can I contribute to Centurion?

Yes. Anyone can make pull requests and suggest improvements, new features and/or bug fixes.
