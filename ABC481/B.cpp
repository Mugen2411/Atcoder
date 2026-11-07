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
    int N, K;
    In() >> N >> K;
    std::vector<int> A(N);
    EachInput(A);

    int ans = 0;
    if (A[0] == K)
    {
        ++ans;
    }
    for (int i = 1; i < N; ++i)
    {
        if (A[i - 1] < K && A[i] >= K)
        {
            ++ans;
        }
        else if (A[i - 1] > K && A[i] <= K)
        {
            ++ans;
        }
    }
    Out() << ans;
    return;
}

#endif //___INCLUDED_MAIN___