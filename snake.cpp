#include <vector>
#include <iostream>
#include "snake.h"
#include "food.h"
#include <algorithm>

#define SNAKE_INIT_LEN 3
#define SNAKE_INIT_MAX_LEN 10


void Snake::changePosition(Coordinates bounds, bool grows)
{
  if (!grows) m_body.erase(m_body.begin());

  Coordinates c = m_body.back();
  switch(m_direction)
  {
    case(Direction::UP):
      c.m_y--;
      break;
    case(Direction::RIGHT):
      c.m_x ++;
      break;
    case(Direction::DOWN):
      c.m_y++;
      break;
    case(Direction::LEFT):
      c.m_x--;
      break;
  }

  if (c.m_y > bounds.m_y) c.m_y = 0;
  if (c.m_y < 0) c.m_y = bounds.m_y;

  if (c.m_x > bounds.m_x) c.m_x = 0;
  if (c.m_x < 0) c.m_x = bounds.m_x;

  m_body.push_back(c);
}

const std::vector<Coordinates>& Snake::getPosition() const
{
  return m_body;
}

void Snake::init()
{
  if (SNAKE_INIT_LEN > SNAKE_INIT_MAX_LEN)
  {
    std::cout << "failed to initialized snake. Initial length is too big.";
    return;
  }

  m_body.resize(SNAKE_INIT_LEN);

  for (int i = 0; i < SNAKE_INIT_LEN; i++)
  {
    Coordinates& c = m_body.at(i);
    c.m_x = i;
    c.m_y = 0;
  }
  
}

void Snake::updateDirection(char input)
{
  switch(input)
  {
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

void Snake::eats(Food& f)
{
  const Coordinates& head = getPosition().back();
  const std::vector<Coordinates>& foods = f.getFood();
  const auto iter = std::find(foods.begin(), foods.end(), head);
  f.despawn(iter);
}

bool Snake::collision()
{
  const Coordinates& head = getPosition().back();
  return std::find(m_body.begin(), std::prev(m_body.end()), head) != std::prev(m_body.end());
}

