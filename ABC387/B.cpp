#include <iostream>

int main()
{
    int X;
    std::cin >> X;
    int ans = 0;
    for (int i = 1; i <= 9; ++i)
    {
        for (int j = 1; j <= 9; ++j)
        {
            if (i * j != X)
            {
                ans += i * j;
            }
        }
    }
    std::cout << ans;
    return 0;
}