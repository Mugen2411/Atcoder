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
    int64_t N, Q;
    In() >> N >> Q;
    SegmentTree<int64_t> A(N, 0, [](int64_t lhs, int64_t rhs) { return lhs ^ rhs; });
    In() >> A;

    while (Q--)
    {
        int64_t T, X, Y;
        In() >> T >> X >> Y;

        if (T == 1)
        {
            --X;
            int64_t cur = A[X];
            A.Update(X, cur ^ Y);
        }
        else
        {
            --X;
            Out() << A.Query(X, Y) << std::endl;
        }
    }
    return;
}

#endif //___INCLUDED_MAIN___