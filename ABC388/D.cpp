#include <iostream>
#include <vector>
#include <queue>

template <typename T>
using greater_priority_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;

int main()
{
    size_t N;
    std::cin >> N;
    std::vector<int64_t> A(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A[i];
    }
    greater_priority_queue<int64_t> q;
    for (int i = 0; i < N; ++i)
    {
        A[i] += q.size();
        q.push(A[i] + i);
        A[i] -= N - i - 1;
        while (!q.empty() && q.top() - i <= 0)
        {
            q.pop();
        }
    }
    for (int i = 0; i < N; ++i)
    {
        std::cout << std::max(0l, A[i]) << " ";
    }
    return 0;
}