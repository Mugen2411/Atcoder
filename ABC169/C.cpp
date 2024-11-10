#include <iostream>
#include <string>

int main()
{
    size_t A;
    std::string B;
    std::cin >> A >> B;
    size_t b = 0;
    int digit = 0;
    for (int i = B.size() - 1; i >= 0; --i)
    {
        if (B[i] == '.')
        {
            continue;
        }
        size_t tmp = 1;
        for (int j = 0; j < digit; ++j)
        {
            tmp *= 10;
        }
        b += (B[i] - '0') * tmp;
        ++digit;
    }
    size_t ans = A * b / 100;
    std::cout << ans << std::endl;
    return 0;
}