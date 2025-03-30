#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

int main()
{
    int N;
    std::cin >> N;
    std::vector<int> P(N);
    std::vector<int> sortP;
    std::unordered_map<int, int> mp;
    std::unordered_map<int, int> ans;
    for (auto &&i : P)
    {
        std::cin >> i;
        ++mp[i];
    }
    for (auto &i : mp)
    {
        sortP.push_back(i.first);
    }
    std::sort(sortP.begin(), sortP.end());
    int r = 1;
    while (!sortP.empty())
    {
        ans[sortP.back()] = r;
        r += mp[sortP.back()];
        sortP.pop_back();
    }

    for (int i = 0; i < N; ++i)
    {
        std::cout << ans[P[i]] << std::endl;
    }

    return 0;
}