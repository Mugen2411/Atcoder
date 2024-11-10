#include <iostream>

int64_t dp[110][110000] = {0};
const int MAX_V = 110000;

int main()
{
    size_t N, W;
    std::cin >> N >> W;
    int64_t w[110] = {0};
    int64_t v[110] = {0};
    for (int i = 0; i < N; ++i)
    {
        std::cin >> w[i] >> v[i];
    }

    for (int i = 0; i <= N; ++i)
    {
        for (int j = 0; j < MAX_V; ++j)
        {
            dp[i][j] = 1LL << 60;
        }
    }

    dp[0][0] = 0;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < MAX_V; ++j)
        {
            dp[i + 1][j] = std::min(dp[i + 1][j], dp[i][j]);
            if (j >= v[i])
            {
                dp[i + 1][j] = std::min(dp[i + 1][j], dp[i][j - v[i]] + w[i]);
            }
        }
    }
    int64_t ans = 0;
    for (int j = 0; j < MAX_V; ++j)
    {
        if (dp[N][j] <= W)
        {
            ans = j;
        }
    }
    std::cout << ans;
    return 0;
}