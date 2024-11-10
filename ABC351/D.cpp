#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <stack>

int main()
{
    int H, W;
    std::cin >> H >> W;
    std::vector<std::string> S(H);
    std::vector<int> checked(H * W, -1);
    auto CalcIndex = [&](int x, int y) -> int
    {
        return y * W + x;
    };

    auto CountMagnet = [&](int x, int y) -> int
    {
        int numMugnet = 0;
        if (y > 0 && S[y - 1][x] == '#')
        {
            ++numMugnet;
        }
        if (y < H - 1 && S[y + 1][x] == '#')
        {
            ++numMugnet;
        }
        if (x > 0 && S[y][x - 1] == '#')
        {
            ++numMugnet;
        }
        if (x < W - 1 && S[y][x + 1] == '#')
        {
            ++numMugnet;
        }
        return numMugnet;
    };
    for (int y = 0; y < H; ++y)
    {
        std::cin >> S[y];
    }
    int ans = 0;
    for (int y = 0; y < H; ++y)
    {
        for (int x = 0; x < W; ++x)
        {
            if (S[y][x] == '#')
            {
                continue;
            }

            if (CountMagnet(x, y) == 0 && checked[CalcIndex(x, y)] != -1)
            {
                continue;
            }
            std::stack<std::array<int, 3>> st;
            st.push({x, y, 1});
            int idx = CalcIndex(x, y);
            int dist = 0;
            checked[CalcIndex(x, y)] = idx;
            while (!st.empty())
            {
                int tx, ty, td;
                auto ta = st.top();
                st.pop();
                tx = ta[0];
                ty = ta[1];
                td = ta[2];
                ++dist;

                // std::cout << "idx:" << idx << " x:" << tx << " y:" << ty << std::endl;

                if (CountMagnet(tx, ty) != 0)
                {
                    continue;
                }
                if (ty > 0 && S[ty - 1][tx] == '.' && checked[CalcIndex(tx, ty - 1)] != idx)
                {
                    st.push({tx, ty - 1, td + 1});
                    checked[CalcIndex(tx, ty - 1)] = idx;
                }
                if (ty < H - 1 && S[ty + 1][tx] == '.' && checked[CalcIndex(tx, ty + 1)] != idx)
                {
                    st.push({tx, ty + 1, td + 1});
                    checked[CalcIndex(tx, ty + 1)] = idx;
                }
                if (tx > 0 && S[ty][tx - 1] == '.' && checked[CalcIndex(tx - 1, ty)] != idx)
                {
                    st.push({tx - 1, ty, td + 1});
                    checked[CalcIndex(tx - 1, ty)] = idx;
                }
                if (tx < W - 1 && S[ty][x + 1] == '.' && checked[CalcIndex(tx + 1, ty)] != idx)
                {
                    st.push({tx + 1, ty, td + 1});
                    checked[CalcIndex(tx + 1, ty)] = idx;
                }
            }
            if (dist > ans)
            {
                ans = dist;
            }
        }
    }
    std::cout << ans;

    return 0;
}