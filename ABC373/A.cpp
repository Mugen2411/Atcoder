#include <iostream>
#include <string>

int main()
{
    size_t ans = 0;
    for (int i = 1; i <= 12; ++i)
    {
        std::string S;
        std::cin >> S;
        if (S.size() == i)
        {
            ++ans;
        }
    }
    std::cout << ans;
    return 0;
}