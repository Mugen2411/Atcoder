#include <iostream>
#include <queue>
#include <vector>

template <typename T>
using greater_priority_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;

int main()
{
    int64_t N, K;
    std::cin >> N >> K;
    std::vector<int64_t> P(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> P[i];
    }
    greater_priority_queue<int64_t> q;
    for (int k = 0; k < K; ++k)
    {
        q.push(P[k]);
    }
    std::cout << q.top() << std::endl;

    for (int k = K; k < N; ++k)
    {
        if (q.top() < P[k])
        {
            q.pop();
            q.push(P[k]);
        }
        std::cout << q.top() << std::endl;
    }
    return 0;
}