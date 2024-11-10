#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include <functional>

int main()
{
    const int64_t inf = 1ll << 60;

    size_t N, M;
    std::cin >> N >> M;
    std::vector<int64_t> seen(N + 1, inf);
    std::vector<std::vector<int64_t>> graph(N);
    while (M--)
    {
        size_t a, b;
        std::cin >> a >> b;
        --a, --b;
        if (b == 0)
        {
            b = N;
        }
        graph[a].push_back(b);
    }
    int64_t ans = inf;

    std::priority_queue<std::array<int64_t, 2>, std::vector<std::array<int64_t, 2>>,
                        std::function<bool(const std::array<int64_t, 2> &, const std::array<int64_t, 2>)>>
        q([](const std::array<int64_t, 2> &lhs, const std::array<int64_t, 2> &rhs)
          { return lhs[0] > rhs[0]; });
    q.push({seen[0] = 0, 0});
    while (!q.empty())
    {
        std::array<int64_t, 2> top = q.top();
        q.pop();
        int64_t cur = top[1];
        int64_t dist = top[0];
        if (cur == N)
        {
            ans = std::min(ans, dist);
            continue;
        }
        if (seen[cur] < dist)
        {
            continue;
        }
        for (auto &p : graph[cur])
        {
            if (dist + 1 < seen[p])
            {
                q.push({seen[p] = dist + 1, p});
            }
        }
    }

    if (ans == inf)
    {
        std::cout << -1;
    }
    else
    {
        std::cout << ans;
    }
    return 0;
}