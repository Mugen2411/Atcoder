#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"
#include <set>
#include <vector>

void AtcoderSolveHelper::Solve()
{
    int64_t N, Q;
    In() >> N >> Q;
    std::vector<int64_t> A(N, 0);
    int64_t ans = 0;
    std::set<int64_t> removable;

    while (Q--)
    {
        int cmd;
        In() >> cmd;
        if (cmd == 1)
        {
            int64_t x;
            In() >> x;
            --x;
            ans ^= A[x];
            ++A[x];
            ans ^= A[x];
            removable.insert(x);
        }
        else
        {
            for (auto itr = removable.begin(); itr != removable.end();)
            {
                ans ^= A[*itr];
                --A[*itr];
                ans ^= A[*itr];
                if (A[*itr] == 0)
                {
                    itr = removable.erase(itr);
                }
                else
                {
                    ++itr;
                }
            }
        }
        Out() << ans << std::endl;
    }
    return;
}

#endif //___INCLUDED_MAIN___