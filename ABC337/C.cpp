#include <iostream>
#include <vector>
#include <list>

int main()
{
    size_t N;
    std::cin >> N;
    int64_t begin;
    std::vector<int64_t> A(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A[i];
        if (A[i] == -1)
        {
            begin = i + 1;
        }
        --A[i];
    }

    std::list<int64_t> ans;
    auto dfs = [&](auto self, int64_t cur) -> void
    {
        if (A[cur] == -2)
        {
            return;
        }
        self(self, A[cur]);
        A[cur] = -2;
        ans.push_back(cur);
    };

    for (int i = 0; i < N; ++i)
    {
        if (A[i] == -2)
        {
            continue;
        }
        dfs(dfs, i);
    }

    std::cout << begin << " ";
    for (auto &i : ans)
    {
        std::cout << i + 1 << " ";
    }
    return 0;
}