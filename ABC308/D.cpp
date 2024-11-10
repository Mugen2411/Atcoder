#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

struct EDGE
{
    size_t toIndex;
    size_t cost;
};
size_t numVertex;
std::vector<std::vector<EDGE>> graph;

int main()
{
    size_t H, W;
    std::cin >> H >> W;
    numVertex = H * W;
    auto calcIndex = [W](size_t x, size_t y)
    { return y * W + x; };
    graph.resize(numVertex);
    std::unordered_map<char, char> snuke;
    snuke['s'] = 'n';
    snuke['n'] = 'u';
    snuke['u'] = 'k';
    snuke['k'] = 'e';
    snuke['e'] = 's';
    std::vector<std::string> S(H);
    for (size_t y = 0; y < H; ++y)
    {
        std::cin >> S[y];
    }
    if (S[0][0] != 's')
    {
        std::cout << "No" << std::endl;
        return 0;
    }
    for (size_t y = 0; y < H; ++y)
    {
        for (size_t x = 0; x < W; ++x)
        {
            if (y > 1 && snuke[S[y][x]] == S[y - 1][x])
            {
                graph[calcIndex(x, y)].push_back({calcIndex(x, y - 1), 0});
            }
            if (y < H - 1 && snuke[S[y][x]] == S[y + 1][x])
            {
                graph[calcIndex(x, y)].push_back({calcIndex(x, y + 1), 0});
            }
            if (x > 1 && snuke[S[y][x]] == S[y][x - 1])
            {
                graph[calcIndex(x, y)].push_back({calcIndex(x - 1, y), 0});
            }
            if (x < W - 1 && snuke[S[y][x]] == S[y][x + 1])
            {
                graph[calcIndex(x, y)].push_back({calcIndex(x + 1, y), 0});
            }
        }
    }
    std::vector<bool> searched(numVertex, false);
    auto dfs = [&](auto &self, size_t start) -> void
    {
        searched[start] = true;
        for (auto &v : graph[start])
        {
            if (searched[v.toIndex])
            {
                continue;
            }
            self(self, v.toIndex);
        }
    };
    dfs(dfs, calcIndex(0, 0));
    if (searched[calcIndex(W - 1, H - 1)])
    {
        std::cout << "Yes" << std::endl;
    }
    else
    {
        std::cout << "No" << std::endl;
    }
    return 0;
}