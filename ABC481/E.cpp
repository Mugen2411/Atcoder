#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"
#include "../module/ModInt.cpp"
#include <algorithm>
#include <limits>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

void AtcoderSolveHelper::Solve()
{
    int64_t N, M;
    In() >> N >> M;

    struct EDGE
    {
        int64_t to;
        int64_t cost;
    };
    std::vector<std::vector<EDGE>> graph(N);

    for (int m = 0; m < M; ++m)
    {
        int64_t A, B, C;
        In() >> A >> B >> C;
        --A, --B;
        graph[A].push_back({B, C});
    }
    for (auto &g : graph)
    {
        std::sort(g.begin(), g.end(), [](const EDGE &lhs, const EDGE &rhs) { return lhs.cost < rhs.cost; });
    }
    std::vector<ModInt998> score(N, -1);
    score[0] = 0;

    struct COST
    {
        int64_t generation;
        int64_t lastCost;
    };
    std::vector<COST> searched(N, {std::numeric_limits<int64_t>::max(), 10});
    std::queue<ModInt998> qSc;
    std::queue<int64_t> qIdx;
    std::queue<int64_t> qGen;
    qSc.push(0);
    qIdx.push(0);
    qGen.push(0);
    searched[0] = {.generation = 0, .lastCost = 0};

    while (!qSc.empty())
    {
        ModInt998 curSc = qSc.front();
        qSc.pop();
        int64_t curIdx = qIdx.front();
        qIdx.pop();
        int64_t curGen = qGen.front();
        qGen.pop();

        score[curIdx] = curSc;
        for (auto &e : graph[curIdx])
        {
            if ((searched[e.to].generation > curGen + 1) ||
                (searched[e.to].generation == curGen + 1 && searched[e.to].lastCost > e.cost))
            {
                searched[e.to] = {.generation = curGen + 1, .lastCost = e.cost};

                ModInt998 nextSc = curSc * 10ll;
                nextSc += e.cost;
                qSc.push(nextSc);
                qIdx.push(e.to);
                qGen.push(curGen + 1);
            }
        }
    }

    for (int i = 1; i < N; ++i)
    {
        Out() << score[i] << std::endl;
    }

    return;
}

#endif //___INCLUDED_MAIN___