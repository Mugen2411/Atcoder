#include <iostream>

int main()
{
    int N;
    std::cin >> N;
    int ans = 0;
    while (N--)
    {
        int A, B;
        std::cin >> A >> B;
        if (A < B)
        {
            ++ans;
        }
    }
    std::cout << ans;
    return 0;
}