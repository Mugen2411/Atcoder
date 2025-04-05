#include <iostream>

int main()
{
    int N, M;
    std::cin >> N >> M;
    int64_t ans = 0;
    for (int i = M; i >= 0; --i)
    {
        int64_t tmp = 1;
        for (int j = 0; j < i; ++j)
        {
            tmp *= N;
        }
        ans += tmp;
        if (ans > 1000000000)
        {
            std::cout << "inf";
            return 0;
        }
    }
    std::cout << ans;
    return 0;
}