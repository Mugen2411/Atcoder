#include <iostream>
#include <vector>

int main()
{
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> A(N);
    for (int i = 0; i < N; ++i)
    {
        A[i] = i + 1;
    }
    int top = 0;
    while (Q--)
    {
        int cmd;
        std::cin >> cmd;
        switch (cmd)
        {
        case 1:
        {
            int p, x;
            std::cin >> p >> x;
            A[(top + p - 1) % N] = x;
        }
        break;
        case 2:
        {
            int p;
            std::cin >> p;
            std::cout << A[(top + p - 1) % N] << " ";
            std::cout << std::endl;
        }
        break;
        case 3:
        {
            int p;
            std::cin >> p;
            top += p;
            top %= N;
        }
        break;
        }
    }
    return 0;
}