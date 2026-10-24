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
    std::array<char, 4> S;
    EachInput(S);

    for (int i = 0; i < 4; ++i)
    {
        if (S[i] == 'A')
        {
            YesNo(S[(3 - i + 4) % 4] != 'D');
        }
    }
    return;
}

#endif //___INCLUDED_MAIN___