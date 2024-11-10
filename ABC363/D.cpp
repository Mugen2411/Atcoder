#include <iostream>
#include <vector>

int main()
{
    std::vector<size_t> possible(37);
    possible[0] = 0;
    possible[1] = 10;
    possible[2] = 9;
    for (int i = 2; i <= 18; ++i)
    {
        possible[i * 2 - 1] = possible[i * 2 - 2] * 10;
        possible[i * 2] = possible[i * 2 - 1];
    }
    for (int i = 1; i < possible.size(); ++i)
    {
        possible[i] += possible[i - 1];
    }
    size_t N;
    std::cin >> N;
    size_t digit = 0;
    for (int i = 0; i <= 18; ++i)
    {
        if (N <= possible[i])
        {
            digit = i;
            break;
        }
    }
    size_t order = possible[digit] - N;
    std::vector<size_t> num(digit);
    return 0;
}