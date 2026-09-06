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
    int X;
    In() >> X;
    if (X == 1)
    {
        Out() << "2";
    }
    else
    {
        Out() << "1";
    }
    return;
}

#endif //___INCLUDED_MAIN___