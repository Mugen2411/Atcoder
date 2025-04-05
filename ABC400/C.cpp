#include <iostream>
#include <cmath>

int main()
{
    int64_t N;
    std::cin >> N;
    int64_t base = 2;
    int64_t ans = 0;
    int64_t logN = std::log2l(N);
    for (int64_t a = 1; a < 3; ++a)
    {
        int64_t t = N / base;
        int64_t sqt = std::sqrt((long double)t);

        ans += sqt;

        base *= 2;
        if (base > N)
        {
            break;
        }
    }
    std::cout << ans;
    return 0;
}