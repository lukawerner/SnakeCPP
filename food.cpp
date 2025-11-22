#include "food.h"
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "snake.h"


void Food::spawn(Coordinates bounds)
{
  if (!(m_foods.empty())) return;

  int num_food = rand() % 8;
  if (num_food <= 0) num_food = 5;

  for (int i = 0; i<num_food; i++)
  {
    Coordinates c;
    do
    {   
      c.m_x = rand() % bounds.m_x;
      c.m_y = rand() % bounds.m_y;   
    }
    while (alreadyExists(c));
    m_foods.push_back(c);
  }
}

bool Food::alreadyExists(const Coordinates& newFood) const
{
  return std::find(m_foods.begin(), m_foods.end(), newFood) != m_foods.end();
}

bool Food::foundBySnake(Snake& snake) const
{
  return m_foods.end() != std::find(m_foods.begin(), m_foods.end(), snake.getPosition().back());
}
    
const std::vector<Coordinates>& Food::getFood() const
{
  return m_foods;
}

void Food::despawn(std::vector<Coordinates>::const_iterator iter)
{
  m_foods.erase(iter);
}
