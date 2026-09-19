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
    In() >> N;
    std::string S, T;
    In() >> S >> T;

    for (int i = 0; i < N; ++i)
    {
        if (T[i] != '*' && T[i] != S[i])
        {
            No();
            return;
        }
    }
    Yes();
    return;
}

#endif //___INCLUDED_MAIN___