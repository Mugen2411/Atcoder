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
    int64_t N, D;
    In() >> N >> D;
    std::vector<int64_t> A(N);
    EachInput(A);

    SegmentTree<int64_t> seg(500010, 0, [&](int64_t lhs, int64_t rhs) { return std::max(lhs, rhs); });
    for (int i = 0; i < N; ++i)
    {
        int64_t l = std::max<int64_t>(0, A[i] - D);
        int64_t r = std::min<int64_t>(seg.GetSize() - 1, A[i] + D);
        int64_t mx = seg.Query(l, r + 1);
        seg.Update(A[i], mx + 1);
    }

    Out() << seg.Query(0, seg.GetSize());
    return;
}

#endif //___INCLUDED_MAIN___