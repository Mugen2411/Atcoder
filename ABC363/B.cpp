#include <iostream>
#include <queue>

int main()
{
    int N, T, P;
    std::cin >> N >> T >> P;
    std::priority_queue<int, std::vector<int>> q;
    int tmp;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> tmp;
        q.push(tmp);
    }
    for (int i = 0; i < P - 1; ++i)
    {
        q.pop();
    }
    int top = q.top();
    if (top >= T)
    {
        std::cout << 0;
        return 0;
    }
    std::cout << T - top;
    return 0;
}