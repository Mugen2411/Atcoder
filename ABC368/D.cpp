#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

int main()
{
    size_t N, K;
    std::cin >> N >> K;
    std::vector<std::unordered_set<size_t>> path(N);
    std::unordered_map<size_t, size_t> dim(N);
    std::unordered_set<size_t> vert;
    std::unordered_set<size_t> V;
    for (int i = 0; i < N - 1; ++i)
    {
        vert.insert(i);
        V.insert(i);
        size_t A, B;
        std::cin >> A >> B;
        --A;
        --B;
        path[A].insert(B);
        path[B].insert(A);
        ++dim[A];
        ++dim[B];
    }
    vert.insert(N - 1);
    V.insert(N - 1);

    for (int i = 0; i < K; ++i)
    {
        size_t t;
        std::cin >> t;
        V.erase(--t);
    }

    while (1)
    {
        bool isFinished = true;
        for (auto itr = V.begin(); itr != V.end();)
        {
            if (dim[*itr] == 1)
            {

                auto p = *path[*itr].begin();
                --dim[p];
                --dim[*itr];
                path[p].erase(*itr);
                path[*itr].erase(p);

                vert.erase(*itr);
                itr = V.erase(itr);
                isFinished = false;
            }
            else
            {
                ++itr;
            }
        }
        if (isFinished)
        {
            break;
        }
    }

    std::cout << vert.size();
    return 0;
}