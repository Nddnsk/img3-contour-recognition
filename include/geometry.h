#pragma once
#include <vector>
#include "point.h"

double dist(const Point& a, const Point& b);
double distancePointToLine(const Point& p, const Point& a, const Point& b);
Point centroid(const std::vector<Point>& contour);
int orientation(const Point& a, const Point& b, const Point& c);
