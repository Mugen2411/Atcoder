#include <iostream>
#include <vector>

int main()
{
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> box(N, 0);
    while (Q--)
    {
        int X;
        std::cin >> X;
        if (X != 0)
        {
            ++box[X - 1];
            std::cout << X << std::endl;
            continue;
        }
        int idx = N - 1;
        int amount = box[N - 1];
        for (int i = N - 1; i >= 0; --i)
        {
            if (box[i] <= amount)
            {
                idx = i;
                amount = box[idx];
            }
        }
        ++box[idx];
        std::cout << idx + 1 << std::endl;
    }

    return 0;
}