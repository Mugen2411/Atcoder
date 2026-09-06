#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

#include "../module/ModInt.cpp"
#include "../module/PrefixSum.cpp"

void AtcoderSolveHelper::Solve()
{
    int64_t N;
    In() >> N;

    std::vector<ModInt998> A(N);
    EachInput(A);

    PrefixSum<ModInt998> pres(A.begin(), A.end());
    ModInt998 ans = 0;
    ModInt998 sum = 0;

    for (int64_t l = 0; l < N / 2 + N % 2; ++l)
    {
        const int64_t r = N - l;
        sum += pres.GetSum(r, l);
        ans += sum / ModInt998(l + 1);
        //Error() << sum << " / " << l + 1 << std::endl;
        if (l + 1 != N - l)
        {
            ans += sum / ModInt998(N - l);
            //Error() << sum << " / " << N - l << std::endl;
        }
    }

    Out() << ans;

    return;
}

#endif //___INCLUDED_MAIN___