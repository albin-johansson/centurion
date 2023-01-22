#include <centurion.hpp>

int main(int, char**)
{
  const cen::sdl sdl;

  cen::message_box mb;
  mb.set_title("This is a message box");
  mb.set_message("May I please have your attention?");

  mb.set_type(cen::message_box_type::warning);
  mb.set_button_order(cen::message_box_button_order::left_to_right);

  const cen::message_box::button_id yes = 1;
  const cen::message_box::button_id no = 2;
  mb.add_button(yes, "Yes");
  mb.add_button(no, "No");

  const auto button = mb.show();
  if (button.has_value()) {
    cen::log_info("Pressed message box button %i!", *button);
  }

  if (button == yes) {
    // If all you need is a simple message box, you can use the static show functions.
    cen::message_box::show("This is a simple message box",
                           "I was opened with a single line of code!",
                           cen::message_box_type::information);
  }

  return 0;
}