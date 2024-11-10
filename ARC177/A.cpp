#include <iostream>
#include <vector>
#include <array>

int main()
{
    std::array<int, 6> value{1, 5, 10, 50, 100, 500};
    std::array<int, 6> has;
    std::cin >> has[0] >> has[1] >> has[2] >> has[3] >> has[4] >> has[5];
    int N;
    std::cin >> N;
    std::vector<int> X(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> X[i];
    }
    std::vector<std::array<int, 6>> required;
    for (int i = 0; i < N; ++i)
    {
        std::array<int, 6> tmp{0};
        int v = 5;
        while (X[i] != 0)
        {
            if (X[i] >= value[v])
            {
                X[i] -= value[v];
                ++tmp[v];
            }
            else
            {
                --v;
            }
        }
        required.push_back(tmp);
    }
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            has[i] -= required[j][i];
        }
    }
    for (int i = 0; i < 6; ++i)
    {
        if (has[i] < 0)
        {
            std::cout << "No" << std::endl;
            return 0;
        }
        if (i != 5)
        {
            while (has[i] >= value[i + 1] / value[i])
            {
                has[i] -= value[i + 1] / value[i];
                ++has[i + 1];
            }
        }
    }
    std::cout << "Yes" << std::endl;
    return 0;
}