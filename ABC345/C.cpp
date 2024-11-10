#include <iostream>
#include <unordered_map>
#include <string>

int main()
{
    std::string S;
    std::cin >> S;
    std::unordered_map<char, size_t> map;
    size_t len = S.size();
    for (size_t i = 0; i < len; ++i)
    {
        ++map[S[i]];
    }
    size_t sum = (len) * (len - 1) / 2;
    bool isSame = false;
    for (const auto &i : map)
    {
        sum -= i.second * (i.second - 1) / 2;
        if (i.second > 1)
        {
            isSame |= true;
        }
    }
    if (isSame)
    {
        ++sum;
    }
    std::cout << sum;
    return 0;
}