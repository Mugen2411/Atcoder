#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<size_t> socks;
    size_t N, K;
    std::cin >> N >> K;
    for (int i = 0; i < K; ++i)
    {
        size_t tmp;
        std::cin >> tmp;
        socks.push_back(tmp);
    }

    return 0;
}