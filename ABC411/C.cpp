#include <iostream>
#include <vector>

int main()
{
    int N, Q;
    std::cin >> N >> Q;
    int ans = 0;
    std::vector<bool> isBlack(N, false);
    while (Q--)
    {
        int A;
        std::cin >> A;
        --A;
        isBlack[A] = !isBlack[A];
        int64_t diff = isBlack[A] ? 1 : -1;

        bool isLeft = (A != 0 && isBlack[A - 1]);
        bool isRight = (A != N - 1 && isBlack[A + 1]);
        if (isLeft && isRight)
        {
            ans -= diff;
        }
        else if (!isLeft && !isRight)
        {
            ans += diff;
        }
        std::cout << ans << std::endl;
    }
    return 0;
}