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
    int64_t N;
    In() >> N;
    std::string S;
    In() >> S;

    struct Elem
    {
        int64_t leftB, rightA;
    };
    SegmentTree<Elem> seg(N, Elem{0, 0}, [](const Elem &lhs, const Elem &rhs) {
        int64_t numPair = std::min<int64_t>(lhs.rightA, rhs.leftB);
        return Elem{lhs.leftB + rhs.leftB - numPair, lhs.rightA + rhs.rightA - numPair};
    });

    for (int i = 0; i < N; ++i)
    {
        if (S[i] == 'A')
        {
            seg.Update(i, Elem{0, 1});
        }
        else
        {
            seg.Update(i, Elem{1, 0});
        }
    }

    int64_t Q;
    In() >> Q;
    while (Q--)
    {
        int cmd;
        In() >> cmd;
        if (cmd == 1)
        {
            int i;
            char c;
            In() >> i >> c;
            --i;
            if (c == 'A')
            {
                seg.Update(i, Elem{0, 1});
                S[i] = 'A';
            }
            else
            {
                seg.Update(i, Elem{1, 0});
                S[i] = 'B';
            }
        }
        else
        {
            int l, r;
            In() >> l >> r;
            --l, --r;
            Elem T = seg.Query(l, r + 1);
            YesNo(T.leftB == 0);
        }
    }

    return;
}

#endif //___INCLUDED_MAIN___