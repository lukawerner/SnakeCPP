#ifndef SNAKE_H
#define SNAKE_H
#include <vector>
#include <iostream>
class Food;

enum class Direction
{
  UP,
  RIGHT,
  DOWN,
  LEFT,
};
struct Coordinates
{
  int m_x;
  int m_y;

  bool operator==(const Coordinates& coord) const
  {
    return (m_x == coord.m_x && m_y == coord.m_y); 
  }
};

class Snake
{
  public:

    void changePosition(Coordinates bounds, bool grows);
    const std::vector<Coordinates>& getPosition() const;
    void init();
    void updateDirection(char input); 
    bool collision();  
    void eats(Food& f);

  private:
    std::vector<Coordinates> m_body;
    Direction m_direction {Direction::DOWN}; 
};

#endif
