#include <iostream>
#include <string>

int main()
{
    size_t N;
    std::string S;
    std::cin >> N >> S;
    if (N < 3)
    {
        std::cout << 0;
        return 0;
    }
    size_t ans = 0;
    for (int i = 0; i < N - 2; ++i)
    {
        if (S[i] == '#' && S[i + 1] == '.' && S[i + 2] == '#')
        {
            ++ans;
        }
    }
    std::cout << ans;
    return 0;
}