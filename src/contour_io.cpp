#include "contour_io.h"
#include <fstream>

std::vector<Point> readContour(const std::string& filename) {
    std::ifstream in(filename);
    int n;
    in >> n;
    std::vector<Point> contour(n);
    for (int i = 0; i < n; ++i) {
        in >> contour[i].x >> contour[i].y;
    }
    return contour;
}
