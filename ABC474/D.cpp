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
    std::vector<int64_t> A(N);
    std::vector<int64_t> B(N);
    EachInput(A);
    EachInput(B);

    std::vector<int64_t> W(N);
    int64_t loss = 0;
    int64_t over = 0;

    for (int i = 0; i < N; ++i)
    {
        if (A[i] <= B[i])
        {
            loss += (B[i] - A[i]);
            W[i] = 1;
        }
        else
        {
            over += (A[i] - B[i]);
            W[i] = 1'000'000'000'000'000'000;
        }
    }

    if (over != 0)
    {
        Yes();
        for (auto w : W)
        {
            Out() << w << " ";
        }
    }
    else
    {
        No();
    }

    return;
}

#endif //___INCLUDED_MAIN___