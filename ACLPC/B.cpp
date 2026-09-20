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
    SegmentTree<int64_t> a(N, 0, [](int64_t lhs, int64_t rhs) { return lhs + rhs; });
    In() >> a;

    while (Q--)
    {
        int cmd;
        In() >> cmd;
        if (cmd == 0)
        {
            int64_t p, x;
            In() >> p >> x;

            int64_t cur = a[p];
            a.Update(p, cur + x);
        }
        else
        {
            int64_t l, r;
            In() >> l >> r;

            Out() << a.Query(l, r) << std::endl;
        }
    }
    return;
}

#endif //___INCLUDED_MAIN___