#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

int main()
{
    size_t N, M;
    std::cin >> N >> M;
    std::vector<int> A(N);
    std::vector<int> B(N + M);
    std::unordered_map<int, int> m;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A[i];
        m[A[i]] = 1;
        B[i] = A[i];
    }
    for (int i = 0; i < M; ++i)
    {
        std::cin >> B[i + N];
    }
    std::sort(B.begin(), B.end());
    bool beforeA = false;
    for (int i = 1; i < N + M; ++i)
    {
        if (m[B[i - 1]] == 1 && m[B[i]])
        {
            std::cout << "Yes";
            return 0;
        }
    }
    std::cout << "No";
    return 0;
}