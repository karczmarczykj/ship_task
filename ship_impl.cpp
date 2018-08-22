#include "ship_impl.h"

#include <cstdint>
#include <cinttypes>

Vector createVector(const Point& p1, const Point& p2)
{
  auto x = getX(p2) - getX(p1);
  auto y = getY(p2) - getY(p1);

  return Vector(x, y);
}

int vectorProduct(const Vector& v1, const Vector& v2)
{
  auto product = getX(v2)*getY(v1) - getX(v1)*getY(v2);

  if(product > 0)
    return 1;

  if(product < 0) 
    return -1;

  return 0;
}

std::istream& operator>>(std::istream& strm, Point& p)
{
  strm >> getX(p) >> getY(p);
  return strm;
}

Ship::Ship(const Point& startP1, const Point& startP2) 
  : base(createVector(startP1, startP2)), b1(startP1), b2(startP2), 
    counter(0), uncertainity(0), prevDirection(0) 
{
}

int Ship::nav(int dPrev, int dCurrent, int dLocal)
{
  if (dPrev != 0 && dPrev == dCurrent)
    return 0;

  if (dPrev * dCurrent == -1)
    return 2 * dLocal;

  return dLocal;
}

int Ship::pav(int dPrev, int dCurrent, int dLocal)
{
  if (dPrev == 0 && dCurrent == 0 && dLocal == 0)
    return 1;

  if (dPrev * dCurrent == -1 && dLocal == 0)
    return 2;

  return 0;
}

void Ship::move(const Point& p)
{
  if ( p == b2 )
    return;

  auto prevVector = createVector(b1, b2);
  auto currVector = createVector(b2, p);
  auto previousDirection = prevDirection;
  auto localDirection = vectorProduct(prevVector, currVector);
  auto currentDirection = vectorProduct(base, currVector);
  prevDirection = currentDirection;
  
  b1 = b2;
  b2 = p;

  if (previousDirection == 0 && currentDirection == 0 && localDirection == 0)
  {
    if (getX(prevVector)*getX(currVector) != -1 &&
        getY(prevVector)*getY(currVector) != -1)
      return;
  } 

  auto un = pav(previousDirection, currentDirection, localDirection);

  if ( un != 0 )
  {
    uncertainity += un;
    return;
  }
   
  counter += nav(previousDirection, currentDirection, localDirection);
}

bool Ship::getResult() const
{
  return (counter - uncertainity) > 0;
}
