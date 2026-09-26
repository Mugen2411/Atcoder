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
    int64_t Q;
    std::string S, T;
    In() >> Q >> S >> T;
    SegmentTree<int> seg(S.size(), 0, [](int lhs, int rhs) { return std::max(lhs, rhs); });
    if (T.size() < S.size())
    {
        for (int l = 0; l <= S.size() - T.size(); ++l)
        {
            int numSame = 0;
            for (int r = 0; r < T.size(); ++r)
            {
                if (S[l + r] == T[r])
                {
                    ++numSame;
                }
            }
            if (numSame == T.size())
            {
                seg.Update(l, 1);
            }
        }
    }

    while (Q--)
    {
        int64_t L, R;
        In() >> L >> R;
        --L, --R;

        if (R - L + 1 < T.size())
        {
            No();
            continue;
        }

        R += 1 - (T.size() - 1);
        /*for (int i = L; i < R; ++i)
        {
            Error() << seg[i];
        }
        Error() << std::endl;*/
        int res = seg.Query(L, R);
        YesNo(res);
    }

    return;
}

#endif //___INCLUDED_MAIN___