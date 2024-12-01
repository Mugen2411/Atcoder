#include <iostream>
#include <string>

int main()
{
    int N, D;
    std::string S;
    std::cin >> N >> D;
    std::cin >> S;

    int day = 0;

    for (int i = S.size() - 1; i >= 0; --i)
    {
        if (S[i] == '@')
        {
            S[i] = '.';
            ++day;
        }
        if (day >= D)
        {
            break;
        }
    }

    for (auto c : S)
    {
        std::cout << c;
    }

    return 0;
}