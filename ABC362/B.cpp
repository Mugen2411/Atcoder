#include <iostream>

int main()
{
    int x1, y1, x2, y2, x3, y3;
    std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    int e1 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    int e2 = (x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3);
    int e3 = (x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3);

    if ((e1 + e2 == e3) || (e1 + e3 == e2) || (e2 + e3 == e1))
    {
        std::cout << "Yes";
    }
    else
    {
        std::cout << "No";
    }

    return 0;
}