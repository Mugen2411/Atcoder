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
    std::string S;
    In() >> S;
    for (auto &c : S)
    {
        if (c != 'A')
        {
            c = '.';
        }
    }
    Out() << S;
    return;
}

#endif //___INCLUDED_MAIN___