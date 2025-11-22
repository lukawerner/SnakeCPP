#ifndef FOOD_H
#define FOOD_H
#include "snake.h" 
#include <vector>
class Food
{
  public:
    void spawn(Coordinates bounds);
    bool alreadyExists(const Coordinates& newFood) const;
    bool foundBySnake(Snake& snake) const;
    const std::vector<Coordinates>& getFood() const;
    void despawn(std::vector<Coordinates>::const_iterator iter);
  private:
    std::vector<Coordinates> m_foods;
};
#endif

