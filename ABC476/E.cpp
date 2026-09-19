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
    int64_t N, M;
    In() >> N >> M;
    std::vector<int64_t> P(N);
    EachInput(P);
    struct Elem
    {
        int64_t idx;
        int64_t val;
    };
    SegmentTree<Elem> minSeg(N, Elem{-1, std::numeric_limits<int64_t>::max()}, [](Elem lhs, Elem rhs) -> Elem {
        if (lhs.val < rhs.val)
        {
            return Elem{lhs.idx, lhs.val};
        }
        else
        {
            return Elem{rhs.idx, rhs.val};
        }
    });
    SegmentTree<Elem> maxSeg(N, Elem{-1, std::numeric_limits<int64_t>::min()}, [](Elem lhs, Elem rhs) -> Elem {
        if (lhs.val > rhs.val)
        {
            return Elem{lhs.idx, lhs.val};
        }
        else
        {
            return Elem{rhs.idx, rhs.val};
        }
    });

    for (int i = 0; i < N; ++i)
    {
        minSeg.Update(i, Elem{i, P[i]});
        maxSeg.Update(i, Elem{i, P[i]});
    }

    while (M--)
    {
        int64_t L, R;
        In() >> L >> R;
        --L;

        Elem minVal = minSeg.Query(L, R);
        Elem maxVal = maxSeg.Query(L, R);

        minSeg.Update(maxVal.idx, Elem{maxVal.idx, minVal.val});
        minSeg.Update(minVal.idx, Elem{minVal.idx, maxVal.val});
        maxSeg.Update(maxVal.idx, Elem{maxVal.idx, minVal.val});
        maxSeg.Update(minVal.idx, Elem{minVal.idx, maxVal.val});
    }

    for (int i = 0; i < N; ++i)
    {
        Out() << minSeg[i].val << " ";
    }
    return;
}

#endif //___INCLUDED_MAIN___