#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void AtcoderSolveHelper::Solve()
{
    int64_t N, M;
    In() >> N >> M;

    struct MATCH
    {
        int64_t A, B;
    };
    std::vector<MATCH> match(M);
    for (auto &&m : match)
    {
        In() >> m.A >> m.B;
        --m.A, --m.B;
    }

    auto _CalcMathID = [N](int64_t A, int64_t B) {
        if (A > B)
        {
            std::swap(A, B);
        }
        return A * N + B;
    };

    std::unordered_set<int64_t> cand;
    auto &sample = match[0];

    {
        int64_t numWin = 0;
        std::vector<MATCH> ext;
        for (auto &m : match)
        {
            if (m.A == sample.A || m.B == sample.A)
            {
                ++numWin;
            }
            else
            {
                ext.push_back(m);
            }
        }
        if (numWin == M)
        {
            for (int b = 0; b < N; ++b)
            {
                if (b == sample.A)
                {
                    continue;
                }
                cand.insert(_CalcMathID(sample.A, b));
            }
        }
        else
        {
            std::vector<int64_t> numExtWin(N, 0);
            for (auto &e : ext)
            {
                ++numExtWin[e.A];
                ++numExtWin[e.B];
            }
            for (int b = 0; b < N; ++b)
            {
                if (numExtWin[b] == ext.size())
                {
                    cand.insert(_CalcMathID(sample.A, b));
                }
            }
        }
    }
    {
        int64_t numWin = 0;
        std::vector<MATCH> ext;
        for (auto &m : match)
        {
            if (m.A == sample.B || m.B == sample.B)
            {
                ++numWin;
            }
            else
            {
                ext.push_back(m);
            }
        }
        if (numWin == M)
        {
            for (int b = 0; b < N; ++b)
            {
                if (b == sample.B)
                {
                    continue;
                }
                cand.insert(_CalcMathID(sample.B, b));
            }
        }
        else
        {
            std::vector<int64_t> numExtWin(N, 0);
            for (auto &e : ext)
            {
                ++numExtWin[e.A];
                ++numExtWin[e.B];
            }
            for (int b = 0; b < N; ++b)
            {
                if (numExtWin[b] == ext.size())
                {
                    cand.insert(_CalcMathID(sample.B, b));
                }
            }
        }
    }

    Out() << cand.size();
    return;
}

#endif //___INCLUDED_MAIN___