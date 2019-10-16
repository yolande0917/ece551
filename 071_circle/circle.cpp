#include "circle.h"

#include <algorithm>
#include <cmath>

Circle::Circle(Point p, double r) : center(p), radius(r) {
}

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double d = center.distanceFrom(otherCircle.getCenter());
  double r = otherCircle.getR();
  if (d >= r + radius || r == 0 || radius == 0) {
    return 0;
  }
  if (d == 0) {
    double smallr = std::min(r, radius);
    return M_PI * smallr * smallr;
  }
  if (d + r <= radius) {
    return M_PI * r * r;
  }
  if (d + radius <= r) {
    return M_PI * radius * radius;
  }

  double d1 = (radius * radius - r * r + d * d) / (2 * d);
  double d2 = d - d1;
  double a = radius * radius * std::acos(d1 / radius) -
             d1 * std::sqrt(radius * radius - d1 * d1) + r * r * std::acos(d2 / r) -
             d2 * std::sqrt(r * r - d2 * d2);
  return a;
}
