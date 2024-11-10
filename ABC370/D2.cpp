#include <iostream>
#include <vector>

#define INVALID 900000
int main()
{
    size_t H, W, Q;
    std::cin >> H >> W >> Q;

    int64_t numWall = H * W;

    std::vector<std::vector<int64_t>> uTable;
    std::vector<std::vector<int64_t>> dTable;
    std::vector<std::vector<int64_t>> lTable;
    std::vector<std::vector<int64_t>> rTable;
    std::vector<std::vector<int64_t>> grid;

    uTable.resize(H + 2);
    dTable.resize(H + 2);
    lTable.resize(H + 2);
    rTable.resize(H + 2);
    grid.resize(H + 2);

    for (int y = 0; y < H + 2; ++y)
    {
        uTable[y].resize(W + 2, 0);
        dTable[y].resize(W + 2, 0);
        lTable[y].resize(W + 2, 0);
        rTable[y].resize(W + 2, 0);
        grid[y].resize(W + 2, 1);
    }

    auto bomb = [&](int64_t r, int64_t c)
    {
        {
            auto f = [&](auto self, int64_t cur) -> int64_t
            {
                if (grid[cur][c] != 0)
                {
                    return 0;
                }
                return uTable[cur][c] = self(self, cur - 1) + 1;
            };
            f(f, r);
        }
        {
            auto f = [&](auto self, int64_t cur) -> int64_t
            {
                if (grid[cur][c] != 0)
                {
                    return 0;
                }
                return dTable[cur][c] = self(self, cur + 1) + 1;
            };
            f(f, r);
        }
        {
            auto f = [&](auto self, int64_t cur) -> int64_t
            {
                if (grid[r][cur] != 0)
                {
                    return 0;
                }
                return lTable[r][cur] = self(self, cur - 1) + 1;
            };
            f(f, c);
        }
        {
            auto f = [&](auto self, int64_t cur) -> int64_t
            {
                if (grid[r][cur] != 0)
                {
                    return 0;
                }
                return rTable[r][cur] = self(self, cur + 1) + 1;
            };
            f(f, c);
        }
    };
    auto update = [&](int64_t r, int64_t c)
    {
        if (grid[r][c])
        {
            grid[r][c] = 0;
            bomb(r, c);
            --numWall;
            return;
        }
        // up
        {
            int64_t U = r - uTable[r][c];
            while (!grid[U][c])
            {
                U -= uTable[U][c];
            }

            if (U < 1)
            {
            }
            else if (grid[U][c])
            {
                grid[U][c] = 0;
                bomb(U, c);
                --numWall;
            }
        }

        // down
        {
            int64_t D = r + dTable[r][c];
            while (!grid[D][c])
            {
                D += dTable[D][c];
            }

            if (D > H)
            {
            }
            else if (grid[D][c])
            {
                grid[D][c] = 0;
                bomb(D, c);
                --numWall;
            }
        }

        // left
        {
            int64_t L = c - lTable[r][c];
            while (!grid[r][L])
            {
                L -= lTable[r][L];
            }

            if (L < 1)
            {
            }
            else if (grid[r][L])
            {
                grid[r][L] = 0;
                bomb(r, L);
                --numWall;
            }
        }

        // right
        {
            int64_t R = c + rTable[r][c];
            while (!grid[r][R])
            {
                R += rTable[r][R];
            }

            if (R > W)
            {
            }
            else if (grid[r][R])
            {
                grid[r][R] = 0;
                bomb(r, R);
                --numWall;
            }
        }
    };

    while (Q--)
    {
        int64_t R, C;
        std::cin >> R >> C;

        update(R, C);

        /*std::cerr << std::endl;
        for (int y = 1; y <= H; ++y)
        {
            for (int x = 1; x <= W; ++x)
            {
                std::cerr << grid[y][x] << " ";
            }
            std::cerr << std::endl;
        }*/
    }
    std::cout << numWall;
}