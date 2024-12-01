#include <iostream>
#include <vector>

int main()
{
    int64_t N, M;
    std::cin >> N >> M;
    std::vector<std::vector<int64_t>> ans;

    int limit = M % 10;

    auto dfs = [&](auto self, std::vector<int64_t> v) -> void
    {
        if (v.size() == N)
        {
            ans.push_back(v);
            return;
        }
        int begin = 1;
        if (!v.empty())
        {
            begin = v.back() + 10;
        }
        for (int i = begin; i <= M - 10 * (N - v.size() - 1); ++i)
        {
            auto next = v;
            next.push_back(i);
            self(self, next);
        }
    };

    dfs(dfs, {});

    std::cout << ans.size() << std::endl;
    for (auto &i : ans)
    {
        for (int j = 0; j < i.size(); ++j)
        {
            std::cout << i[j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}