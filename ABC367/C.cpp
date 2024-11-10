#include <iostream>
#include <vector>

int main()
{
    int N, K;
    std::cin >> N >> K;
    std::vector<int> R(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> R[i];
    }
    std::vector<int> glob(N);
    std::vector<std::vector<int>> list;
    auto f = [&](auto f, int digit) -> void
    {
        if (digit == 0)
        {
            list.push_back(std::vector<int>(N));
            auto itr = list.rbegin();
            for (int i = 0; i < N; ++i)
            {
                (*itr)[i] = glob[i];
            }
            return;
        }
        for (int i = 1; i <= R[N - digit]; ++i)
        {
            glob[N - digit] = i;
            f(f, digit - 1);
        }
    };
    f(f, N);
    for (auto &v : list)
    {
        int sum = 0;
        for (auto &i : v)
        {
            sum += i;
        }
        if (sum % K == 0)
        {
            for (auto &i : v)
            {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
    }
    return 0;
}