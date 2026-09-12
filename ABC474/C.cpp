#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

void AtcoderSolveHelper::Solve()
{
    int64_t N, Q;
    In() >> N >> Q;
    std::vector<int64_t> P(N);
    EachInput(P);
    std::list<int64_t> Pl;
    std::vector<std::list<int64_t>::iterator> vitr(N);
    for (auto &p : P)
    {
        --p;
        Pl.push_back(p);
        vitr[p] = --Pl.end();
    }

    while (Q--)
    {
        int64_t a;
        In() >> a;
        --a;

        Pl.splice(Pl.end(), Pl, vitr[a]);
    }

    for (auto p : Pl)
    {
        Out() << p + 1 << " ";
    }

    return;
}

#endif //___INCLUDED_MAIN___