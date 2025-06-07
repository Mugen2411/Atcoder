#include <iostream>
#include <vector>

int main()
{
    int N;
    std::cin >> N;
    std::vector<int64_t> mp(N + 1);
    for (int i = 0; i < N; ++i)
    {
        int tmp;
        std::cin >> tmp;
        for (int j = std::min(tmp, N); j > 0; --j)
        {
            ++mp[j];
        }
    }
    int ans = 0;
    for (int i = 0; i <= N; ++i)
    {
        if (mp[i] >= i)
        {
            ans = std::max(ans, i);
        }
    }
    std::cout << ans;
    return 0;
}