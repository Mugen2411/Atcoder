#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"
#include <algorithm>
#include <vector>

void AtcoderSolveHelper::Solve()
{
    int64_t N, Q;
    In() >> N >> Q;
    std::vector<int64_t> P(N);
    EachInput(P);
    std::vector<int64_t> order(N);
    for (int i = 0; i < N; ++i)
    {
        order[P[i] - 1] = i + 1;
    }

    while (Q--)
    {
        int cmd;
        In() >> cmd;
        if (cmd == 1)
        {
            int64_t x, y;
            In() >> x >> y;
            --x, --y;

            std::swap(order[P[x] - 1], order[P[y] - 1]);
            std::swap(P[x], P[y]);
        }
        else
        {
            std::swap(P, order);
        }
    }
    for (auto p : P)
    {
        Out() << p << " ";
    }
    return;
}

#endif //___INCLUDED_MAIN___