#include <iostream>
#include <vector>

#include "ship_impl.h"

int main()
{
  std::size_t n;
  std::cin>>n;
  std::vector<Point> points;
  for (std::size_t i = 0 ; i < n/2 ; ++i)
  {
    Point p;
    std::cin >> p;
    points.push_back(p);
  }
  Ship ship(points[0], points[1]);

  for (std::size_t i = 2 ; i < points.size() ; ++i)
    ship.move(points[i]);

  std::cout<<std::boolalpha<<ship.getResult()<<std::endl;

  return 0;
}
