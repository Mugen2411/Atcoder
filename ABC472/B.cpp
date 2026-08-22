#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

void AtcoderSolveHelper::Solve()
{
    int N;
    In() >> N;
    std::vector<int> L(N);
    EachInput(L);

    for (int i = 1; i < N; ++i)
    {
        L[i] += L[i - 1];
    }

    int ans = L.back();
    for (int i = 0; i < N - 1; ++i)
    {
        ans = std::min<int>(ans, std::abs(L[i] - L.back() + L[i]));
    }
    Out() << ans;
    return;
}

#endif //___INCLUDED_MAIN___