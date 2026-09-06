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
    EachInput(A);

    int64_t mx = 0;
    for (auto a : A)
    {
        mx = std::max<int64_t>(mx, a);
    }
    int64_t ans = mx - A[0];

    for (auto &a : A)
    {
        a = mx - a;
    }

    for (int64_t i = N - 1; i >= 0; --i)
    {
        int64_t val = i + 1;

        if (A[i] <= 0)
        {
            continue;
        }

        int64_t num = A[i];

        std::vector<int64_t> divisor;

        for (int64_t d = 1; d * d <= val; ++d)
        {
            if (val % d == 0)
            {
                divisor.push_back(d);
                if (d * d != val)
                {
                    divisor.push_back(val / d);
                }
            }
        }

        for (auto d : divisor)
        {
            A[d - 1] -= num;
        }
    }

    for (auto a : A)
    {
        if (a != 0)
        {
            Out() << -1;
            return;
        }
    }

    Out() << ans;

    return;
}

#endif //___INCLUDED_MAIN___