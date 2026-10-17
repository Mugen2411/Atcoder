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
    std::string S;
    In() >> N >> S;
    S.push_back('S');

    int ans = 0;
    int cur = 0;
    for (char c : S)
    {
        if (c == 'R')
        {
            ++cur;
        }
        else
        {
            ans = std::max<int>(cur, ans);
            cur = 0;
        }
    }

    Out() << ans;
    return;
}

#endif //___INCLUDED_MAIN___