#include <iostream>
#include <vector>
#include <array>
#include <queue>

int main()
{
    size_t N;
    std::cin >> N;
    std::array<size_t, 3> tmp;
    using pair = std::pair<size_t, size_t>;
    struct edge
    {
        size_t to;
        size_t cost;
    };
    std::vector<std::vector<edge>> graph(N);
    for (size_t i = 0; i < N - 1; ++i)
    {
        std::cin >> tmp[0] >> tmp[1] >> tmp[2];
        --tmp[2];
        graph[i].push_back(edge{i + 1, tmp[0]});
        graph[i].push_back(edge{tmp[2], tmp[1]});
    }
    std::vector<size_t> dist;
    std::priority_queue<pair, std::vector<pair>, std::greater<pair>> Q;
    dist.assign(N, 1e20);
    Q.emplace(dist[0] = 0, 0);
    while (!Q.empty())
    {
        pair tmp = Q.top();
        Q.pop();
        size_t d = tmp.first;
        size_t v = tmp.second;
        if (v == N - 1)
        {
            continue;
        }
        if (d > dist[v])
        {
            continue;
        }
        for (const auto &edge : graph[v])
        {
            size_t nextDist = d + edge.cost;
            if (nextDist < dist[edge.to])
            {
                Q.emplace(dist[edge.to] = nextDist, edge.to);
            }
        }
    }

    std::cout << dist[N - 1] << std::endl;

    return 0;
}