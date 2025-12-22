#include "characteristic.h"
#include "geometry.h"

// Определение функции для поиска характеристических точек 
void findCharacteristicPoints(
    const std::vector<Point>& contour,
    int start,
    int end,
    double eps,
    std::vector<bool>& isChar
) {
    // Базовый случай рекурсии, если между start и end нету точек
    if (end <= start + 1)
        return;

    // Прямая с которой сравнивают
    double baseLen = dist(contour[start], contour[end]);
    // Если точка совпала выходим
    if (baseLen == 0)
        return;

    // Инициализация параметров поиска характеристической точки
    double maxRatio = 0.0;
    int idx = -1;

    // Для каждой точки между start и end смотрим расстояние до прямой
    for (int i = start + 1; i < end; ++i) {
        double d = distancePointToLine(
            contour[i],
            contour[start],
            contour[end]
        );

    //!! Делает алгоритм масштабно инвариантным !!
        double ratio = d / baseLen;

        if (ratio > maxRatio) {
            maxRatio = ratio;
            idx = i;
        }
    }
    // Продолжаем находить точки по дальнейшему участка, если точка была найдена и она больше eps
    // Тоесть если мы считаем весь участок между end и start не просто прямой
    if (maxRatio > eps && idx != -1) {
        isChar[idx] = true;
        findCharacteristicPoints(contour, start, idx, eps, isChar);
        findCharacteristicPoints(contour, idx, end, eps, isChar);
    }
}
