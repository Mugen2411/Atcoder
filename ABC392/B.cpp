#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int N, M;
    std::cin >> N >> M;
    std::vector<int> A(M);
    for (int i = 0; i < M; ++i)
    {
        std::cin >> A[i];
    }
    std::sort(A.begin(), A.end());
    std::vector<int> a;
    for (int ans = 1; ans <= N; ++ans)
    {
        bool isAns = false;
        for (int i = 0; i < M; ++i)
        {
            if (A[i] == ans)
            {
                isAns |= true;
            }
        }
        if (!isAns)
        {
            a.push_back(ans);
        }
    }
    std::cout << a.size() << std::endl;
    for (auto i : a)
    {
        std::cout << i << " ";
    }
    return 0;
}