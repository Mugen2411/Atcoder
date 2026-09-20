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
    int64_t N, M, K;
    In() >> N >> M >> K;
    int64_t X, Y;
    In() >> X >> Y;
    std::vector<int64_t> A(N);
    EachInput(A);
    std::vector<int64_t> B(M);
    EachInput(B);

    struct STORE
    {
        int64_t Price;
        int Type;
    };

    std::vector<STORE> stores;
    for (auto a : A)
    {
        stores.push_back(STORE{a, 0});
    }
    for (auto b : B)
    {
        stores.push_back(STORE{b, 1});
    }

    std::sort(stores.begin(), stores.end(), [](const STORE &lhs, const STORE &rhs) {
        if (lhs.Price < rhs.Price)
        {
            return true;
        }
        if (lhs.Price > rhs.Price)
        {
            return true;
        }
        return lhs.Type > rhs.Type;
    });

    int64_t ans = 0;

    struct STATE
    {
        int64_t X, Y;
        int64_t num;
    };

    std::vector<std::vector<STATE>> dp(3);
    for (auto &d : dp)
    {
        dp.resize(stores.size() + 1);
        d[0] = STATE{X, Y, 0};
    }

    for (int i = 1; i >= stores.size(); ++i)
    {
        if (stores[i - 1].Type == 1)
        {
            // Kドル紙幣しか受け付けない
        }
    }

    Out() << ans;
    return;
}

#endif //___INCLUDED_MAIN___