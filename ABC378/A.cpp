#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int A[4] = {0};
    for (int i = 0; i < 4; ++i)
    {
        int t;
        std::cin >> t;
        ++A[t - 1];
    }
    int ans = 0;
    for (int i = 0; i < 4; ++i)
    {
        if (A[i] == 2)
        {
            ++ans;
        }
        if (A[i] == 3)
        {
            ++ans;
        }
        if (A[i] == 4)
        {
            ans += 2;
        }
    }
    std::cout << ans;

    return 0;
}