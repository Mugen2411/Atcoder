#include <iostream>
#include <vector>
#include <unordered_set>

int main()
{
    int64_t T;
    std::cin >> T;
    std::vector<int64_t> output;
    for (int64_t t = 0; t < T; ++t)
    {
        int64_t N;
        std::cin >> N;
        std::vector<int64_t> A(2 * N);
        for (auto &&a : A)
        {
            std::cin >> a;
        }
        // compress
        std::vector<std::pair<int64_t, int64_t>> comp;
        for (int i = 0; i < 2 * N; ++i)
        {
            if (comp.empty() || comp.back().first != A[i])
            {
                comp.push_back({A[i], 1});
            }
            else
            {
                ++comp.back().second;
            }
        }

        int64_t ans = 0;
        std::vector<std::unordered_set<int64_t>> expected(N + 1);
        for (int i = 0; i < comp.size(); ++i)
        {
            if (comp[i].second != 1)
            {
                continue;
            }
            if (i != 0 && comp[i - 1].second == 1)
            {
                if (expected[comp[i].first].count(comp[i - 1].first) == 0)
                {
                    // if (comp[i].first > comp[i - 1].first)
                    {
                        expected[comp[i].first].insert(comp[i - 1].first);
                        expected[comp[i - 1].first].insert(comp[i].first);
                    }
                }
                else
                {
                    expected[comp[i].first].erase(comp[i - 1].first);
                    expected[comp[i - 1].first].erase(comp[i].first);
                    ++ans;
                }
            }
        }
        output.push_back(ans);
    }
    for (auto &i : output)
    {
        std::cout << i << std::endl;
    }
    return 0;
}