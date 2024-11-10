#include <iostream>
#include <string>
#include <vector>
#include <array>

int main()
{
    int H, W, N;
    std::cin >> H >> W >> N;
    std::vector<std::string> S(H);
    std::string T;
    std::vector<std::array<int, 2>> landPos;

    std::cin >> T;
    for (int i = 0; i < H; ++i)
    {
        std::cin >> S[i];
    }
    for (int y = 0; y < H; ++y)
    {
        for (int x = 0; x < W; ++x)
        {
            if (S[y][x] == '.')
            {
                landPos.push_back({x, y});
            }
        }
    }
    int failed = 0;
    for (int i = 0; i < landPos.size(); ++i)
    {
        int tmpX = landPos[i][0];
        int tmpY = landPos[i][1];

        for (int j = 0; j < N; ++j)
        {
            switch (T[j])
            {
            case 'U':
                --tmpY;
                break;

            case 'D':
                ++tmpY;
                break;

            case 'R':
                ++tmpX;
                break;

            case 'L':
                --tmpX;
                break;
            }
            if (S[tmpY][tmpX] == '#' || tmpY < 0 || tmpX < 0 || tmpY >= H || tmpX >= W)
            {
                ++failed;
                break;
            }
        }
    }

    std::cout << landPos.size() - failed;
    return 0;
}