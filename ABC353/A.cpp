#include <iostream>
#include <vector>

int main()
{
    int N;
    std::cin >> N;
    std::vector<int> H(N);
    int max = -1;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> H[i];
        if (i > 0)
        {
            if (H[i] > H[0])
            {
                std::cout << i + 1 << std::endl;
                return 0;
            }
        }
    }

    std::cout << -1 << std::endl;

    return 0;
}