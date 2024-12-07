#include <iostream>

int main()
{
    int N;
    std::cin >> N;
    int last = 0;
    int cur = 0;
    while (N--)
    {
        int T, V;
        std::cin >> T >> V;
        cur = std::max(0, cur - T + last);
        cur += V;
        last = T;
        std::cerr << cur << std::endl;
    }
    std::cout << cur;
    return 0;
}