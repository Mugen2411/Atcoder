#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"
#include <vector>

void AtcoderSolveHelper::Solve()
{
    int64_t N, M;
    In() >> N >> M;

    std::vector<int64_t> A(N);
    std::vector<int64_t> B(N - 1);
    EachInput(A);
    EachInput(B);

    int64_t ans = N * 2;

    auto _GetAns = [&](std::vector<int64_t> _A) {
        int64_t _ans = 0;
        for (int i = 0; i < N - 1; ++i)
        {
            if (((_A[i] + _A[i + 1]) % M != B[i]))
            {
                ++_A[i + 1];
                ++_ans;
            }
        }
        return _ans;
    };

    std::vector<int64_t> A2(A);
    ++A2[0];
    ans = std::min<int64_t>(_GetAns(A), ans);
    ans = std::min<int64_t>(_GetAns(A2) + 1, ans);

    Out() << ans;
    return;
}

#endif //___INCLUDED_MAIN___