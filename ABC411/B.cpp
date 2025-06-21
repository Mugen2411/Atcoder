#include <iostream>
#include <vector>

int main()
{
    int N;
    std::cin >> N;
    std::vector<int> D(N - 1);
    for (auto &&d : D)
    {
        std::cin >> d;
    }
    for (int i = 0; i < N - 1; ++i)
    {
        int cur = D[i];
        for (int j = i + 1; j < N; ++j)
        {
            std::cout << cur << " ";
            cur += D[j];
        }
        std::cout << std::endl;
    }

    return 0;
}