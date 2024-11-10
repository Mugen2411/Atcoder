#include <iostream>
#include <vector>
#include <unordered_map>

size_t N, X;
size_t ans = 0;

std::vector<std::vector<size_t>> A;

void dfs(size_t pos, size_t seki)
{
    if (pos == N)
    {
        if (seki == X)
        {
            ++ans;
        }
        return;
    }
    for (const auto &i : A[pos])
    {
        if (seki > X / i)
        {
            continue;
        }
        dfs(pos + 1, seki * i);
    }
}
int main()
{
    std::cin >> N >> X;
    std::vector<size_t> L(N);
    size_t pattern = 1;
    for (size_t i = 0; i < N; ++i)
    {
        std::cin >> L[i];
        pattern *= L[i];
        A.push_back(std::vector<size_t>(L[i]));
        for (size_t j = 0; j < L[i]; ++j)
        {
            std::cin >> A[i][j];
        }
    }
    dfs(0, 1);
    std::cout << ans << std::endl;
    return 0;
}