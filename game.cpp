#include "IO.h"
#include "food.h"
#include "snake.h"
#include <iostream>
#include <unistd.h>

int main() {
  Terminal t;
  Snake s;
  s.init();
  t.enableRawMode();
  Food f;
  bool grows = false;
  std::cout << "Initialization complete\n";

  while (1) {
    char c = t.getKeyboardInput();
    if (c == '\x1B')
      break; // esc char

    Coordinates bounds = t.getBounds();

    if (f.foundBySnake(s)) {
      grows = true;
      s.eats(f);
    }
    s.updateDirection(c);
    s.changePosition(bounds, grows);
    t.clearTerminal();
    t.drawSnake(s);

    f.spawn(bounds);
    t.drawFood(f);
    grows = false;
    if (s.collision())
      break;

    usleep(100000);
  }
  t.disableRawMode();
  t.clearTerminal();

  std::cout << "Game Over\n";

  return 0;
}
