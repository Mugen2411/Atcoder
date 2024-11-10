#include <iostream>
#include <vector>
#include <unordered_map>

int main()
{
    size_t N;
    std::cin >> N;
    std::unordered_map<int, int> history;
    std::vector<int> A(N);
    std::vector<int> B(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A[i];
    }
    for (int i = 0; i < N; ++i)
    {
        if (history.count(A[i]) == 0)
        {
            B[i] = -1;
        }
        else
        {
            B[i] = history[A[i]];
        }
        history[A[i]] = i + 1;
    }
    for (int &b : B)
    {
        std::cout << b << " ";
    }
    return 0;
}