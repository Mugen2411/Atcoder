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
    SegmentTree<int64_t> seg(N, 0, [](int64_t lhs, int64_t rhs) -> int64_t { return lhs + rhs; });

    while (Q--)
    {
        int cmd;
        In() >> cmd;

        if (cmd == 1)
        {
            int64_t pos, x;
            In() >> pos >> x;
            --pos;
            seg.Update(pos, x);
        }
        else
        {
            int64_t l, r;
            In() >> l >> r;
            --l, --r;
            Out() << seg.Query(l, r) << std::endl;
        }
    }
    return;
}

#endif //___INCLUDED_MAIN___