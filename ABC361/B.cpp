#include <iostream>

bool isOverlap(int b1, int e1, int b2, int e2)
{
    return !(e1 <= b2 || e2 <= b1);
}
int main()
{
    int x[4];
    int y[4];
    int z[4];
    std::cin >> x[0] >> y[0] >> z[0] >> x[1] >> y[1] >> z[1];
    std::cin >> x[2] >> y[2] >> z[2] >> x[3] >> y[3] >> z[3];
    if (!isOverlap(x[0], x[1], x[2], x[3]))
    {
        std::cout << "No";
        return 0;
    }
    if (!isOverlap(y[0], y[1], y[2], y[3]))
    {
        std::cout << "No";
        return 0;
    }
    if (!isOverlap(z[0], z[1], z[2], z[3]))
    {
        std::cout << "No";
        return 0;
    }
    std::cout << "Yes";
    return 0;
}