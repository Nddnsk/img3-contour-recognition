#pragma once
#include <vector>
#include "point.h"

void findCharacteristicPoints(
    const std::vector<Point>& contour,
    int start,
    int end,
    double eps,
    std::vector<bool>& isChar
);
