#include <iostream>
#include <unordered_map>

int main()
{
    size_t N;
    std::cin >> N;
    std::unordered_map<size_t, size_t> memo;
    auto rec = [&](auto self, size_t v) -> size_t
    {
        if (v == 0)
        {
            return 1;
        }
        if (memo.count(v))
        {
            return memo[v];
        }
        return memo[v] = self(self, v / 2) + self(self, v / 3);
    };
    std::cout << rec(rec, N) << std::endl;
    return 0;
}