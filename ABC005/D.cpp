#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Grid2D.cpp"
#include "../module/Helper.cpp"
#include "../module/PrefixSum.cpp"

void AtcoderSolveHelper::Solve()
{
    size_t N;
    In() >> N;

    Grid2D<int64_t> A(N, N, 0);
    In() >> A;
    PrefixSum<int64_t> pres(A);

    std::vector<int64_t> score(N * N + 1, 0);

    for (int x1 = 0; x1 < N; ++x1)
    {
        for (int x2 = x1 + 1; x2 <= N; ++x2)
        {
            for (int y1 = 0; y1 < N; ++y1)
            {
                for (int y2 = y1 + 1; y2 <= N; ++y2)
                {
                    int64_t area = (x2 - x1) * (y2 - y1);
                    int64_t val = pres.GetSum(x2, x1, y2, y1);
                    score[area] = std::max<int64_t>(score[area], val);
                }
            }
        }
    }

    for (int a = 1; a < score.size(); ++a)
    {
        score[a] = std::max<int64_t>(score[a], score[a - 1]);
    }

    int64_t Q;
    In() >> Q;

    while (Q--)
    {
        int64_t P;
        In() >> P;
        Out() << score[P] << std::endl;
    }

    return;
}

#endif //___INCLUDED_MAIN___