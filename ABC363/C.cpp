#include <iostream>
#include <string>
#include <unordered_map>

int main()
{
    size_t fact[31] = {1};
    for (int i = 1; i <= 30; ++i)
    {
        fact[i] = fact[i - 1] * i;
    }
    std::string S;
    size_t N, K;
    std::cin >> N >> K;
    std::cin >> S;
    std::unordered_map<char, size_t> cnt;
    for (auto ch : S)
    {
        cnt[ch]++;
    }
    size_t all = fact[N];
    for (auto c : cnt)
    {
        all /= c.second;
    }

    return 0;
}