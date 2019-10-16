#include <cstdio>
#include <cstdlib>

class Point {
 private:
  double x, y;

 public:
  Point();
  void move(double dx, double dy);
  double distanceFrom(const Point & p);
  double getX() const { return x; }
  double getY() const { return y; }
};
