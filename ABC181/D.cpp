#include <iostream>
#include <unordered_map>
#include <string>

int main()
{
    std::string S;
    std::cin >> S;
    std::unordered_map<int, size_t> map;
    for (const auto &i : S)
    {
        ++map[i - '0'];
    }
    if (S.size() == 1)
    {
        if (map[8] == 1)
        {
            std::cout << "Yes" << std::endl;
            return 0;
        }
    }
    if (S.size() == 2)
    {
        if (std::stoi(S) % 8 == 0)
        {
            std::cout << "Yes" << std::endl;
            return 0;
        }
        char t = S[0];
        S[0] = S[1];
        S[1] = t;
        if (std::stoi(S) % 8 == 0)
        {
            std::cout << "Yes" << std::endl;
            return 0;
        }
    }
    for (int i = 112; i < 1000; i += 8)
    {
        std::unordered_map<int, size_t> tmp;
        int cnt = 0;
        for (int j = i; j > 0; j /= 10)
        {
            ++tmp[j % 10];
        }
        bool ok = true;
        for (const auto &d : tmp)
        {
            if (map[d.first] < d.second)
            {
                ok = false;
            }
        }
        if (ok)
        {
            std::cout << "Yes" << std::endl;
            return 0;
        }
    }
    std::cout << "No" << std::endl;
    return 0;
}