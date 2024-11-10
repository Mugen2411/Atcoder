#include <iostream>
#include <vector>

int dp[101000] = {0};

int main()
{
    size_t N, M;
    std::cin >> N >> M;
    std::vector<std::vector<size_t>> graph(N);
    for (int i = 0; i < M; ++i)
    {
        size_t x, y;
        std::cin >> x >> y;
        --x;
        --y;
        graph[x].push_back(y);
    }

    for (auto &i : dp)
    {
        i = -1;
    }

    auto dfs = [&](auto self, int cur) -> int
    {
        if (dp[cur] != -1)
        {
            return dp[cur];
        }

        int res = 0;
        for (const auto &p : graph[cur])
        {
            res = std::max(res, self(self, p) + 1);
        }

        dp[cur] = res;
        return res;
    };

    int ans = 0;
    for (int i = 0; i < N; ++i)
    {
        ans = std::max(ans, dfs(dfs, i));
    }

    std::cout << ans;
    return 0;
}