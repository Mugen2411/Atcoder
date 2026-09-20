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

    SegmentTree<int64_t> a(N, std::numeric_limits<int64_t>::max(),
                           [](int64_t lhs, int64_t rhs) { return std::min(lhs, rhs); });

    In() >> a;

    while (Q--)
    {
        int64_t T, X, Y;
        In() >> T >> X >> Y;

        if (T == 1)
        {
            a.Update(X, Y);
        }
        else
        {
            Out() << a.Query(X, Y) << std::endl;
        }
    }
    return;
}

#endif //___INCLUDED_MAIN___