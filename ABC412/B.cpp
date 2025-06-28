#include <iostream>
#include <string>
#include <unordered_set>

int main()
{
    std::string S, T;
    std::cin >> S >> T;
    std::unordered_set<char> cond;
    for (int i = 1; i < S.size(); ++i)
    {
        if ('A' <= S[i] && S[i] <= 'Z')
        {
            cond.insert(S[i - 1]);
        }
    }
    for (auto c : cond)
    {
        bool has = false;
        for (int i = 0; i < T.size(); ++i)
        {
            if (c == T[i])
            {
                has = true;
            }
        }
        if (!has)
        {
            std::cout << "No";
            return 0;
        }
    }
    std::cout << "Yes";
    return 0;
}