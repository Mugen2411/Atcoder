#include <iostream>

int main()
{
    size_t fact[26 * 1000 + 1];
    fact[0] = 1;
    constexpr size_t MOD = 998244353;
    for (int i = 1; i <= 26 * 1000; ++i)
    {
        fact[i] = fact[i - 1] * i;
        fact[i] %= MOD;
    }

    return 0;
}