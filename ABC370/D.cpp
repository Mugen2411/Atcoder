#include <iostream>
#include <set>
#include <vector>

int main()
{
    size_t H, W, Q;
    std::cin >> H >> W >> Q;

    std::vector<std::set<size_t>> g1(H);
    std::vector<std::set<size_t>> g2(W);

    for (int64_t y = 0; y < H; ++y)
    {
        for (int64_t x = 0; x < W; ++x)
        {
            g1[y].insert(x);
            g2[x].insert(y);
        }
    }

    auto erase = [&](int64_t y, int64_t x)
    {
        g1[y].erase(x);
        g2[x].erase(y);
    };

    for (size_t q = 0; q < Q; ++q)
    {
        int64_t R, C;
        std::cin >> R >> C;
        --R;
        --C;
        if (g1[R].count(C))
        {
            erase(R, C);
            continue;
        }

        // up
        {
            auto itr = g2[C].lower_bound(R);
            if (itr != g2[C].begin())
            {
                erase(*--itr, C);
            }
        }

        // down
        {
            auto itr = g2[C].lower_bound(R);
            if (itr != g2[C].end())
            {
                erase(*itr, C);
            }
        }

        // left
        {
            auto itr = g1[R].lower_bound(C);
            if (itr != g1[R].begin())
            {
                erase(R, *--itr);
            }
        }

        // right
        {
            auto itr = g1[R].lower_bound(C);
            if (itr != g1[R].end())
            {
                erase(R, *itr);
            }
        }
    }

    size_t ans = 0;
    for (auto &r : g1)
    {
        ans += r.size();
    }

    std::cout << ans;
    return 0;
}