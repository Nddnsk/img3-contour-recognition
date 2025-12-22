#include "contour_features.h"
#include "characteristic.h"
#include "geometry.h"

#include <vector>
#include <cmath>

// Функция проверки последняя точка совпадает с первой
static bool isClosedContour(const std::vector<Point>& c) {
    if (c.size() < 2) return false;
    return dist(c.front(), c.back()) < 1e-12;
}

// Сама функция по созданию массива характеристик характеристических))) точек
std::vector<Feature> extractFeatures(
    const std::vector<Point>& contourIn,
    double eps
) {
    if (contourIn.size() < 4) return {};

    // Если контур замкнут и последняя точка = первая, уберём дубль
    std::vector<Point> contour = contourIn;
    if (isClosedContour(contour)) {
        contour.pop_back();
    }

    int n = (int)contour.size();
    if (n < 4) return {};

    // Находим характерные точки (линеаризация)
    std::vector<bool> isChar(n, false);
    isChar[0] = true;
    isChar[n - 1] = true;

    findCharacteristicPoints(contour, 0, n - 1, eps, isChar);

    // Собираем их в массив по порядку
    std::vector<Point> P;
    P.reserve(n);
    for (int i = 0; i < n; ++i) {
        if (isChar[i]) P.push_back(contour[i]);
    }

    int m = (int)P.size();
    if (m < 4) return {}; // Проверка того, что точек хватает

    // Читаем признаки Протасова для ОТРЕЗКОВ между характерными точками
    std::vector<Feature> features;
    features.reserve(m - 3);

    //Начинаем с точки P[1], просто потомучто так удобнее считать
    for (int k = 1; k <= m - 3; ++k) {
        // Текущий отрезок: P[k] -> P[k+1]
        const Point& A = P[k];
        const Point& B = P[k + 1];

        double lenAB = dist(A, B);

        // Точки соседи нашего отрезка
        const Point& L = P[k - 1];
        const Point& R = P[k + 2];


        // "Не-контурные" стороны (диагонали треугольников):
        // слева: L - B (это НЕ отрезок контура)
        // справа: A - R (это НЕ отрезок контура)
        double diagLeft  = dist(L, B);
        double diagRight = dist(A, R);

        if (diagLeft < 1e-12 || diagRight < 1e-12) continue;

        Feature f;
        // N1 и N2 — отношения длины текущего отрезка к длинам "диагоналей"
        f.n1 = lenAB / diagLeft;
        f.n2 = lenAB / diagRight;

        // Z: +1 если соседние отрезки "с одной стороны" от AB.
        // Это эквивалентно: точки L и R лежат по одну сторону прямой AB.
        int s1 = orientation(A, B, L); // знак для L относительно AB
        int s2 = orientation(A, B, R); // знак для R относительно AB
        f.z = (s1 == s2) ? 1 : -1;

        features.push_back(f);
    }

    return features;
}
