#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>

size_t prime_divide(size_t n)
{
    for (int i = 2; i * i <= n; ++i)
    {
        while (n % (i * i) == 0)
        {
            n /= i * i;
        }
    }
    return n;
}

int main()
{
    size_t N, tmp;
    std::cin >> N;
    std::unordered_map<size_t, size_t> A;
    size_t ans = 0;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> tmp;
        size_t essense = prime_divide(tmp);

        ans += A[essense]++;
    }

    std::cout << ans + A[0] * (N - A[0]);
    return 0;
}