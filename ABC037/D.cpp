#include <iostream>

int64_t dp[1100][1100] = {0};
int64_t A[1100][1100] = {0};

#define MOD 1000000007

int main()
{
    size_t H, W;
    std::cin >> H >> W;
    for (int y = 0; y < H; ++y)
    {
        for (int x = 0; x < W; ++x)
        {
            std::cin >> A[y][x];
            dp[y][x] = -1;
        }
    }

    auto dfs = [&](auto self, int cx, int cy) -> int
    {
        if (dp[cy][cx] != -1)
        {
            return dp[cy][cx];
        }

        int64_t res = 1;
        if (cy > 0)
        {
            if (A[cy][cx] < A[cy - 1][cx])
            {
                res += self(self, cx, cy - 1);
                res %= MOD;
            }
        }
        if (cy < H - 1)
        {
            if (A[cy][cx] < A[cy + 1][cx])
            {
                res += self(self, cx, cy + 1);
                res %= MOD;
            }
        }
        if (cx > 0)
        {
            if (A[cy][cx] < A[cy][cx - 1])
            {
                res += self(self, cx - 1, cy);
                res %= MOD;
            }
        }
        if (cx < W - 1)
        {
            if (A[cy][cx] < A[cy][cx + 1])
            {
                res += self(self, cx + 1, cy);
                res %= MOD;
            }
        }
        dp[cy][cx] = res;
        return res;
    };

    int64_t ans = 0;
    for (int y = 0; y < H; ++y)
    {
        for (int x = 0; x < W; ++x)
        {
            ans += dfs(dfs, x, y);
            ans %= MOD;
        }
    }
    std::cout << ans;
    return 0;
}