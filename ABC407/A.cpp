#include <iostream>

int main()
{
    int A, B;
    std::cin >> A >> B;
    double div = (double)A / (double)B;
    int ans1 = A / B;
    int ans2 = ans1 + 1;
    double diff1 = std::abs(double(ans1) - div);
    double diff2 = std::abs(double(ans2) - div);
    if (diff1 < diff2)
    {
        std::cout << ans1;
    }
    else
    {
        std::cout << ans2;
    }
    return 0;
}