#include <iostream>
#include <vector>

#define MOD 998244353

int main()
{
    size_t N, M;
    std::cin >> N >> M;
    size_t ans = 0;

    for (int i = 0; i < 60; ++i)
    {
        if (!(M & (1LL << i)))
        {
            continue;
        }

        size_t m = (N + 1) >> (i + 1);

        ans += m * (1LL << (i));
        ans %= MOD;

        if (m % 2)
        {
            continue;
        }
        size_t n = (N + 1) % (1 << i);

        ans += n % (1LL << i);
        ans %= MOD;
    }

    std::cout << ans;
}