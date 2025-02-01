#include <iostream>
#include <vector>

int main()
{
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> P(N);
    std::vector<int> H(N);

    for (int i = 0; i < N; ++i)
    {
        P[i] = i;
        H[i] = 1;
    }

    int ans = 0;

    while (Q--)
    {
        int cmd;
        std::cin >> cmd;
        switch (cmd)
        {
        case 1:
        {
            int p, h;
            std::cin >> p >> h;
            --p, --h;
            if (H[P[p]] == 2)
            {
                --ans;
            }
            --H[P[p]];
            P[p] = h;
            ++H[P[p]];
            if (H[P[p]] == 2)
            {
                ++ans;
            }
        }
        break;
        case 2:
        {
            std::cout << ans << std::endl;
        }
        break;

        default:
            break;
        }
    }
    return 0;
}