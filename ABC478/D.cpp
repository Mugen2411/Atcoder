#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"
#include "../module/RangeSet.cpp"
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

void AtcoderSolveHelper::Solve()
{
    int64_t N, Q;
    In() >> N >> Q;

    std::vector<std::unordered_map<int64_t, int64_t>> query(N + 1);
    while (Q--)
    {
        int64_t L, R, X;
        In() >> L >> R >> X;
        --L;
        ++query[L][X];
        --query[R][X];
    }

    std::unordered_map<int64_t, int64_t> cur;
    for (int i = 0; i < N; ++i)
    {
        for (auto &q : query[i])
        {
            cur[q.first] += q.second;
            if (cur[q.first] == 0)
            {
                cur.erase(q.first);
            }
        }
        Out() << cur.size() << " ";
    }

    return;
}

#endif //___INCLUDED_MAIN___