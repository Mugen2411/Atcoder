#include <iostream>
#include <vector>
#include <queue>

int main()
{
    size_t N, M;
    std::cin >> N >> M;
    using pair = std::pair<size_t, size_t>;
    struct edge
    {
        size_t to;
        size_t cost;
    };
    using Graph = std::vector<std::vector<edge>>;
    Graph g;
    g.resize(N);
    size_t ta, tb, tc;
    for (size_t i = 0; i < M; ++i)
    {
        std::cin >> ta >> tb >> tc;
        --ta, --tb;
        edge te = {tb, tc};
        g[ta].push_back(te);
        te.to = ta;
        g[tb].push_back(te);
    }
    size_t ans = 0;
    for (int i = 0; i < N; ++i)
    {
        std::vector<bool> used(N, false);
        auto dfs = [&](auto self, size_t start, size_t dist) -> void
        {
            if (dist > ans)
            {
                ans = dist;
            }
            used[start] = true;
            for (const auto &v : g[start])
            {
                if (used[v.to])
                {
                    continue;
                }
                self(self, v.to, dist + v.cost);
            }
            used[start] = false;
        };
        dfs(dfs, i, 0);
    }
    std::cout << ans << std::endl;
    return 0;
}