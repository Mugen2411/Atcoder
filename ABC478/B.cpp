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
    int64_t N, V;
    In() >> N >> V;
    std::vector<int64_t> W(N);
    EachInput(W);

    int64_t ans = 0;

    for (int i = 0; i < N - 2; ++i)
    {
        for (int j = i + 1; j < N - 1; ++j)
        {
            for (int k = j + 1; k < N; ++k)
            {
                if (i + j + k + 3 <= V)
                {
                    ans = std::max<int64_t>(ans, W[i] + W[j] + W[k]);
                }
            }
        }
    }

    Out() << ans;

    return;
}

#endif //___INCLUDED_MAIN___