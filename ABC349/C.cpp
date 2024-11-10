#include <iostream>
#include <string>

int main()
{
    std::string S, T;
    std::cin >> S >> T;
    int idx = 0;
    for (int i = 0; i < S.size(); ++i)
    {
        if (T[idx] == S[i] + ('A' - 'a'))
        {
            ++idx;
        }
    }
    if (idx == 3)
    {
        std::cout << "Yes";
    }
    else if (idx == 2 && T[2] == 'X')
    {
        std::cout << "Yes";
    }
    else
    {
        std::cout << "No";
    }
    return 0;
}