#include <iostream>

int main()
{
    size_t K;
    std::cin >> K;

    if (K % 2 == 0)
    {
        std::cout << -1;
        return 0;
    }

    int64_t cur = 7;
    int idx = 1;

    size_t k = K;
    while (k--)
    {
        if (cur % K == 0)
        {
            std::cout << idx;
            return 0;
        }
        cur *= 10;
        cur += 7;
        cur %= K;

        ++idx;
    }

    std::cout << -1;
}