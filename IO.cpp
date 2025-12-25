#include "IO.h"

#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include <iostream>

#include "food.h"
#include "snake.h"

void Terminal::clearTerminal() { std::cout << "\x1b[2J\x1b[H"; }

void Terminal::drawSnake(const Snake &snake) {
  const std::vector<Coordinates> &body = snake.getPosition();
  for (const Coordinates &pixel : body) {
    std::cout << "\033[" << pixel.m_y << ";" << pixel.m_x << "H#";
  }
}

void Terminal::enableRawMode() {
  termios t;
  tcgetattr(STDIN_FILENO, &t);

  t.c_lflag &= ~(ECHO | ICANON); // Disable character echo and canonical mode
                                 // (line-based editing capabilities)

  tcsetattr(STDIN_FILENO, TCSANOW, &t);
  fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK); // set STDIN non-blocking
}
void Terminal::disableRawMode() {
  termios t;
  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag |= (ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
  int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
  flags &= ~O_NONBLOCK;
  fcntl(STDIN_FILENO, F_SETFL, flags);
}

char Terminal::getKeyboardInput() { return getchar(); }

Coordinates Terminal::getBounds() {
  winsize w;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
    std::perror("ioctl");
  }
  Coordinates c{w.ws_col - 1, w.ws_row - 1};
  return c;
}

void Terminal::drawFood(const Food &food) {
  const std::vector<Coordinates> &food_array = food.getFood();
  for (const Coordinates &f : food_array) {
    std::cout << "\033[" << f.m_y << ";" << f.m_x << "H*";
  }
}
