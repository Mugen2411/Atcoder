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
    char c;
    In() >> c;

    switch (c)
    {
    case 'B':
        Out() << 'Y';
        return;
    case 'Y':
        Out() << 'R';
        return;
    case 'R':
        Out() << 'B';
        return;
    }
    return;
}

#endif //___INCLUDED_MAIN___