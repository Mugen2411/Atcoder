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
    int64_t N;
    In() >> N;
    std::vector<int64_t> P(N);
    EachInput(P);
    for (auto &p : P)
    {
        --p;
    }

    for (int i = 0; i < N; ++i)
    {
        if (P[i] / 10 != i / 10)
        {
            No();
            return;
        }
    }
    Yes();

    return;
}

#endif //___INCLUDED_MAIN___