#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main()
{
    int H, W, K;
    std::cin >> H >> W >> K;
    std::vector<std::string> S(H);
    for (int y = 0; y < H; ++y)
    {
        std::cin >> S[y];
    }

    long long ans = 0;

    auto idx = [&](int x, int y)
    {
        return y * W + x;
    };
    auto dfs = [&](auto self, std::vector<int> root, int curX, int curY, int dist)
    {
        if (dist == K)
        {
            ++ans;
            return;
        }
        root.push_back(-1);
        if (curX > 0 && S[curY][curX - 1] != '#')
        {
            int next = idx(curX - 1, curY);
            if (root.end() == std::find(root.begin(), root.end(), next))
            {
                root.back() = next;
                self(self, root, curX - 1, curY, dist + 1);
            }
        }
        if (curX < W - 1 && S[curY][curX + 1] != '#')
        {
            int next = idx(curX + 1, curY);
            if (root.end() == std::find(root.begin(), root.end(), next))
            {
                root.back() = next;
                self(self, root, curX + 1, curY, dist + 1);
            }
        }
        if (curY > 0 && S[curY - 1][curX] != '#')
        {
            int next = idx(curX, curY - 1);
            if (root.end() == std::find(root.begin(), root.end(), next))
            {
                root.back() = next;
                self(self, root, curX, curY - 1, dist + 1);
            }
        }
        if (curY < H - 1 && S[curY + 1][curX] != '#')
        {
            int next = idx(curX, curY + 1);
            if (root.end() == std::find(root.begin(), root.end(), next))
            {
                root.back() = next;
                self(self, root, curX, curY + 1, dist + 1);
            }
        }
    };

    for (int y = 0; y < H; ++y)
    {
        for (int x = 0; x < W; ++x)
        {
            if (S[y][x] == '#')
            {
                continue;
            }
            dfs(dfs, std::vector<int>(1, idx(x, y)), x, y, 0);
        }
    }

    std::cout << ans;
}