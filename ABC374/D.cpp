#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <numeric>
#include <cmath>
#include <iomanip>

int main()
{
    size_t N, S, T;
    std::cin >> N >> S >> T;
    std::vector<std::array<int64_t, 4>> line(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> line[i][0] >> line[i][1] >> line[i][2] >> line[i][3];
    }
    long double ans = 9999999999999999;
    for (int rev = 0; rev < 1 << N; ++rev)
    {
        std::vector<int64_t> idx(N);
        std::iota(idx.begin(), idx.end(), 0);
        do
        {
            long double tmp = 0;
            int64_t curX = 0;
            int64_t curY = 0;
            for (int i = 0; i < N; ++i)
            {
                if (rev & 1 << idx[i])
                {
                    tmp += std::sqrt((curX - line[idx[i]][0]) * (curX - line[idx[i]][0]) + (curY - line[idx[i]][1]) * (curY - line[idx[i]][1])) / S;
                    curX = line[idx[i]][0];
                    curY = line[idx[i]][1];
                    tmp += std::sqrt((curX - line[idx[i]][2]) * (curX - line[idx[i]][2]) + (curY - line[idx[i]][3]) * (curY - line[idx[i]][3])) / T;
                    curX = line[idx[i]][2];
                    curY = line[idx[i]][3];
                }
                else
                {
                    tmp += std::sqrt((curX - line[idx[i]][2]) * (curX - line[idx[i]][2]) + (curY - line[idx[i]][3]) * (curY - line[idx[i]][3])) / S;
                    curX = line[idx[i]][2];
                    curY = line[idx[i]][3];
                    tmp += std::sqrt((curX - line[idx[i]][0]) * (curX - line[idx[i]][0]) + (curY - line[idx[i]][1]) * (curY - line[idx[i]][1])) / T;
                    curX = line[idx[i]][0];
                    curY = line[idx[i]][1];
                }
            }
            ans = std::min(ans, tmp);
        } while (std::next_permutation(idx.begin(), idx.end()));
    }
    std::cout << std::fixed << std::setprecision(10) << ans;
    return 0;
}