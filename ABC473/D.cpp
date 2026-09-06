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

    std::vector<std::vector<std::vector<int64_t>>> ans(K + 1);
    std::vector<int64_t> cur(N, 0);

    int64_t numCalc = 0;

    auto _Dfs = [&](auto self, int idx, int64_t val) {
        if (idx == N)
        {
            cur[0] = val;
            ans[cur[0]].push_back(cur);
            ++numCalc;
            return;
        }
        for (int i = 0; i <= val / (idx + 1); ++i)
        {
            cur[idx] = i;
            self(self, idx + 1, val - i * (idx + 1));
        }
    };

    _Dfs(_Dfs, 1, K);
    for (auto &a : ans)
    {
        for (auto &v : a)
        {
            for (auto c : v)
            {
                Out() << c << " ";
            }
            Out() << std::endl;
        }
    }
    return;
}

#endif //___INCLUDED_MAIN___