#include <iostream>
#include <unordered_map>

std::unordered_map<size_t, size_t> memo;

size_t f(size_t v)
{
    if (v == 1)
    {
        return 0;
    }
    if (memo.count(v))
    {
        return memo[v];
    }
    return memo[v] = v + f(v / 2) + f((v + 1) / 2);
}

int main()
{
    size_t N;
    std::cin >> N;
    std::cout << f(N) << std::endl;
    return 0;
}