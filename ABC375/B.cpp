#include <iostream>
#include <cmath>
#include <iomanip>

int main()
{
    long double ans = 0.0;
    size_t N;
    std::cin >> N;
    int64_t curX = 0, curY = 0;
    while (N--)
    {
        int64_t X, Y;
        std::cin >> X >> Y;
        ans += std::sqrt((X - curX) * (X - curX) + (Y - curY) * (Y - curY));
        curX = X;
        curY = Y;
    }
    ans += std::sqrt((0 - curX) * (0 - curX) + (0 - curY) * (0 - curY));
    std::cout << std::fixed << std::setprecision(10) << ans;
    return 0;
}