#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

void AtcoderSolveHelper::Solve()
{
    int64_t N;
    In() >> N;
    std::vector<int64_t> A(N);
    EachInput(A);

    int64_t ans = 0;
    for (int i = N / 2; i < N; ++i)
    {
        ans += A[i];
    }
    Out() << ans;
    return;
}

#endif //___INCLUDED_MAIN___