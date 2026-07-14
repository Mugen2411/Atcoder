#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Grid2D.cpp"
#include "../module/Helper.cpp"

void AtcoderSolveHelper::Solve()
{
    int64_t H, W;
    In() >> H >> W;
    Grid2D<char> S(H, W, '.');
    In() >> S;
    Grid2D<char> init(S);

    Grid2D<int> searched(H, W, 0);

    auto q = S.GetPositionsQueueByValue('#');

    // 2手目で黒に戻れないやつを白にする
    while (!q.empty())
    {
        auto curPos = q.front();
        q.pop();

        int64_t numBlack = 0;
        int64_t numValid = 0;

        for (char dir : POSITION::GetTenkeyChars())
        {
            auto nextPos = curPos + POSITION::Tenkey(dir);
            if (nextPos.IsInner())
            {
                ++numValid;
                if (*init.GetItr(nextPos.GetIndex()) == '#')
                {
                    ++numBlack;
                }
            }
        }

        if (numBlack == numValid)
        {
            *curPos = '.';
        }
    }

    // 生き残った黒を起点に偶数手目で黒になるマスを検出
    q = S.GetPositionsQueueByValue('#');

    std::queue<int64_t> distQ;
    for (int i = 0; i < q.size(); ++i)
    {
        distQ.push(0);
    }

    while (!q.empty())
    {
        auto curPos = q.front();
        q.pop();
        auto dist = distQ.front();
        distQ.pop();

        if (*searched.GetItr(curPos.GetIndex()) != 0)
        {
            continue;
        }

        *searched.GetItr(curPos.GetIndex()) = 1;
        if (dist % 2 == 0)
        {
            *curPos = '#';
        }

        for (char dir : POSITION::GetTenkeyChars())
        {
            auto nextPos = curPos + POSITION::Tenkey(dir);
            if (nextPos.IsInner() && *searched.GetItr(nextPos.GetIndex()) == 0)
            {
                q.push(nextPos);
                distQ.push(dist + 1);
            }
        }
    }

    for (int y = 0; y < S.GetHeight(); ++y)
    {
        for (int x = 0; x < S.GetWidth(); ++x)
        {
            Out() << S.Ref(x, y);
        }
        Out() << std::endl;
    }
}

#endif //___INCLUDED_MAIN___