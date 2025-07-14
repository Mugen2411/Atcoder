#include <iostream>

int main()
{
    int N, L, R;
    std::cin >> N >> L >> R;
    int ans = 0;
    while (N--)
    {
        int X, Y;
        std::cin >> X >> Y;
        if (X <= L && R <= Y)
        {
            ++ans;
        }
    }
    std::cout << ans;
    return 0;
}