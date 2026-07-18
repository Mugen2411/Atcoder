#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/BitManager.cpp"
#include "../module/Grid2D.cpp"
#include "../module/Helper.cpp"
#include <algorithm>
#include <vector>

void AtcoderSolveHelper::Solve()
{
    int64_t N, H, W;
    In() >> N >> H >> W;
    struct RECT
    {
        int64_t H, W;
    };
    std::vector<RECT> rect(N);
    for (auto &&r : rect)
    {
        In() >> r.H >> r.W;
    }

    std::vector<int> order(N);
    for (int i = 0; i < N; ++i)
    {
        order[i] = i;
    }

    do
    {
        for (BitManager b = BitManager::AllFalse(); b != BitManager::Onehot(N); ++b)
        {
            Grid2D<int> filled(H, W, 0);

            auto _GetTop = [&]() {
                for (int i = 0; i < H * W; ++i)
                {
                    if (filled.Get(filled.GetX(i), filled.GetY(i)) == 0)
                    {
                        return i;
                    }
                }
                return -1;
            };

            bool isAns = true;
            for (int i = 0; i < N; ++i)
            {
                int64_t topIdx = _GetTop();
                if (topIdx < 0)
                {
                    break;
                }
                int64_t topX = topIdx % W;
                int64_t topY = topIdx / W;

                int64_t tgtW = b.Get(i) ? rect[order[i]].H : rect[order[i]].W;
                int64_t tgtH = b.Get(i) ? rect[order[i]].W : rect[order[i]].H;

                if (topX + tgtW > W || topY + tgtH > H)
                {
                    isAns = false;
                    break;
                }

                for (int y = 0; y < tgtH; ++y)
                {
                    for (int x = 0; x < tgtW; ++x)
                    {
                        if (filled.Get(topX + x, topY + y))
                        {
                            isAns = false;
                            break;
                        }
                        filled.Ref(topX + x, topY + y) = 1;
                    }
                }
            }

            if (isAns && _GetTop() < 0)
            {
                Yes();
                return;
            }
        }
    } while (std::next_permutation(order.begin(), order.end()));

    No();
    return;
}

#endif //___INCLUDED_MAIN___