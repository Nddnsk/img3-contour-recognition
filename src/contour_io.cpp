#include "contour_io.h"
#include <fstream>


// Принимаем файл с координатами и 
// Возвращаем контур в виде точек
std::vector<Point> readContour(const std::string& filename) {
    std::ifstream in(filename);
    // первая строчка файла ввода ожидаемо 
    // будет количеством точек в файле
    int n;
    in >> n;
    std::vector<Point> contour(n);
    for (int i = 0; i < n; ++i) {
        in >> contour[i].x; 
        in >> contour[i].y;
    }
    return contour;
}
