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
    int64_t N, K;
    In() >> N >> K;
    std::vector<int64_t> A(N);
    EachInput(A);

    std::vector<int64_t> sorted(A);
    std::sort(sorted.begin(), sorted.end());

    int firstIdx = 0;
    while (firstIdx < N)
    {
        if (A[firstIdx] != sorted[firstIdx])
        {
            break;
        }
        ++firstIdx;
    }
    int lastIdx = N - 1;
    while (lastIdx >= 0)
    {
        if (A[lastIdx] != sorted[lastIdx])
        {
            break;
        }
        --lastIdx;
    }

    YesNo(lastIdx - firstIdx + 1 <= K);

    return;
}

#endif //___INCLUDED_MAIN___