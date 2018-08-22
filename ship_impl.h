#include <cinttypes>
#include <istream>
#include <utility>

template<typename T>
decltype(auto) getX(T&& value)
{
  return (std::forward<T>(value).first);
}

template<typename T>
decltype(auto) getY(T&& value)
{
  return (std::forward<T>(value).second);
}

using Point = std::pair<std::int64_t, std::int64_t>;
using Vector = std::pair<std::int64_t, std::int64_t>;

std::istream& operator>>(std::istream& strm, Point& p);

struct Ship
{
  explicit Ship(const Point& startP1, const Point& startP2);

  static int nav(int dPrev, int dCurrent, int dLocal);
  static int pav(int dPrev, int dCurrent, int dLocal);

  void move(const Point& p);
  bool getResult() const;

private:
  
  Vector base;
  Point b1;
  Point b2;
  std::int64_t counter;
  std::int64_t uncertainity;
  int prevDirection;
};
