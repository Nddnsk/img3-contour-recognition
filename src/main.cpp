#include <iostream>
#include "contour_io.h"
#include "contour_features.h"
#include "compare.h"

int main() {
    auto c1 = readContour("data/contour1.txt");
    auto c2 = readContour("data/contour2.txt");

    double eps = 0.5;

    auto f1 = extractFeatures(c1, eps);
    auto f2 = extractFeatures(c2, eps);

    double score = compareContours(f1, f2);

    std::cout << "Similarity score: " << score << std::endl;
    return 0;
}
