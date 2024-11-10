#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <string>

int main()
{
    size_t N;
    std::cin >> N;
    std::unordered_map<std::string, size_t> memo;
    std::string S;
    for (size_t i = 0; i < N; ++i)
    {
        std::cin >> S;
        std::sort(S.begin(), S.end());
        ++memo[S];
    }
    size_t ans = 0;
    for (const auto &i : memo)
    {
        ans += (i.second - 1) * i.second / 2;
    }
    std::cout << ans << std::endl;
    return 0;
}