#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"
#include <algorithm>
#include <limits>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

template <typename T>
using greater_priority_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;

void AtcoderSolveHelper::Solve()
{
    int64_t N, M, S, T;
    In() >> N >> M >> S >> T;
    --S, --T;

    std::vector<std::vector<int64_t>> graph(N);
    for (int m = 0; m < M; ++m)
    {
        int64_t A, B;
        In() >> A >> B;
        --A, --B;
        graph[A].push_back(B);
    }
    for (auto &g : graph)
    {
        std::sort(g.begin(), g.end());
    }

    using NODE = std::pair<int64_t, int64_t>;
    greater_priority_queue<NODE> gpq;
    gpq.push({0, S});
    const int64_t INF = std::numeric_limits<int64_t>::max();
    std::vector<int64_t> dp(N, INF);
    dp[S] = 0;

    while (!gpq.empty())
    {
        NODE cur = gpq.top();
        gpq.pop();

        auto &edges = graph[cur.second];
        for (int i = 0; i < edges.size(); ++i)
        {
            int64_t nextCost = cur.first + (i != 0);
            if (dp[edges[i]] <= nextCost)
            {
                continue;
            }

            dp[edges[i]] = nextCost;
            gpq.push({nextCost, edges[i]});
        }
    }

    if (dp[T] == INF)
    {
        Out() << -1;
    }
    else
    {
        Out() << dp[T];
    }

    return;
}

#endif //___INCLUDED_MAIN___