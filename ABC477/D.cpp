#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"
#include <algorithm>
#include <bitset>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void AtcoderSolveHelper::Solve()
{
    int64_t N, Q;
    In() >> N >> Q;

    struct QUERY
    {
        int Type;
        char C;
        int X;
    };

    std::vector<QUERY> q;
    std::unordered_set<int> cur;
    for (int i = 0; i < N; ++i)
    {
        cur.insert(i);
    }

    while (Q--)
    {
        int cmd;
        In() >> cmd;

        if (cmd == 1)
        {
            int X;
            In() >> X;
            --X;
            if (cur.count(X))
            {
                cur.erase(X);
            }
            else
            {
                cur.insert(X);
            }
            q.push_back(QUERY{.Type = 1, .X = X});
        }
        else
        {
            char C;
            In() >> C;
            q.push_back(QUERY{.Type = 2, .C = C});
        }
    }

    std::unordered_set<int> pos;
    for (int i = 0; i < N; ++i)
    {
        pos.insert(i);
    }

    std::reverse(q.begin(), q.end());

    std::string ans(N, 'a');
    for (auto &cq : q)
    {
        if (cq.Type == 1)
        {
            if (cur.count(cq.X))
            {
                cur.erase(cq.X);
            }
            else
            {
                if (pos.count(cq.X))
                {
                    cur.insert(cq.X);
                }
            }
        }
        else
        {
            std::unordered_set<int> rem;
            for (auto p : cur)
            {
                rem.insert(p);
                ans[p] = cq.C;
            }
            for (auto r : rem)
            {
                pos.erase(r);
                cur.erase(r);
            }
        }
    }
    Out() << ans;
    return;
}

#endif //___INCLUDED_MAIN___