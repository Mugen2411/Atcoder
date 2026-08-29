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
    int64_t N, K;
    In() >> N >> K;

    int64_t mx = 0;
    std::vector<int64_t> num(K);
    for (int i = 0; i < N; ++i)
    {
        int64_t k;
        In() >> K;
        --K;
        ++num[K];
        mx = std::max<int64_t>(mx, num[K]);
    }
    int64_t ans = 0;
    for (auto n : num)
    {
        if (n >= mx - 1)
        {
            ++ans;
        }
    }
    Out() << ans;
    return;
}

#endif //___INCLUDED_MAIN___