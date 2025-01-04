#include <iostream>
#include <string>

int main()
{
    std::string S;
    std::cin >> S;
    int cur = 0;
    int ans = 0;
    while (cur != S.size())
    {
        switch (S[cur])
        {
        case '0':
        {
            if (cur < S.size() - 1 && S[cur + 1] == '0')
            {
                cur++;
            }
        }
        break;
        default:
            break;
        }
        ++cur;
        ++ans;
    }
    std::cout << ans;
    return 0;
}