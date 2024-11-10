#include <iostream>
#include <cmath>

int main()
{
    long double N, A, B;
    std::cin >> A >> B >> N;
    long double x = std::min(B - 1, N);
    std::cout << std::floor((A * x) / B) - A * std::floor(x / B) << std::endl;
    return 0;
}