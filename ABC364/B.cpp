#include <iostream>
#include <vector>
#include <string>

int main()
{
    size_t W, H;
    std::cin >> H >> W;
    size_t Sx, Sy;
    std::cin >> Sy >> Sx;
    std::vector<std::vector<char>> map;
    map.resize(H + 1);
    for (auto &i : map)
    {
        i.resize(W + 1);
    }
    char tmp;
    for (int y = 0; y < H; ++y)
    {
        for (int x = 0; x < W; ++x)
        {
            std::cin >> map[y + 1][x + 1];
        }
    }
    size_t x = Sx;
    size_t y = Sy;
    std::string command;
    std::cin >> command;
    for (auto c : command)
    {
        switch (c)
        {
        case 'U':
        {
            if (y > 1 && map[y - 1][x] != '#')
            {
                y--;
            }
        }
        break;
        case 'D':
        {
            if (y < H && map[y + 1][x] != '#')
            {
                y++;
            }
        }
        break;
        case 'L':
        {
            if (x > 1 && map[y][x - 1] != '#')
            {
                x--;
            }
        }
        break;
        case 'R':
        {
            if (x < W && map[y][x + 1] != '#')
            {
                x++;
            }
        }
        break;
        }
    }
    std::cout << y << " " << x << std::endl;
    return 0;
}