#pragma once
#include <vector>
#include "point.h"

std::vector<Feature> extractFeatures(const std::vector<Point>& contour,double eps);
