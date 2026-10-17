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
    SegmentTree<int64_t> segL(N - 1, std::numeric_limits<int64_t>::max(),
                              [](int64_t lhs, int64_t rhs) { return std::min(lhs, rhs); });
    SegmentTree<int64_t> segR(N - 1, std::numeric_limits<int64_t>::max(),
                              [](int64_t lhs, int64_t rhs) { return std::min(lhs, rhs); });

    In() >> segL >> segR;

    while (Q--)
    {
        int64_t s, t;
        In() >> s >> t;
        --s, --t;

        if (s < t)
        {
            int64_t costR = (s != N - 1) ? segR[s] : std::numeric_limits<int64_t>::max();
            int64_t costL = (s != 0) ? segL[s - 1] + segR.Query(0, s) : std::numeric_limits<int64_t>::max();

            Out() << std::min<int64_t>(costR, costL) << std::endl;
        }
        else
        {
            int64_t costR = (s != N - 1) ? segR[s] + segL.Query(s, N) : std::numeric_limits<int64_t>::max();
            int64_t costL = (s != 0) ? segL[s - 1] : std::numeric_limits<int64_t>::max();

            Out() << std::min<int64_t>(costR, costL) << std::endl;
        }
    }
    return;
}

#endif //___INCLUDED_MAIN___