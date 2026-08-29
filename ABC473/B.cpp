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
    std::unordered_map<int64_t, int64_t> A;
    int64_t N;
    In() >> N;
    for (int i = 0; i < N; ++i)
    {
        int64_t tmp;
        In() >> tmp;
        ++A[tmp];
    }

    int64_t ans = 0;
    for (auto &a : A)
    {
        if (a.second & 1)
        {
            ans += a.first;
        }
    }

    Out() << ans;

    return;
}

#endif //___INCLUDED_MAIN___