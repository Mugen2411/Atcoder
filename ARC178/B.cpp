#include <iostream>
#include <array>
#include <cmath>

int main()
{
    size_t T;
    std::array<size_t, 3> A;
    std::cin >> A[0] >> A[1] >> A[2];
    size_t maxI = std::pow(10, A[0]);
    size_t maxJ = std::pow(10, A[1]);
    size_t maxK = std::pow(10, A[2]);
    size_t cnt = 0;
    size_t B = 765;
    for (int i = 1; B != 0; ++i)
    {
        ++cnt;
        B -= i;
    }
    std::cout << cnt;
    return 0;
}