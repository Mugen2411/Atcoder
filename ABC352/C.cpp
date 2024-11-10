#include <iostream>

int main()
{
    int N;
    std::cin >> N;
    int A, B;
    int maximum = 0;
    size_t sum = 0;
    int tmp;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A >> B;
        tmp = B - A;
        sum += A;
        if (tmp > maximum)
        {
            maximum = tmp;
        }
    }
    std::cout << sum + maximum << std::endl;
    return 0;
}