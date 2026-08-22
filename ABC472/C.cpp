#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

#include "../module/PrefixSum.cpp"

void AtcoderSolveHelper::Solve()
{
    int64_t N, M, K;
    In() >> N >> M >> K;
    std::vector<int64_t> A(N);
    EachInput(A);
    std::vector<bool> isAte(N, false);

    int64_t cal = 0;
    for (int i = 0; i < N; ++i)
    {
        if (i >= M && isAte[i - M])
        {
            cal -= A[i - M];
        }
        if (cal + A[i] <= K)
        {
            cal += A[i];
            isAte[i] = true;
            Yes();
        }
        else
        {
            isAte[i] = false;
            No();
        }
    }
}

#endif //___INCLUDED_MAIN___