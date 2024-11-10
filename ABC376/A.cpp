#include <iostream>

int main()
{
    int64_t N, C;
    std::cin >> N >> C;
    int64_t T;
    std::cin >> T;
    int64_t prev = T;
    int64_t ans = 1;
    while (--N)
    {
        std::cin >> T;

        if (T - prev >= C)
        {
            prev = T;
            ++ans;
        }
    }
    std::cout << ans;
    return 0;
}