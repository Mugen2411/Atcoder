#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

int main()
{
    struct Brock
    {
        int64_t X;
        int64_t Y;
        int64_t n;
    };
    int64_t N, W;
    std::cin >> N >> W;
    std::vector<Brock> tmp;
    for (int i = 0; i < N; ++i)
    {
        int64_t X, Y;
        std::cin >> X >> Y;
        tmp.push_back({X - 1, Y - 1, i});
    }
    std::sort(tmp.begin(), tmp.end(), [](const Brock &lhs, const Brock &rhs)
              { return lhs.Y < rhs.Y; });

    std::vector<int64_t> curStack(W);
    std::vector<int64_t> order(N);
    std::vector<int64_t> maxHeight;
    std::vector<int64_t> numInW;

    for (int i = 0; i < N; ++i)
    {
        Brock &t = tmp[i];
        order[t.n] = curStack[t.X];
        if (maxHeight.size() <= curStack[t.X])
        {
            maxHeight.push_back(t.Y);
            numInW.push_back(1);
        }
        else
        {
            maxHeight[curStack[t.X]] = std::max(maxHeight[curStack[t.X]], t.Y);
            ++numInW[curStack[t.X]];
        }
        ++curStack[t.X];
    }

    for (int i = 1; i < maxHeight.size(); ++i)
    {
        maxHeight[i] = std::max(maxHeight[i - 1], maxHeight[i]);
    }

    int64_t Q;
    std::cin >> Q;
    while (Q--)
    {
        int64_t T, A;
        std::cin >> T >> A;
        --A;
        if (maxHeight[order[A]] < T && numInW[order[A]] == W)
        {
            std::cout << "No" << std::endl;
        }
        else
        {
            std::cout << "Yes" << std::endl;
        }
    }

    return 0;
}