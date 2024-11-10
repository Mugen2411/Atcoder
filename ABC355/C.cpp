#include <iostream>
#include <vector>

int main()
{
    size_t N, T;
    std::cin >> N >> T;
    std::vector<size_t> row(N);
    std::vector<size_t> col(N);
    std::vector<size_t> naname(2);
    size_t tmp;
    for (size_t i = 0; i < T; ++i)
    {
        std::cin >> tmp;
        --tmp;
        size_t r = tmp % N;
        ++row[r];
        size_t c = tmp / N;
        ++col.at(c);
        if (tmp % N == tmp / N)
        {
            ++naname[0];
        }
        if (tmp % N == N - tmp / N - 1)
        {
            ++naname[1];
        }
        for (size_t j = 0; j < N; ++j)
        {
            if (row[j] == N)
            {
                std::cout << i + 1;
                return 0;
            }
            if (col[j] == N)
            {
                std::cout << i + 1;
                return 0;
            }
        }
        for (int j = 0; j < 2; ++j)
        {
            if (naname[j] == N)
            {
                std::cout << i + 1;
                return 0;
            }
        }
    }
    std::cout << -1;
    return 0;
}