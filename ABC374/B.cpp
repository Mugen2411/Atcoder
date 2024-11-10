#include <iostream>
#include <string>

int main()
{
    std::string S, T;
    std::cin >> S >> T;
    for (int i = 0; i < S.size() && i < T.size(); ++i)
    {
        if (S[i] != T[i])
        {
            std::cout << i + 1;
            return 0;
        }
    }
    if (S.size() == T.size())
    {
        std::cout << 0;
        return 0;
    }
    std::cout << std::min(S.size(), T.size()) + 1;
    return 0;
}