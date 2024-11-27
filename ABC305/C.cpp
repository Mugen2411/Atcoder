#ifndef __INCLUDED_GRID2D__
#define __INCLUDED_GRID2D__

#include <vector>
#include <cassert>
#include <cstdint>
#include <iostream>

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
    T &Ref(int64_t x, int64_t y)
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

    template <class U>
    friend std::istream &operator>>(std::istream &stream, Grid2D<U> &dest);
};

/**
    @brief	        入力ストリーム演算子

    @tparam	T       Grid2Dに格納する型
    @param[in]	    stream  入力ストリーム
    @param[in]	    dest    入力を受け付ける先のGrid2D
    @return                 入力ストリーム
 */
template <class T>
std::istream &operator>>(std::istream &stream, Grid2D<T> &dest)
{
    for (int64_t y = 0; y < dest.m_height; ++y)
    {
        for (int64_t x = 0; x < dest.m_width; ++x)
        {
            stream >> dest.Ref(x, y);
        }
    }
    return stream;
}

#endif //__INCLUDED_GRID2D__

#include <iostream>

int main()
{
    int64_t H, W;
    std::cin >> H >> W;
    //****************************************
    // 一撃で入力可能！
    Grid2D<char> grid(H, W, '\0');
    std::cin >> grid;
    //****************************************

    int64_t beginX = 1000, endX = -1;
    int64_t beginY = 1000, endY = -1;

    for (int y = 0; y < H; ++y)
    {
        for (int x = 0; x < W; ++x)
        {
            if (grid.Ref(x, y) == '#')
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
            if (grid.Ref(x, y) != '#')
            {
                std::cout << y + 1 << " " << x + 1;
                return 0;
            }
        }
    }

    return 0;
}