#include "point.h"

#include <cmath>

Point::Point() : x(0), y(0) {
}

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  return std::sqrt(std::pow(x - p.getX(), 2) + std::pow(y - p.getY(), 2));
}
