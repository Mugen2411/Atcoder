#include <iostream>
#include <vector>

int main()
{
    int64_t min = 0;
    int64_t max = 0;
    size_t N;
    std::cin >> N;
    std::vector<int64_t> L(N);
    std::vector<int64_t> R(N);

    int64_t tmpL, tmpR;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> tmpL >> tmpR;
        L[i] = tmpL;
        R[i] = tmpR;
        min += tmpL;
        max += tmpR - tmpL;
    }

    min *= -1;
    if (min >= 0 && min <= max)
    {
        std::cout << "Yes" << std::endl;
    }
    else
    {
        std::cout << "No" << std::endl;
        return 0;
    }

    for (int i = 0; i < N; ++i)
    {
        int64_t a = std::min(min, R[i] - L[i]);
        std::cout << L[i] + a << " ";
        min -= a;
    }

    return 0;
}