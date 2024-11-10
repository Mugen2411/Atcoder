#include <iostream>

int main()
{
    int N, K;
    std::cin >> N >> K;
    int A;
    int cnt = 1;
    int cap = K;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A;
        if (A <= cap)
        {
            cap -= A;
        }
        else
        {
            cap = K - A;
            ++cnt;
        }
    }
    std::cout << cnt << std::endl;
    return 0;
}