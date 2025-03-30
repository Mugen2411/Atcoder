#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

int main()
{
    int N, M;
    std::cin >> N >> M;
    std::vector<std::unordered_set<int>> graph(N);
    for (int i = 0; i < M; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        graph[u].insert(v);
        graph[v].insert(u);
    }

    int ans = 0;
    std::vector<int> seen(N, 0);
    std::queue<int> q;
    std::queue<int> prev;
    for (int i = 0; i < N; ++i)
    {
        if (seen[i] != 0)
        {
            continue;
        }
        q.push(i);
        prev.push(-1);
        while (!q.empty())
        {
            auto cur = q.front();
            q.pop();
            auto before = prev.front();
            prev.pop();
            for (auto to = graph[cur].begin(); to != graph[cur].end();)
            {
                if (seen[*to] != 0)
                {
                    if (*to != before)
                    {
                        graph[*to].erase(cur);
                        to = graph[cur].erase(to);
                        ++ans;
                    }
                }
                else
                {
                    q.push(*to);
                    prev.push(cur);
                    seen[*to] = 1;
                }
            }
        }
    }

    std::cout << ans;

    return 0;
}