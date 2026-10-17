#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/BitManager.cpp"
#include "../module/Helper.cpp"
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

void AtcoderSolveHelper::Solve()
{
    int64_t N, W;
    In() >> N >> W;
    struct FOOD
    {
        int64_t A, B;
    };
    std::vector<FOOD> fd(N);
    for (auto &&f : fd)
    {
        In() >> f.A >> f.B;
    }

    int64_t ans = 0;
    for (BitManager bm = BitManager::AllFalse(); bm != BitManager::Onehot(N); ++bm)
    {
        int64_t eval = 0;
        int64_t volume = 0;

        for (int i = 0; i < N; ++i)
        {
            if (bm.Get(i))
            {
                eval += fd[i].A;
                volume += fd[i].B;
            }
        }

        if (volume <= W)
        {
            ans = std::max<int64_t>(ans, eval);
        }
    }

    Out() << ans;
    return;
}

#endif //___INCLUDED_MAIN___