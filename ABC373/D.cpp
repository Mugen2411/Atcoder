#include <iostream>
#include <vector>
#include <queue>

int main()
{
    struct EDGE
    {
        size_t to;
        int64_t weight;
    };

    size_t N, M;
    std::cin >> N >> M;
    std::vector<std::vector<EDGE>> graph(N, std::vector<EDGE>());
    for (int i = 0; i < M; ++i)
    {
        size_t u, v;
        int64_t w;
        std::cin >> u >> v >> w;
        --u, --v;
        graph[u].push_back({v, w});
        graph[v].push_back({u, -w});
    }

    int64_t inf = 1ll << 60;

    std::vector<int64_t> weight(N, -inf);

    for (int i = 0; i < N; ++i)
    {
        if (weight[i] == -inf)
        {
            weight[i] = 0;
        }
        std::queue<size_t> bfsQueue;

        bfsQueue.push(i);

        while (!bfsQueue.empty())
        {
            size_t cur = bfsQueue.front();
            bfsQueue.pop();

            for (auto &e : graph[cur])
            {
                if (weight[e.to] == -inf)
                {
                    weight[e.to] = weight[cur] + e.weight;
                    bfsQueue.push(e.to);
                }
            }
        }
    }

    for (auto i : weight)
    {
        std::cout << i << " ";
    }

    return 0;
}