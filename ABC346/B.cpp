#include <iostream>
#include <string>
#include <array>
#include <vector>

int main()
{
    int W, B;
    std::cin >> W >> B;
    while (W >= 7 && B >= 5)
    {
        W -= 7;
        B -= 5;
    }
    std::string piano("wbwbwwbwbwbwwbwbwwbwbwbw");
    std::vector<std::array<int, 2>> chance;
    if (W + B > piano.size())
    {
        std::cout << "No";
        return 0;
    }
    for (int i = 0; i < piano.size() - (W + B); ++i)
    {
        int w = 0, b = 0;
        for (int j = 0; j < W + B; ++j)
        {
            if (piano[i + j] == 'w')
            {
                ++w;
            }
            else
            {
                ++b;
            }
        }
        chance.push_back({w, b});
    }
    for (const auto &i : chance)
    {
        if (i[0] == W && i[1] == B)
        {
            std::cout << "Yes";
            return 0;
        }
    }
    std::cout << "No";
    return 0;
}