#include <iostream>
#include <set>
#include <vector>

int main()
{
    int64_t N, Q;
    std::cin >> N >> Q;
    std::set<std::pair<int64_t, int64_t>> parentSet;
    std::vector<int64_t> colorCntMap(N + 1);

    for (int i = 0; i < N; ++i)
    {
        parentSet.insert({i, i});
        colorCntMap[i] = 1;
    }
    parentSet.insert({-1, 2e9});
    parentSet.insert({N, 2e9});

    while (Q--)
    {
        int cmd;
        std::cin >> cmd;
        switch (cmd)
        {
        case 1:
        {
            int64_t x, c;
            std::cin >> x >> c;
            --x, --c;
            auto itr = parentSet.upper_bound({x, 2e9});

            // 右・中・左のインデックスと色番号をバラす
            auto [r, rColor] = *itr;
            auto [m, mColor] = *--itr;
            auto [l, lColor] = *--itr;

            // 今見ている領域のサイズ
            int64_t size = (r - m);

            // 色の塗られているマスの数を更新
            colorCntMap[mColor] -= size;
            colorCntMap[c] += size;

            // イテレータを左から真ん中に戻す
            ++itr;
            // とりあえず真ん中は色が変わったので削除して刺しなおす
            itr = parentSet.erase(itr);

            // 右との境界を消す場合
            if (rColor == c)
            {
                itr = parentSet.erase(itr);
            }
            // 左との境界を消す場合
            if (lColor == c)
            {
                // 真ん中は消しっぱでおｋ
            }
            else
            {
                // 真ん中の色変えた奴を指しなおす
                parentSet.insert(itr, {m, c});
            }
        }
        break;
        case 2:
        {
            int64_t c;
            std::cin >> c;
            --c;
            std::cout << colorCntMap[c] << std::endl;
        }
        break;
        }
    }
}