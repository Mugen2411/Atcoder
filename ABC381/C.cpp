#include <iostream>
#include <string>
#include <vector>

int main()
{
    int N;
    std::string S;
    std::cin >> N >> S;
    std::vector<std::pair<char, int64_t>> leng;
    for (int i = 0; i < N; ++i)
    {
        if (leng.empty() || leng.back().first != S[i])
        {
            leng.push_back({S[i], 1});
            continue;
        }
        else
        {
            ++leng.back().second;
        }
    }
    int64_t ans = 0;
    for (int i = 0; i < leng.size(); ++i)
    {
        if (leng[i].first == '/' && i != 0 && i != leng.size() - 1)
        {
            if (leng[i - 1].first == '1' && leng[i + 1].first == '2')
            {
                ans = std::max(ans, std::min(leng[i - 1].second, leng[i + 1].second));
            }
        }
    }
    if (ans == 0)
    {
        std::cout << 1;
        return 0;
    }
    std::cout << ans * 2 + 1;
    return 0;
}