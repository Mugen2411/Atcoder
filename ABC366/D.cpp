#include <iostream>
#include <vector>

int main()
{
    size_t N;
    std::cin >> N;
    std::vector<std::vector<std::vector<size_t>>> A(N + 1);

    for (int z = 0; z <= N; ++z)
    {
        A[z].resize(N + 1);
        for (int y = 0; y <= N; ++y)
        {
            A[z][y].resize(N + 1);
        }
    }
    for (int z = 1; z <= N; ++z)
    {
        for (int y = 1; y <= N; ++y)
        {
            for (int x = 1; x <= N; ++x)
            {
                std::cin >> A[x][y][z];
            }
        }
    }

    for (int y = 0; y <= N; y++)
    {
        for (int x = 0; x <= N; ++x)
        {
            for (int z = 1; z <= N; ++z)
            {
                A[z][y][x] += A[z - 1][y][x];
            }
        }
    }

    for (int z = 0; z <= N; z++)
    {
        for (int x = 0; x <= N; ++x)
        {
            for (int y = 1; y <= N; ++y)
            {
                A[z][y][x] += A[z][y - 1][x];
            }
        }
    }

    for (int z = 0; z <= N; z++)
    {
        for (int y = 0; y <= N; ++y)
        {
            for (int x = 1; x <= N; ++x)
            {
                A[z][y][x] += A[z][y][x - 1];
            }
        }
    }

    size_t Q;
    std::cin >> Q;
    for (int q = 0; q < Q; ++q)
    {
        size_t Lx, Rx, Ly, Ry, Lz, Rz;
        std::cin >> Lx >> Rx >> Ly >> Ry >> Lz >> Rz;

        size_t a = A[Rz - 0][Ry - 0][Rx - 0];
        size_t b = A[Lz - 1][Ry - 0][Rx - 0];
        size_t c = A[Rz - 0][Ly - 1][Rx - 0];
        size_t d = A[Rz - 0][Ry - 0][Lx - 1];
        size_t e = A[Lz - 1][Ly - 1][Rx - 0];
        size_t f = A[Rz - 0][Ly - 1][Lx - 1];
        size_t g = A[Lz - 1][Ry - 0][Lx - 1];
        size_t h = A[Lz - 1][Ly - 1][Lx - 1];

        size_t ans = a - b - c - d + e + f + g - h;

        std::cout << ans << std::endl;
    }
    return 0;
}