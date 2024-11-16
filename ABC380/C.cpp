#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <string>

int main()
{
    int N, K;
    std::cin >> N >> K;
    std::string S;
    std::cin >> S;

    std::vector<std::array<int64_t, 2>> leng;
    for (auto s : S)
    {
        if (leng.empty() || leng.back()[0] != s - '0')
        {
            leng.push_back({s - '0', 1});
        }
        else
        {
            ++leng.back()[1];
        }
    }
    int k = 1;
    decltype(leng)::iterator rhs;
    decltype(leng)::iterator lhs;
    for (auto itr = leng.begin(); itr != leng.end(); ++itr)
    {
        if ((*itr)[0] == 0)
        {
            continue;
        }
        if ((*itr)[0] == 1)
        {
            if (k == K - 1)
            {
                lhs = itr;
            }
            if (k == K)
            {
                rhs = itr;
            }
            ++k;
        }
    }
    auto tmp = *rhs;
    leng.erase(rhs);
    leng.insert(lhs, tmp);
    for (auto &l : leng)
    {
        for (int i = 0; i < l[1]; ++i)
        {
            std::cout << l[0];
        }
    }
    return 0;
}