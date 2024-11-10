#include <iostream>
#include <string>
#include <vector>

int main()
{
    int64_t N;
    std::cin >> N;
    std::vector<std::string> A(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A[i];
    }

    std::vector<std::string> ans(N);
    for (auto &s : ans)
    {
        s.resize(N);
    }

    for (int64_t y = 0; y < N; ++y)
    {
        for (int64_t x = 0; x < N; ++x)
        {
            int64_t repX = std::min(N - x - 1, x);
            int64_t repY = std::min(N - y - 1, y);
            int64_t rep = std::min(repX, repY) % 4 + 1;
            int64_t curX = x;
            int64_t curY = y;
            while (rep--)
            {
                int64_t tmpX = curY;
                int64_t tmpY = N - curX - 1;
                curY = tmpY;
                curX = tmpX;
            }
            ans[y][x] = A[curY][curX];
        }
    }

    for (auto &s : ans)
    {
        for (auto &c : s)
        {
            std::cout << c;
        }
        std::cout << std::endl;
    }
    return 0;
}