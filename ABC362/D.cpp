#include <iostream>
#include <vector>
#include <utility>    // std::pair
#include <queue>      // std::priority_queue
#include <functional> // std::greater

constexpr long long INF = (1LL << 60);

// 辺の情報
struct Edge
{
    // 行先
    int to;

    // コスト
    int cost;

    int vertexCost;
};

using Graph = std::vector<std::vector<Edge>>;

// { distance, from }
using Pair = std::pair<long long, int>;

// ダイクストラ法 (1.1 基本実装)
// distances は頂点数と同じサイズ, 全要素 INF で初期化しておく
void Dijkstra(const Graph &graph, std::vector<long long> &distances, int startIndex)
{
    // 「現時点での最短距離, 頂点」の順に取り出す priority_queue
    // デフォルトの priority_queue は降順に取り出すため std::greater を使う
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> q;
    q.emplace((distances[startIndex] = 0), startIndex);

    while (!q.empty())
    {
        const long long distance = q.top().first;
        const int from = q.top().second;
        q.pop();

        // 最短距離でなければ処理しない
        if (distances[from] < distance)
        {
            continue;
        }

        // 現在の頂点からの各辺について
        for (const auto &edge : graph[from])
        {
            // to までの新しい距離
            const long long d = (distances[from] + edge.cost + edge.vertexCost);

            // d が現在の記録より小さければ更新
            if (d < distances[edge.to])
            {
                q.emplace((distances[edge.to] = d), edge.to);
            }
        }
    }
}

int main()
{
    size_t vertexNum, edgeNum;
    std::cin >> vertexNum >> edgeNum;

    Graph graph(vertexNum);
    std::vector<int64_t> A(vertexNum);

    size_t tmpU, tmpV;
    for (int i = 0; i < vertexNum; ++i)
    {
        std::cin >> A[i];
    }
    for (int i = 0; i < edgeNum; ++i)
    {
        Edge tmpE;
        std::cin >> tmpU >> tmpV >> tmpE.cost;
        tmpE.to = tmpV - 1;
        tmpE.vertexCost = A[tmpU - 1];
        graph[tmpU - 1].emplace_back(tmpE);
        tmpE.to = tmpU - 1;
        tmpE.vertexCost = A[tmpV - 1];
        graph[tmpV - 1].emplace_back(tmpE);
    }

    std::vector<long long> distances(vertexNum, INF);
    Dijkstra(graph, distances, 0);

    for (int64_t i = 1; i < vertexNum; ++i)
    {
        std::cout << distances[i] + A[i] << " ";
    }

    return 0;
}