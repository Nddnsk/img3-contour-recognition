#include "contour_features.h"
#include "characteristic.h"
#include "geometry.h"

std::vector<Feature> extractFeatures(
    const std::vector<Point>& contour,
    double eps
) {
    int n = contour.size();
    std::vector<bool> isChar(n, false);

    isChar[0] = true;
    isChar[n - 1] = true;

    findCharacteristicPoints(contour, 0, n - 1, eps, isChar);

    // Масштаб — средняя длина сегмента контура
    double scale = 0.0;
    for (int i = 1; i < n; ++i)
        scale += dist(contour[i - 1], contour[i]);
    scale /= (n - 1);

    Point c = centroid(contour);

    std::vector<Feature> features;

    for (int i = 0; i < n; ++i) {
        if (!isChar[i])
            continue;

        Feature f;
        f.n1 = dist(contour[i], c) / scale;

        if (i + 1 < n)
            f.n2 = dist(contour[i], contour[i + 1]) / scale;
        else
            f.n2 = 0.0;

        f.z = orientation(
            c,
            contour[i],
            contour[(i + 1) % n]
        );

        features.push_back(f);
    }

    return features;
}
