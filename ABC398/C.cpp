#include <iostream>
#include <vector>
#include <unordered_map>

int main()
{
    int N;
    std::cin >> N;
    std::vector<int64_t> A(N);
    for (auto &&i : A)
    {
        std::cin >> i;
    }
    std::unordered_map<int64_t, int64_t> m;
    int curIdx = -1;
    int curNum = -1;
    for (auto i : A)
    {
        ++m[i];
    }
    for (int i = 0; i < N; ++i)
    {
        if (m[A[i]] != 1)
        {
            continue;
        }
        if (curNum < A[i])
        {
            curIdx = i + 1;
            curNum = A[i];
        }
    }
    std::cout << curIdx;
    return 0;
}