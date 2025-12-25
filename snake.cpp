#include "snake.h"
#include "food.h"
#include <algorithm>
#include <iostream>
#include <vector>

#define SNAKE_INIT_LEN 3
#define SNAKE_INIT_MAX_LEN 10

void Snake::changePosition(Coordinates bounds, bool grows) {
  if (!grows)
    m_body.erase(m_body.begin());

  Coordinates head = m_body.back();
  switch (m_direction) {
  case (Direction::UP):
    head.m_y--;
    break;
  case (Direction::RIGHT):
    head.m_x++;
    break;
  case (Direction::DOWN):
    head.m_y++;
    break;
  case (Direction::LEFT):
    head.m_x--;
    break;
  }

  if (head.m_y > bounds.m_y)
    head.m_y = 0;
  if (head.m_y < 0)
    head.m_y = bounds.m_y;

  if (head.m_x > bounds.m_x)
    head.m_x = 0;
  if (head.m_x < 0)
    head.m_x = bounds.m_x;

  m_body.push_back(head);
}

const std::vector<Coordinates> &Snake::getPosition() const { return m_body; }

void Snake::init() {
  if (SNAKE_INIT_LEN > SNAKE_INIT_MAX_LEN) {
    std::cout << "failed to initialized snake. Initial length is too big.";
    return;
  }

  m_body.resize(SNAKE_INIT_LEN);

  for (int i = 0; i < SNAKE_INIT_LEN; i++) {
    Coordinates &body_part = m_body.at(i);
    body_part.m_x = i;
    body_part.m_y = 0;
  }
}

void Snake::updateDirection(char input) {
  switch (input) {
  case 'w':
    m_direction = Direction::UP;
    break;
  case 'a':
    m_direction = Direction::LEFT;
    break;
  case 's':
    m_direction = Direction::DOWN;
    break;
  case 'd':
    m_direction = Direction::RIGHT;
    break;
  default:
    break;
  }
}

void Snake::eats(Food &f) {
  const Coordinates &head = getPosition().back();
  const std::vector<Coordinates> &foods = f.getFood();
  const auto iter = std::find(foods.begin(), foods.end(), head);
  f.despawn(iter);
}

bool Snake::collision() {
  const Coordinates &head = getPosition().back();
  return std::find(m_body.begin(), std::prev(m_body.end()), head) !=
         std::prev(m_body.end());
}
