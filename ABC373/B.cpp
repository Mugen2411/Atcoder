#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    std::string S;
    std::cin >> S;

    size_t ans = 0;
    auto itr = std::find(S.begin(), S.end(), 'A');
    for (char ch = 'B'; ch <= 'Z'; ++ch)
    {
        auto cur = std::find(S.begin(), S.end(), ch);
        ans += std::abs(cur - itr);
        itr = cur;
    }
    std::cout << ans;
    return 0;
}