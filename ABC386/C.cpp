#include <iostream>
#include <string>

int main()
{
    int64_t K;
    std::string S, T;
    std::cin >> K >> S >> T;
    if (std::abs((int64_t)S.size() - (int64_t)T.size()) >= 2)
    {
        std::cout << "No";
        return 0;
    }
    if (S.size() > T.size())
    {
        std::swap(S, T);
    }

    int offset = 0;
    int edited = 0;
    for (int i = 0; i < S.size(); ++i)
    {
        if (S[i] == T[i + offset])
        {
            continue;
        }
        if (S[i] == T[i + offset + 1])
        {
            offset++;
            edited++;
            continue;
        }
        if (S[i + 1] == T[i + offset + 1])
        {
            edited++;
            continue;
        }
        std::cout << "No";
        return 0;
    }
    if (edited <= 1)
    {
        std::cout << "Yes";
    }
    else
    {
        std::cout << "No";
    }
    return 0;
}