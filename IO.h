#ifndef IO_H
#define IO_H

#include "snake.h"
class Snake;
class Food;

class Terminal
{
  public:
    void clearTerminal();
    void drawSnake(const Snake& snake);
    void enableRawMode();
    void disableRawMode();
    char getKeyboardInput();
    Coordinates getBounds();
    void drawFood(const Food& food);
};

#endif
