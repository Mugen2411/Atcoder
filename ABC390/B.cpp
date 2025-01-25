#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    size_t N;
    std::cin >> N;
    std::vector<int64_t> A(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A[i];
    }
    if (N == 2)
    {
        std::cout << "Yes";
        return 0;
    }
    for (int i = 1; i < N - 1; ++i)
    {
        long double ratio1 = (long double)A[i] / (long double)A[i - 1];
        long double ratio2 = (long double)A[i + 1] / (long double)A[i];
        if (std::abs(ratio1 - ratio2) > 0.0000000000000000000001l)
        {
            std::cout << "No";
            return 0;
        }
    }
    std::cout << "Yes";
    return 0;
}