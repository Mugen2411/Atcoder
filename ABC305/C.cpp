#ifndef __INCLUDED_GRID2D__
#define __INCLUDED_GRID2D__

#include <vector>
#include <cassert>
#include <cstdint>

/**
    @brief	二次元のグリッドを表すクラス

    @tparam	T   格納する型
 */
template <class T>
class Grid2D
{
public:
    /**
        @brief	コンストラクタ

        @param[in]	height          高さ
        @param[in]	width           幅
        @param[in]	initialValue    初期値
    */
    Grid2D(int64_t height, int64_t width, T initialValue)
        : m_data(height * width, initialValue), m_width(width), m_height(height)
    {
    }

    /**
        @brief	        指定した座標の値にアクセスする

        @param[in]	x   X座標
        @param[in]	y   Y座標

        @return         目的の座標の参照
     */
    T &at(int64_t x, int64_t y)
    {
        assert(0 <= x && x < m_width);
        assert(0 <= y && y < m_height);

        return m_data[y * m_width + x];
    }

    /**
        @brief	高さの取得

        @return 高さ
     */
    int64_t GetHeight() const
    {
        return m_height;
    }

    /**
        @brief	幅の取得

        @return 幅
     */
    int64_t GetWidth() const
    {
        return m_width;
    }

private:
    std::vector<T> m_data; //!< 本体となる配列
    int64_t m_width;       //!< 幅
    int64_t m_height;      //!< 高さ
};

#endif //__INCLUDED_GRID2D__

#include <iostream>

int main()
{
    int64_t H, W;
    std::cin >> H >> W;
    Grid2D<char> grid(H, W, '\0');
    for (int y = 0; y < H; ++y)
    {
        for (int x = 0; x < W; ++x)
        {
            std::cin >> grid.at(x, y);
        }
    }

    int64_t beginX = 1000, endX = -1;
    int64_t beginY = 1000, endY = -1;

    for (int y = 0; y < H; ++y)
    {
        for (int x = 0; x < W; ++x)
        {
            if (grid.at(x, y) == '#')
            {
                if (beginX > x)
                {
                    beginX = x;
                }
                if (endX <= x)
                {
                    endX = x;
                }
                if (beginY > y)
                {
                    beginY = y;
                }
                if (endY <= y)
                {
                    endY = y;
                }
            }
        }
    }

    for (int y = beginY; y <= endY; ++y)
    {
        for (int x = beginX; x <= endX; ++x)
        {
            if (grid.at(x, y) != '#')
            {
                std::cout << y + 1 << " " << x + 1;
                return 0;
            }
        }
    }

    return 0;
}