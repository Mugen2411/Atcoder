#include <iostream>

int main()
{
    uint64_t Sx, Sy, Tx, Ty;
    std::cin >> Sx >> Sy;
    std::cin >> Tx >> Ty;
    if (Sx < Tx)
    {
        uint64_t tmp = Sx;
        Sx = Tx;
        Tx = tmp;
    }
    if (Sy < Ty)
    {
        uint64_t tmp = Sy;
        Sy = Ty;
        Ty = tmp;
    }
    uint64_t diffY = Sy - Ty;
    uint64_t diffX = Sx - Tx;
    if (diffY <= diffX)
    {
        diffX -= diffY;
    }
    else
    {
        diffX = 0;
    }
    diffX /= 2;
    std::cout << diffX + diffY << std::endl;
    return 0;
}