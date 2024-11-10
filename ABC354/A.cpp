#include <iostream>

int main()
{
    size_t H;
    std::cin >> H;
    size_t ans = 0;
    size_t h = 0;
    size_t t = 1;
    while (h <= H)
    {
        h += t;
        t *= 2;
        ++ans;
    }
    std::cout << ans << std::endl;
    return 0;
}