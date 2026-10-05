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
    int N, M;
    In() >> N >> M;
    std::vector<int> ans(N);
    int idx = 0;
    while (M--)
    {
        ++ans[idx];
        ++idx;
        idx %= N;
    }
    for (auto a : ans)
    {
        Out() << a << std::endl;
    }
    return;
}

#endif //___INCLUDED_MAIN___