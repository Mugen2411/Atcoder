#include <iostream>
#include <vector>
#include <unordered_set>

int main()
{
    int N, M;
    std::cin >> N >> M;
    std::vector<std::unordered_set<int>> v(N);
    struct EDGE
    {
        int weight;
        int to;
    };
    std::vector<std::vector<EDGE>> graph(N);
    while (M--)
    {
        int A, B, W;
        std::cin >> A >> B >> W;
        --A, --B;
        graph[A].push_back({W, B});
    }

    auto dfs = [&](auto self, int idx, int cur)
    {
        if (v[idx].count(cur) != 0)
        {
            return;
        }
        v[idx].insert(cur);
        for (auto &e : graph[idx])
        {
            self(self, e.to, cur ^ e.weight);
        }
    };

    dfs(dfs, 0, 0);

    if (v[N - 1].size() == 0)
    {
        std::cout << -1;
        return 0;
    }

    int ans = 999999999;
    for (auto a : v[N - 1])
    {
        ans = std::min(ans, a);
    }
    std::cout << ans;
    return 0;
}