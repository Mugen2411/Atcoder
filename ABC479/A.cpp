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
    int N;
    In() >> N;
    std::vector<int> A(N);
    EachInput(A);

    int ans = 0;
    for (int i = 0; i < N; i += 2)
    {
        ans += A[i];
    }

    Out() << ans;
    return;
}

#endif //___INCLUDED_MAIN___