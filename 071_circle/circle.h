#include <cstdio>
#include <cstdlib>

#include "point.h"

class Circle {
 private:
  Point center;
  const double radius;

 public:
  Circle(Point p, double r);
  void move(double dx, double dy);
  Point getCenter() const { return center; }
  double getR() const { return radius; }
  double intersectionArea(const Circle & otherCircle);
};
