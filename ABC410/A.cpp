#include <iostream>
#include <vector>

int main()
{
    int N;
    std::cin >> N;
    std::vector<int> A(N);
    for (auto &&a : A)
    {
        std::cin >> a;
    }
    int K;
    std::cin >> K;
    int ans = 0;
    for (auto &a : A)
    {
        if (a >= K)
        {
            ++ans;
        }
    }
    std::cout << ans;
    return 0;
}