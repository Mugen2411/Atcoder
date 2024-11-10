#include <iostream>
#include <vector>
#include <array>

int main()
{
    size_t N;
    std::cin >> N;
    std::vector<std::array<int, 2>> A(N + 1, {-1, -1});
    int tmp;
    for (int i = 0; i < 2 * N; ++i)
    {
        std::cin >> tmp;
        if (A[tmp][0] == -1)
        {
            A[tmp][0] = i;
        }
        else
        {
            A[tmp][1] = i;
        }
    }
    int ans = 0;
    for (int i = 0; i <= N; ++i)
    {
        if (A[i][1] - A[i][0] == 2)
        {
            ++ans;
        }
    }
    std::cout << ans << std::endl;
    return 0;
}