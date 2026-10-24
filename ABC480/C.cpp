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
    int64_t N, K, T;
    In() >> N >> K >> T;

    std::vector<int64_t> A(N);
    EachInput(A);
    std::sort(A.begin(), A.end());
    while (!A.empty() && A.back() > T)
    {
        A.pop_back();
    }

    int64_t last = 0;
    struct RANGE
    {
        int64_t Begin, End;
    };
    std::vector<RANGE> R;
    for (auto a : A)
    {
        if (last < a)
        {
            R.push_back(RANGE{.Begin = last, .End = a});
        }
        last = a + K;
    }
    if (last < T)
    {
        R.push_back(RANGE{.Begin = last, .End = T});
    }

    // 取得した空きから必要回数を算出
    int64_t ans = 0;
    last = 0;
    for (auto &r : R)
    {
        if (last > r.Begin)
        {
            r.Begin = last;
        }
        if (r.Begin >= r.End)
        {
            continue;
        }
        int64_t tmp = (r.End - r.Begin + K - 1) / K;
        ans += tmp;
        last = tmp * K;
    }

    Out() << ans;
    return;
}

#endif //___INCLUDED_MAIN___