#include <iostream>

int A[110][110] = {0};

int main()
{
    size_t N;
    std::cin >> N;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            int tmp;
            std::cin >> tmp;
            --tmp;
            A[i][j] = tmp;
            A[j][i] = tmp;
        }
    }

    int ans = 0;
    for (int i = 0; i < N; ++i)
    {
        ans = A[ans][i];
    }
    std::cout << ans + 1;
    return 0;
}