#include <iostream>
#include <vector>
#include <unordered_map>
#include <iomanip>

int main()
{
    int64_t N;
    std::cin >> N;
    std::vector<std::unordered_map<int64_t, int64_t>> data;
    std::vector<int64_t> K(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> K[i];
        std::unordered_map<int64_t, int64_t> A;
        for (int j = 0; j < K[i]; ++j)
        {
            int64_t tmp;
            std::cin >> tmp;
            ++A[tmp];
        }
        data.push_back(A);
    }

    long double ans = 0.;
    for (int i = 0; i < N - 1; ++i)
    {
        for (int j = i + 1; j < N; ++j)
        {
            long double tmp = 0.;
            for (auto &cur : data[i])
            {
                if (data[j].count(cur.first) == 0)
                {
                    continue;
                }
                tmp += static_cast<long double>(cur.second * data[j][cur.first]) / static_cast<long double>(K[i] * K[j]);
            }
            ans = std::max(tmp, ans);
        }
    }

    std::cout << std::fixed << std::setprecision(15) << ans;
    return 0;
}