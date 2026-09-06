#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

void AtcoderSolveHelper::Solve()
{
    int64_t X;
    In() >> X;

    if (X == 0)
    {
        Out() << "ATCODER";
        return;
    }

    int64_t sqX = [X]() {
        int64_t ans = std::sqrt(X);
        if (ans * ans != X)
        {
            ++ans;
        }
        return ans;
    }();

    int64_t diff = sqX * sqX - X; // この分だけ最適から崩す
    int64_t pass = diff / sqX;
    diff -= pass * sqX;

    std::string ans;
    for (int i = 0; i < pass; ++i)
    {
        ans.push_back('C');
    }
    for (int i = 0; i < sqX; ++i)
    {
        ans.push_back('A');
    }
    for (int i = pass; i < sqX; ++i)
    {
        ans.push_back('C');
    }

    if (diff != 0)
    {
        std::swap(ans[sqX + pass], ans[sqX + pass - diff]);
    }

    Out() << ans[0];
    for (int i = 1; i < ans.size(); ++i)
    {
        Out() << "R" << ans[i];
    }

    return;
}

#endif //___INCLUDED_MAIN___