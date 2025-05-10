#include <iostream>
#include <vector>

int main()
{
    int N, M;
    std::cin >> N >> M;
    std::vector<int> A(N);
    for (auto &&i : A)
    {
        std::cin >> i;
    }

    for (int i = 0; i <= N; ++i)
    {
        std::vector<bool> judge(M, false);
        for (auto a : A)
        {
            if (a <= M)
            {
                judge[a - 1] = true;
            }
        }
        for (auto j : judge)
        {
            if (!j)
            {
                std::cout << i;
                return 0;
            }
        }
        A.pop_back();
    }
    return 0;
}