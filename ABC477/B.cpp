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
    int64_t N, D;
    In() >> N >> D;

    std::vector<int64_t> X(N);
    EachInput(X);

    std::vector<int64_t> ans;
    for (int i = 0; i < N; ++i)
    {
        int64_t tmp = 0;
        for (int j = 0; j < N; ++j)
        {
            if (i == j)
            {
                continue;
            }
            if ((X[i] - X[j]) * (X[i] - X[j]) < D * D)
            {
                ++tmp;
            }
        }
        if (tmp == 0)
        {
            ans.push_back(i);
        }
    }
    Out() << ans.size() << std::endl;
    for (auto a : ans)
    {
        Out() << a + 1 << " ";
    }
    if (ans.empty())
    {
        Out() << std::endl;
    }
    return;
}

#endif //___INCLUDED_MAIN___