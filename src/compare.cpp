#include "compare.h"
#include <cmath>

double compareContours(
    const std::vector<Feature>& A,
    const std::vector<Feature>& B
) {
    int m = std::min(A.size(), B.size());
    double sum = 0;

    for (int i = 0; i < m; ++i) {
        sum += std::fabs(A[i].n1 - B[i].n1)
             + std::fabs(A[i].n2 - B[i].n2)
             + std::abs(A[i].z - B[i].z);
    }

    return sum / m;
}
