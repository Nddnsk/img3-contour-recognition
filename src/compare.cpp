#include "compare.h"
#include <cmath>
#include <algorithm>


// Расстояние между двумя признаками Протасова
// Так называемая Манхэттенская метрика L1(sorry)
double distFeature(const Feature& a, const Feature& b) {
    return std::fabs(a.n1 - b.n1)
         + std::fabs(a.n2 - b.n2)
         + std::abs(a.z - b.z);
}

// Сравниваем признаки двух контуров и 
// Возвращаем число, характеризующее степень различия
double compareContours(
    const std::vector<Feature>& A,
    const std::vector<Feature>& B
) {
    if (A.empty() || B.empty()) return 1e9; // Проверка на наличае признаков 

    int m = static_cast<int>(A.size());
    int n = static_cast<int>(B.size());
// Случай, когда размеры разные
    if (m != n) {
        int k = std::min(m, n);
        double sum = 0.0;
        for (int i = 0; i < k; ++i) sum += distFeature(A[i], B[i]);
        return sum / k;
    }
// Цикл сдвига, ищем лучший момент старта, обеспечивает  
// Инвариантность для массивов одинакового размера
    double best = 1e18;
    for (int shift = 0; shift < n; ++shift) {
        double sum = 0.0;
        for (int i = 0; i < m; ++i) {
            sum += distFeature(A[i], B[(i + shift) % n]);
        }
        best = std::min(best, sum / m);
    }
    return best;
}
