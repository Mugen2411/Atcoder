#include <iostream>
#include <unordered_map>
#include <string>

int main()
{
    std::string S;
    std::cin >> S;
    if (S.size() % 2 != 0)
    {
        std::cout << "No";
        return 0;
    }

    std::unordered_map<char, int64_t> map;
    for (auto &c : S)
    {
        ++map[c];
    }
    for (auto &i : map)
    {
        if (i.second != 0 && i.second != 2)
        {
            std::cout << "No";
            return 0;
        }
    }

    for (int i = 0; i < S.size() / 2; ++i)
    {
        if (S[i * 2] != S[i * 2 + 1])
        {
            std::cout << "No";
            return 0;
        }
    }

    std::cout << "Yes";
    return 0;
}