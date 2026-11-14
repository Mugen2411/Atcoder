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
    struct CARD
    {
        int val;
        bool isFace;
    };

    int N, Q;
    In() >> N >> Q;
    std::stack<CARD> cd;
    for (int i = N; i > 0; --i)
    {
        cd.push(CARD{.val = i, .isFace = true});
    }

    while (Q--)
    {
        int K;
        In() >> K;

        std::queue<CARD> tmp;
        for (int i = 0; i < K; ++i)
        {
            tmp.push(cd.top());
            cd.pop();
        }

        for (int i = 0; i < K; ++i)
        {
            cd.push(CARD{.val = tmp.front().val, .isFace = !tmp.front().isFace});
            tmp.pop();
        }
    }

    while (!cd.empty())
    {
        Out() << cd.top().val * (cd.top().isFace ? 1 : -1) << std::endl;
        cd.pop();
    }

    return;
}

#endif //___INCLUDED_MAIN___