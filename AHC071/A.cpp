#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Grid2D.cpp"
#include "../module/Helper.cpp"
#include <algorithm>
#include <chrono>
#include <functional>
#include <queue>
#include <random>
#include <stack>
#include <unordered_map>
#include <vector>

void AtcoderSolveHelper::Solve()
{
    auto startTime = std::chrono::system_clock::now();

    int64_t W, H, K;
    In() >> W >> H >> K;
    std::vector<int64_t> c(5);
    EachInput(c);
    std::vector<int64_t> length({1, 3, 5, 7, 9});
    std::vector<int64_t> order({0, 1, 2, 3, 4});
    std::vector<std::function<void(std::vector<int64_t> &)>> GetPivotFunc;
    for (auto l : length)
    {
        GetPivotFunc.push_back([l](std::vector<int64_t> &out) { out.push_back(l / 2); });
    }
    std::random_device seedGen;
    std::mt19937 rnd(seedGen());

    Grid2D<char> Wall(H, W, '#');
    for (int i = 0; i < K; ++i)
    {
        int64_t a, b;
        In() >> a >> b;
        Wall.Ref(a, b) = '.';
    }

    struct BRICK
    {
        int64_t x, y, l;
    };
    std::vector<BRICK> ans;
    int64_t ansScore = W * H * c[0];

    while (1)
    {
        std::vector<BRICK> tmp;
        Grid2D<char> CurWall(Wall);
        int64_t curScore = 0;
        for (int64_t y = H - 1; y > 0; --y)
        {
            for (int64_t x = 0; x < W; ++x)
            {
                if (CurWall.Ref(x, y) != '.')
                {
                    continue;
                }
                std::vector<int64_t> score(length.size(), 0);
                int64_t mx = 0;
                // 出来るだけ長いレンガを用いて一気に覆うことを考える
                for (int i = 0; i < length.size(); ++i)
                {
                    if (x + length[i] > W)
                    {
                        continue;
                    }
                    for (int j = 0; j < length[i]; ++j)
                    {
                        if (CurWall.Ref(x + j, y) == '.')
                        {
                            mx = std::max<int64_t>(mx, ++score[i]);
                        }
                    }
                }
                if (mx == 0)
                {
                    continue;
                }

                // コストが同じレンガをシャッフルして上振れ引きたい
                std::shuffle(order.begin(), order.end(), rnd);
                std::stable_sort(order.begin(), order.end(), [&](int64_t lhs, int64_t rhs) { return c[lhs] < c[rhs]; });
                // 使うべきレンガを使ったことをシミュレーションする
                for (auto i : order)
                {
                    if (score[i] == mx)
                    {
                        curScore += c[i];
                        tmp.push_back(BRICK{.x = x, .y = y, .l = length[i]});
                        for (int j = 0; j < length[i]; ++j)
                        {
                            CurWall.Ref(x + j, y) = '_';
                        }
                        if (y != 0)
                        {
                            // 支えるべき場所を穴とする
                            std::vector<int64_t> pivot;
                            GetPivotFunc[i](pivot);
                            for (auto p : pivot)
                            {
                                CurWall.Ref(x + p, y - 1) = '.';
                            }
                        }
                        CurWall.Ref(x, y) = i + '0';
                        break;
                    }
                }
            }
        }

        // 最下段はつなげるインセンティブが無いので1ずつを検討する
        for (int64_t x = 0; x < W; ++x)
        {
            if (CurWall.Ref(x, 0) != '.')
            {
                continue;
            }
            std::vector<int64_t> score(length.size(), 0);
            int64_t mx = 0;
            // 出来るだけ長いレンガを用いて一気に覆うことを考える
            for (int i = 0; i < length.size(); ++i)
            {
                if (x + length[i] > W)
                {
                    continue;
                }
                for (int j = 0; j < length[i]; ++j)
                {
                    if (CurWall.Ref(x + j, 0) == '.')
                    {
                        mx = std::max<int64_t>(mx, ++score[i]);
                    }
                }
            }
            if (mx == 0)
            {
                continue;
            }
            // コストが同じならでかい方がお得
            std::stable_sort(order.begin(), order.end(), [&](int64_t lhs, int64_t rhs) {
                if (c[lhs] < c[rhs])
                {
                    return true;
                }
                if (c[lhs] > c[rhs])
                {
                    return true;
                }
                return length[lhs] < length[rhs];
            });
            // 使うべきレンガを使ったことをシミュレーションする
            for (auto i : order)
            {
                if (score[i] == mx)
                {
                    // もし1つずつ覆った方が安いならそれでよい
                    if (c[i] > c[0] * score[i])
                    {
                        for (int j = 0; j < length[i]; ++j)
                        {
                            if (CurWall.Ref(x + j, 0) == '.')
                            {
                                curScore += c[0];
                                tmp.push_back(BRICK{.x = x + j, .y = 0, .l = length[0]});
                                CurWall.Ref(x + j, 0) = '0';
                            }
                        }
                        break;
                    }
                    curScore += c[i];
                    tmp.push_back(BRICK{.x = x, .y = 0, .l = length[i]});
                    for (int j = 0; j < length[i]; ++j)
                    {
                        CurWall.Ref(x + j, 0) = '_';
                    }
                    CurWall.Ref(x, 0) = i + '0';
                    break;
                }
            }
        }

        if (ansScore > curScore)
        {
            ansScore = curScore;
            std::swap(ans, tmp);
            tmp.clear();
        }

        auto endTime = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        if (elapsed > 1950)
        {
            break;
        }
    }

    // 以下解答出力
    Out() << ans.size() << std::endl;
    for (auto &b : ans)
    {
        Out() << b.x << " " << b.y << " " << b.l << std::endl;
    }

    return;
}

#endif //___INCLUDED_MAIN___