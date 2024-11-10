#include <vector>
#include <iostream>

int main()
{
    int N;
    std::cin >> N;
    std::vector<int[2]> A(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A[i][0] >> A[i][1];
    }
    int Q;
    std::cin >> Q;
    while (Q--)
    {
        int t, d;
        std::cin >> t >> d;
        --t;
        int ans = A[t][1];
        while (ans < d)
        {
            ans += A[t][0];
        }
        std::cout << ans << std::endl;
    }
    return 0;
}