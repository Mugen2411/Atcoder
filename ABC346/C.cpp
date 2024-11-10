#include <iostream>
#include <set>

int main()
{
    size_t N, K;
    std::cin >> N >> K;
    size_t sum = (1 + K) * K / 2;
    std::set<size_t> s;
    size_t tmp;
    size_t sumA = 0;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> tmp;
        if (tmp > K)
        {
            continue;
        }
        if (s.count(tmp) != 0)
        {
            continue;
        }
        s.insert(tmp);
        sumA += tmp;
    }
    std::cout << sum - sumA;
    return 0;
}