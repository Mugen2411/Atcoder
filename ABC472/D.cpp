#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

#include "../module/Grid2D.cpp"

void AtcoderSolveHelper::Solve()
{
    int64_t H, W, K;
    In() >> H >> W >> K;
    Grid2D<char> S(H, W, 0);
    In() >> S;

    std::queue<Grid2D<char>::Iterator> safe;
    std::queue<int64_t> dist;
    std::vector<int64_t> numY(W);
    std::vector<int64_t> numX(H);

    S.ForEach([&](int64_t idx, char val) {
        if (val == '#')
        {
            ++numY[S.GetX(idx)];
            ++numX[S.GetY(idx)];
        }
    });
    for (int64_t y = 0; y < H; ++y)
    {
        for (int64_t x = 0; x < W; ++x)
        {
            if (numY[x] == 0 && numX[y] == 0)
            {
                safe.push(S.GetItr(x, y));
                dist.push(0);
            }
        }
    }

    int64_t ans = 0;
    while (!safe.empty())
    {
        auto curItr = safe.front();
        safe.pop();

        auto d = dist.front();
        dist.pop();

        if (d > K)
        {
            continue;
        }

        if (*curItr != '.')
        {
            continue;
        }

        ++ans;
        *curItr = '_';

        for (auto dir : POSITION::GetDirectionChars())
        {
            auto nextItr = curItr + POSITION::RLDU(dir);
            if (nextItr.IsInner() && *nextItr == '.')
            {
                safe.push(nextItr);
                dist.push(d + 1);
            }
        }
    }

    Out() << ans;

    return;
}

#endif //___INCLUDED_MAIN___