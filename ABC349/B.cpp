#include <iostream>
#include <string>
#include <cstring>

int main()
{
    std::string S;
    std::cin >> S;
    int cnt[26] = {0};
    int answer = 0;
    for (const auto &i : S)
    {
        ++cnt[i - 'a'];
    }
    for (int i = 1; i < 101; ++i)
    {
        for (int j = 0; j < 26; ++j)
        {
            if (cnt[j] == i)
            {
                ++answer;
            }
        }
        if (answer != 0 && answer != 2)
        {
            std::cout << "No" << std::endl;
            return 0;
        }
        answer = 0;
    }
    std::cout << "Yes" << std::endl;
    return 0;
}