#include <iostream>
#include <string>
#include <vector>

#define MOD 1000000007

int main()
{
    size_t H, W;
    std::cin >> H >> W;
    std::vector<std::string> A(H);
    std::vector<std::vector<int64_t>> dp(H);
    for (int y = 0; y < H; ++y)
    {
        std::cin >> A[y];
        dp[y].resize(W, -1);
    }

    auto dfs = [&](auto self, int64_t x, int64_t y) -> int64_t
    {
        if (dp[y][x] != -1)
        {
            return dp[y][x];
        }

        if (A[y][x] == '#')
        {
            dp[y][x] = 0;
            return 0;
        }
        int res = 0;
        if (y > 0)
        {
            res += self(self, x, y - 1);
            res %= MOD;
        }
        if (x > 0)
        {
            res += self(self, x - 1, y);
            res %= MOD;
        }
        dp[y][x] = res;
        return res;
    };

    dp[0][0] = 1;
    for (int y = 0; y < H; ++y)
    {
        for (int x = 0; x < W; ++x)
        {
            dfs(dfs, x, y);
        }
    }
    std::cout << dp[H - 1][W - 1];
    return 0;
}