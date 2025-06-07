#include <iostream>
#include <unordered_set>
#include <vector>

int main()
{
    int H, W;
    std::cin >> H >> W;
    std::vector<int64_t> A(H * W);
    for (auto &&a : A)
    {
        std::cin >> a;
    }

    auto Write = [W](uint32_t base, int x, int y) -> uint32_t
    {
        return base | (1 << (y * W + x));
    };
    auto Read = [W](uint32_t base, int x, int y) -> bool
    {
        return 1 & (base >> (y * W + x));
    };
    auto isInner = [H, W](int x, int y)
    {
        return 0 <= y && y < H && 0 <= x && x < W;
    };
    std::unordered_set<uint32_t> pattern;
    pattern.insert(0);

    for (int y = 0; y < H; ++y)
    {
        for (int x = 0; x < W; ++x)
        {
            std::vector<uint32_t> addRange;

            for (auto p : pattern)
            {
                if (isInner(x + 1, y) && !Read(p, x, y) && !Read(p, x + 1, y))
                {
                    uint32_t res = p;
                    res = Write(res, x, y);
                    res = Write(res, x + 1, y);
                    addRange.push_back(res);
                }
                if (isInner(x, y + 1) && !Read(p, x, y) && !Read(p, x, y + 1))
                {
                    uint32_t res = p;
                    res = Write(res, x, y);
                    res = Write(res, x, y + 1);
                    addRange.push_back(res);
                }
                if (isInner(x - 1, y) && !Read(p, x, y) && !Read(p, x - 1, y))
                {
                    uint32_t res = p;
                    res = Write(res, x, y);
                    res = Write(res, x - 1, y);
                    addRange.push_back(res);
                }
                if (isInner(x, y - 1) && !Read(p, x, y) && !Read(p, x, y - 1))
                {
                    uint32_t res = p;
                    res = Write(res, x, y);
                    res = Write(res, x, y - 1);
                    addRange.push_back(res);
                }
            }
            for (auto r : addRange)
            {
                pattern.insert(r);
            }
        }
    }

    uint64_t ans = 0;
    for (auto p : pattern)
    {
        uint64_t tmp = 0;
        for (int d = 0; d < H * W; ++d)
        {
            if ((1 & (p >> d)) == 0)
            {
                tmp ^= A[d];
            }
        }
        ans = std::max(ans, tmp);
    }
    std::cout << ans;
    return 0;
}