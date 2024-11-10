#include <iostream>
#include <cmath>
#include <vector>

int main()
{
    size_t N;
    std::cin >> N;
    size_t c = std::cbrtl(N);
    for (size_t i = c; i * i * i >= 0; --i)
    {
        size_t digit = std::log10(i * i * i) + 1;
        size_t tmp = i * i * i;
        std::vector<int> d(digit);
        for (int j = digit - 1; j >= 0; --j)
        {
            d[j] = tmp % 10;
            tmp /= 10;
        }
        bool isKaibun = true;
        for (int j = 0; j < digit / 2; ++j)
        {
            if (d[j] != d[digit - j - 1])
            {
                isKaibun = false;
            }
        }
        if (isKaibun)
        {
            std::cout << i * i * i << std::endl;
            break;
        }
    }
    return 0;
}