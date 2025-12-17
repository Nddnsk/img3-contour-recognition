#include "geometry.h"
#include <cmath>

double dist(const Point& a, const Point& b) {
    return std::hypot(a.x - b.x, a.y - b.y);
}

double distancePointToLine(const Point& p, const Point& a, const Point& b) {
    double A = b.y - a.y;
    double B = a.x - b.x;
    double C = b.x * a.y - a.x * b.y;
    return std::fabs(A * p.x + B * p.y + C) / std::sqrt(A*A + B*B);
}

Point centroid(const std::vector<Point>& contour) {
    Point c{0, 0};
    for (const auto& p : contour) {
        c.x += p.x;
        c.y += p.y;
    }
    c.x /= contour.size();
    c.y /= contour.size();
    return c;
}

int orientation(const Point& a, const Point& b, const Point& c) {
    double v = (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
    return (v >= 0) ? 1 : -1;
}
