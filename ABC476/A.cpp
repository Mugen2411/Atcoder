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
    if (S.back() == 'e')
    {
        S.push_back('r');
    }
    else
    {
        S.push_back('e');
        S.push_back('r');
    }
    Out() << S;
    return;
}

#endif //___INCLUDED_MAIN___