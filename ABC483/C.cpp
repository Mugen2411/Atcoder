#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"
#include <algorithm>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <vector>

void AtcoderSolveHelper::Solve()
{
    int64_t N, M;
    In() >> N >> M;

    std::vector<std::vector<int64_t>> OnCanceled(N);
    std::unordered_map<int64_t, int64_t> got;
    std::map<int64_t, std::set<int64_t>> order;

    for (int i = 0; i < N; ++i)
    {
        order[0].insert(i);
    }

    for (int i = 0; i < M; ++i)
    {
        int64_t A, B;
        In() >> A >> B;
        --A, --B;

        OnCanceled[A].push_back(B);
        ++got[A];
        order[-got[A] + 1].erase(A);
        order[-got[A]].insert(A);
    }

    for (int i = 0; i < N; ++i)
    {
        for (auto &c : OnCanceled[i])
        {
            order[-got[i]].erase(i);
            if (order[-got[i]].size() == 0)
            {
                order.erase(-got[i]);
            }
            --got[i];
            order[-got[i]].insert(i);

            order[-got[c]].erase(i);
            if (order[-got[c]].size() == 0)
            {
                order.erase(-got[c]);
            }
            ++got[c];
            order[-got[c]].insert(c);
        }

        Out() << 1 + *order.begin()->second.begin() << std::endl;

        for (auto &c : OnCanceled[i])
        {
            order[-got[i]].erase(i);
            if (order[-got[i]].size() == 0)
            {
                order.erase(-got[i]);
            }
            ++got[i];
            order[-got[i]].insert(i);

            order[-got[c]].erase(c);
            if (order[-got[c]].size() == 0)
            {
                order.erase(-got[c]);
            }
            --got[c];
            order[-got[c]].insert(c);
        }
    }
    return;
}

#endif //___INCLUDED_MAIN___