#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"
#include "../module/PrefixSum.cpp"

void AtcoderSolveHelper::Solve()
{
    int64_t N;
    In() >> N;

    std::vector<int64_t> W(N);
    EachInput(W);

    PrefixSum<int64_t> pres(W.begin(), W.end());

    int64_t ans = 99999;
    for (int t = 1; t <= N; ++t)
    {
        int64_t tmp = std::abs(pres.GetSum(0, t) - pres.GetSum(t, N));
        ans = std::min<int64_t>(tmp, ans);
    }

    Out() << ans;
    return;
}

#endif //___INCLUDED_MAIN___