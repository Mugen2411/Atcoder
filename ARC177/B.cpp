#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

int main()
{
    int N = 0;
    std::cin >> N;
    size_t S = 0;
    std::string tmp;
    std::cin >> tmp;
    for (int i = 0; i < N; ++i)
    {
        if (tmp[i] == '1')
        {
            S |= 1 << N - i - 1;
        }
    }

    std::vector<char> ans;
    for (int i = 0; i < N; ++i)
    {
        if (!((S >> i) & 1))
        {
            continue;
        }
        for (int j = 0; j < N - i; ++j)
        {
            ans.push_back('A');
        }
        for (int j = 0; j < N - i - 1; ++j)
        {
            ans.push_back('B');
        }
    }

    std::cout << ans.size() << std::endl;
    for (const auto &i : ans)
    {
        std::cout << i;
    }

    return 0;
}