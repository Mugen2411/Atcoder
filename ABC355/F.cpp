#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
using ll = long long;
#define REP(A, B) for (ll A = 0; A < B; ++A)

using namespace std;
/* UnionFind：素集合系管理の構造体(union by rank)
    isSame(x, y): x と y が同じ集合にいるか。 計算量はならし O(α(n))
    unite(x, y): x と y を同じ集合にする。計算量はならし O(α(n))
*/
struct UnionFind
{ // The range of node number is u 0 v n-1
    vector<int> rank, parents;
    UnionFind() {}
    UnionFind(int n)
    { // make n trees.
        rank.resize(n, 0);
        parents.resize(n, 0);
        for (int i = 0; i < n; i++)
        {
            makeTree(i);
        }
    }
    void makeTree(int x)
    {
        parents[x] = x; // the parent of x is x
        rank[x] = 0;
    }
    bool isSame(int x, int y) { return findRoot(x) == findRoot(y); }
    void unite(int x, int y)
    {
        x = findRoot(x);
        y = findRoot(y);
        if (rank[x] > rank[y])
        {
            parents[y] = x;
        }
        else
        {
            parents[x] = y;
            if (rank[x] == rank[y])
            {
                rank[y]++;
            }
        }
    }
    int findRoot(int x)
    {
        if (x != parents[x])
            parents[x] = findRoot(parents[x]);
        return parents[x];
    }
};
// 辺の定義
struct Edge
{
    long long u;
    long long v;
    long long cost;
};
bool comp_e(const Edge &e1, const Edge &e2) { return e1.cost < e2.cost; } // 辺を直接比較するための関数
/* Kruskal :クラスカル法で minimum spanning tree を求める構造体
    入力: 辺のvector, 頂点数V
    最小全域木の重みの総和: sum
    計算量: O(|E|log|V|)
*/
struct Kruskal
{
    UnionFind uft;
    long long sum; // 最小全域木の重みの総和
    vector<Edge> edges;
    int V;
    Kruskal(const vector<Edge> &edges_, int V_) : edges(edges_), V(V_) { init(); }
    void init()
    {
        sort(edges.begin(), edges.end(), comp_e); // 辺の重みでソート
        uft = UnionFind(V);
        sum = 0;
        for (auto e : edges)
        {
            if (!uft.isSame(e.u, e.v))
            { // 閉路にならなければ加える
                uft.unite(e.u, e.v);
                sum += e.cost;
            }
        }
    }
};

int main()
{
    size_t N, Q;
    std::cin >> N >> Q;
    vector<Edge> G(N - 1);
    G.reserve(N + Q - 1);
    Edge tmp;
    for (size_t i = 0; i < N - 1; ++i)
    {
        cin >> tmp.u >> tmp.v >> tmp.cost;
        G[i] = tmp;
    }
    for (size_t i = 0; i < Q; ++i)
    {
        cin >> tmp.u >> tmp.v >> tmp.cost;
        G.push_back(tmp);
        Kruskal krs(G, N);
        cout << krs.sum << endl;
    }
    return 0;
}