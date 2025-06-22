#include <iostream>
#include <vector>

int main()
{
    int N, M;
    std::cin >> N >> M;
    struct EDGE
    {
        int64_t weight;
        int to;
    };
    std::vector<std::vector<EDGE>> graph(N);
    while (M--)
    {
        int u, v;
        int64_t w;
        std::cin >> u >> v >> w;
        --u, --v;
        graph[u].push_back({w, v});
        graph[v].push_back({w, u});
    }

    auto ReadBit = [](int64_t filter, int digit)
    {
        return (filter >> digit) & 1;
    };
    auto WriteBit = [](int64_t &filter, int digit)
    {
        filter |= 1 << digit;
    };

    int64_t ans = 0xfffffffffffffffll;

    auto dfs = [&](auto self, int cur, int64_t filter, int64_t val)
    {
        if (cur == N - 1)
        {
            ans = std::min(ans, val);
            return;
        }
        WriteBit(filter, cur);
        for (auto &e : graph[cur])
        {
            if (!ReadBit(filter, e.to))
            {
                self(self, e.to, filter, val ^ e.weight);
            }
        }
    };

    dfs(dfs, 0, 0, 0);

    std::cout << ans;

    return 0;
}