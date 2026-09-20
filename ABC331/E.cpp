#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"
#include "../module/SegmentTree.cpp"
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

void AtcoderSolveHelper::Solve()
{
    int64_t N, M, L;
    In() >> N >> M >> L;
    std::vector<int64_t> A(N);
    std::vector<int64_t> B(M);
    EachInput(A);
    EachInput(B);

    std::vector<std::vector<int64_t>> notForSales(N);
    for (int i = 0; i < L; ++i)
    {
        int64_t c, d;
        In() >> c >> d;

        --c, --d;
        notForSales[c].push_back(d);
    }

    SegmentTree<int64_t> maxSeg(M, 0, [](int64_t lhs, int64_t rhs) { return std::max(lhs, rhs); });
    for (int i = 0; i < M; ++i)
    {
        maxSeg.Update(i, B[i]);
    }

    int64_t ans = 0;
    for (int i = 0; i < N; ++i)
    {
        for (auto b : notForSales[i])
        {
            maxSeg.Update(b, 0);
        }
        ans = std::max<int64_t>(ans, maxSeg.Query(0, M) + A[i]);
        for (auto b : notForSales[i])
        {
            maxSeg.Update(b, B[b]);
        }
    }
    Out() << ans;
    return;
}

#endif //___INCLUDED_MAIN___