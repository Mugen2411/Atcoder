#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <list>

using Graph = std::vector<std::vector<size_t>>;

int main()
{
    size_t N, M;
    std::cin >> N >> M;
    Graph graph(N);
    std::vector<size_t> numPathByVertex(N);
    for (int i = 0; i < M; ++i)
    {
        size_t from, to;
        std::cin >> from >> to;
        --from;
        --to;
        graph[from].push_back(to);
        graph[to].push_back(from);
        ++numPathByVertex[from];
        ++numPathByVertex[to];
    }

    std::list<std::vector<size_t>> group;
    std::vector<bool> searched(N, false);
    for (int start = 0; start < N; ++start)
    {
        if (searched[start])
        {
            continue;
        }
        group.emplace_back(std::vector<size_t>());
        auto dfs = [&](auto &dfs, int64_t start) -> void
        {
            if (searched[start])
            {
                return;
            }
            group.back().push_back(start);
            searched[start] = true;
            for (auto &path : graph[start])
            {
                dfs(dfs, path);
            }
        };
        dfs(dfs, start);
    }
    for (auto &g : group)
    {
        int64_t numPath = 0;
        for (auto &v : g)
        {
            numPath += numPathByVertex[v];
        }
        if (numPath != g.size() * 2)
        {
            std::cout << "No";
            return 0;
        }
    }
    std::cout << "Yes";
    return 0;
}