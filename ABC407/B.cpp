#include <iostream>
#include <iomanip>

int main()
{
    int X, Y;
    std::cin >> X >> Y;
    int ans = 0;
    for (int d1 = 1; d1 <= 6; ++d1)
    {
        for (int d2 = 1; d2 <= 6; ++d2)
        {
            if (X <= d1 + d2 || Y <= std::abs(d1 - d2))
            {
                ++ans;
            }
        }
    }
    std::cout << std::setprecision(10) << double(ans) / 36.0;
    return 0;
}