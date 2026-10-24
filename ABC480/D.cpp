#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/BinarySearch.cpp"
#include "../module/Helper.cpp"
#include "../module/PrefixSum.cpp"
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

void AtcoderSolveHelper::Solve()
{
    int64_t N, Q;
    In() >> N >> Q;

    const int64_t LEN = (N + 1) * N / 2;

    std::vector<int64_t> A(N);
    EachInput(A);

    PrefixSum<int64_t> pres1(A.begin(), A.end());
    std::vector<int64_t> A2;
    for (int i = 1; i <= N; ++i)
    {
        A2.push_back(pres1.GetSum(i, 0));
    }
    PrefixSum<int64_t> pres2(A2.begin(), A2.end());

    std::vector<int64_t> O;
    for (int i = 1; i <= N; ++i)
    {
        O.push_back(i);
    }
    PrefixSum<int64_t> o1(O.begin(), O.end());
    std::vector<int64_t> O2;
    for (int i = 1; i <= N; ++i)
    {
        O2.push_back(o1.GetSum(i, 0));
    }

    while (Q--)
    {
        int64_t L, R;
        In() >> L >> R;

        int64_t oL = BinarySearch(-1, O2.size(), [&](int64_t cur) { return O2[cur] >= L; });
        int64_t oR = BinarySearch(-1, O2.size(), [&](int64_t cur) { return O2[cur] >= R; });

        int64_t ans = pres2.GetSum(oR + 1, oL);
        if (oL > 0)
        {
            ans -= pres1.GetSum(L - O2[oL - 1] - 1, 0);
        }

        if (R < O2[oR])
        {
            ans -= pres1.GetSum(N, O2[oR] - R);
        }

        Out() << ans << std::endl;
    }
    return;
}

#endif //___INCLUDED_MAIN___