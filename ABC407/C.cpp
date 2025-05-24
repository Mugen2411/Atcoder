#include <iostream>
#include <string>

int main()
{
    std::string S;
    std::cin >> S;
    int64_t ans = 0;
    int64_t cur = S[0] - '0';
    for (int i = 1; i < S.size(); ++i)
    {
        int digit = S[i] - '0';
        int diff = cur - digit;
        cur = digit;
        diff = (diff < 0) ? diff + 10 : diff;
        std::cerr << diff << std::endl;
        ans += diff;
    }
    std::cout << ans + S.size() + (S.back() - '0');

    return 0;
}