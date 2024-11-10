#include <iostream>
#include <queue>

int main()
{
    size_t N;
    std::cin >> N;
    std::queue<int64_t> H;
    int64_t tmp;
    while (N--)
    {
        std::cin >> tmp;
        H.push(tmp);
    }

    int64_t T = 0;
    while (!H.empty())
    {
        int64_t t = H.front() / 5;
        T += 3 * t;
        t = H.front() % 5;
        while (t > 0)
        {
            ++T;
            t -= (T % 3 == 0) ? 3 : 1;
        }
        H.pop();
    }

    std::cout << T;
}