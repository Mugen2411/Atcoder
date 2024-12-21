#include <iostream>
#include <vector>

int main()
{
    int N;
    std::cin >> N;
    std::vector<int> H(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> H[i];
    }

    int ans = 1;
    for (int gap = 1; gap <= N / 2; ++gap)
    {
        for (int i = 0; i < gap; ++i)
        {
            int tmp = 1;
            for (int cur = i + gap; cur < N; cur += gap)
            {
                if (H[cur - gap] == H[cur])
                {
                    ++tmp;
                }
                else
                {
                    ans = std::max(ans, tmp);
                    // std::cerr << gap << ' ' << i << ' ' << tmp << std::endl;
                    tmp = 1;
                }
            }
            ans = std::max(ans, tmp);
        }
    }
    std::cout << ans;
    return 0;
}