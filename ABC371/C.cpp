#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int G[8][8] = {0};
int H[8][8] = {0};
int A[8][8] = {0};

int main()
{
    int64_t N, Mg, Mh;
    std::cin >> N;
    std::cin >> Mg;
    int u, v;
    while (Mg--)
    {
        std::cin >> u >> v;
        --u, --v;
        G[u][v] = 1;
        G[v][u] = 1;
    }

    std::cin >> Mh;
    while (Mh--)
    {
        std::cin >> u >> v;
        --u, --v;
        H[u][v] = 1;
        H[v][u] = 1;
    }

    for (int i = 0; i < N; ++i)
    {
        for (int j = i + 1; j < N; ++j)
        {
            std::cin >> A[i][j];
            A[j][i] = A[i][j];
        }
    }

    std::vector<int64_t> idx(N);
    std::iota(idx.begin(), idx.end(), 0);

    int64_t ans = 999999999;
    do
    {
        int64_t tmp = 0;
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (H[i][j] != G[idx[i]][idx[j]])
                {
                    tmp += A[i][j];
                }
            }
        }
        ans = std::min(ans, tmp);

    } while (std::next_permutation(idx.begin(), idx.end()));
    std::cout << ans;
    return 0;
}