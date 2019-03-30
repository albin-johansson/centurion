#pragma once

namespace centurion {
namespace events {

class KeyListener {
 protected:
  KeyListener() = default;

 public:
  virtual ~KeyListener() = default;

  virtual void KeyPressed() = 0;

  virtual void KeyReleased() = 0;
};

}  // namespace events
}  // namespace centurion