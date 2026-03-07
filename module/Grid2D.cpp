#ifndef __INCLUDED_GRID2D__
#define __INCLUDED_GRID2D__

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

//! @brief 座標型
struct POSITION
{
    //! @brief 右移動の差分を取得
    //! @return 右移動の差分
    static POSITION R()
    {
        return POSITION(1, 0);
    }

    //! @brief 左移動の差分を取得
    //! @return 左移動の差分
    static POSITION L()
    {
        return POSITION(-1, 0);
    }

    //! @brief 下移動の差分を取得
    //! @return 下移動の差分
    static POSITION D()
    {
        return POSITION(0, 1);
    }

    //! @brief 上移動の差分を取得
    //! @return 上移動の差分
    static POSITION U()
    {
        return POSITION(0, -1);
    }

    static POSITION RLDU(char dir)
    {
        switch (dir)
        {
        case 'R':
            return R();
        case 'L':
            return L();
        case 'D':
            return D();
        case 'U':
            return U();
        default:
            return POSITION();
        }
    }

  public:
    //! @brief デフォルトコンストラクタ
    POSITION() : X(0), Y(0)
    {
    }

    //! @brief コンストラクタ
    //! @param x
    //! @param y
    POSITION(int64_t x, int64_t y) : X(x), Y(y)
    {
    }

    //! @brief コピーコンストラクタ
    //! @param rhs コピー元
    POSITION(const POSITION &rhs) : X(rhs.X), Y(rhs.Y)
    {
    }

    //! @brief コピー代入演算子
    //! @param rhs コピー元
    //! @return 自身の参照
    POSITION &operator=(const POSITION &rhs)
    {
        X = rhs.X;
        Y = rhs.Y;

        return *this;
    }

    //! @brief 加算代入演算子
    //! @param rhs 右辺
    //! @return 自身の参照
    POSITION &operator+=(const POSITION &rhs)
    {
        X += rhs.X;
        Y += rhs.Y;

        return *this;
    }

    //! @brief 減算代入演算子
    //! @param rhs 右辺
    //! @return 自身の参照
    POSITION &operator-=(const POSITION &rhs)
    {
        X -= rhs.X;
        Y -= rhs.Y;

        return *this;
    }

    //! @brief 乗算代入演算子
    //! @param rhs 右辺
    //! @return 自身の参照
    POSITION &operator*=(const POSITION &rhs)
    {
        X *= rhs.X;
        Y *= rhs.Y;

        return *this;
    }

    //! @brief 加算演算子
    //! @param rhs 右辺
    //! @return 加算した結果
    POSITION operator+(const POSITION &rhs) const
    {
        POSITION retval = *this;
        retval += rhs;

        return retval;
    }

    //! @brief 減算演算子
    //! @param rhs 右辺
    //! @return 減算した結果
    POSITION operator-(const POSITION &rhs) const
    {
        POSITION retval = *this;
        retval -= rhs;

        return retval;
    }

    //! @brief 乗算演算子
    //! @param rhs 右辺
    //! @return 乗算した結果
    POSITION operator*(const POSITION &rhs) const
    {
        POSITION retval = *this;
        retval *= rhs;

        return retval;
    }

  public:
    int64_t X; //!< X座標
    int64_t Y; //!< Y座標
};

/**
    @brief    二次元のグリッドを表すクラス

    @tparam    T   格納する型
 */
template <class T>
class Grid2D
{
  public:
    class Iterator
    {
      public:
        //! @brief デフォルトコンストラクタ
        Iterator() : m_pGrid(nullptr), m_position()
        {
        }

        //! @brief コンストラクタ
        //! @param grid グリッド
        //! @param position 初期座標
        Iterator(Grid2D &grid, const POSITION &position) : m_pGrid(&grid), m_position(position)
        {
        }

        //! @brief コピーコンストラクタ
        //! @param rhs コピー元
        Iterator(const Iterator &rhs) : m_pGrid(rhs.m_pGrid), m_position(rhs.m_position)
        {
        }

        //! @brief コピー代入演算子
        //! @param rhs コピー元
        //! @return 自身の参照
        Iterator &operator=(const Iterator &rhs)
        {
            m_pGrid = rhs.m_pGrid;
            m_position = rhs.m_position;

            return *this;
        }

        //! @brief 加算代入演算子
        //! @param rhs 右辺
        //! @return 自身の参照
        Iterator &operator+=(const POSITION &rhs)
        {
            m_position += rhs;

            return *this;
        }

        //! @brief 減算代入演算子
        //! @param rhs 右辺
        //! @return 自身の参照
        Iterator &operator-=(const POSITION &rhs)
        {
            m_position -= rhs;

            return *this;
        }
        //! @brief 加算演算子
        //! @param rhs 右辺
        //! @return 加算の結果
        Iterator operator+(const POSITION &rhs) const
        {
            Iterator retval = *this;
            retval += rhs;

            return retval;
        }

        //! @brief 減算演算子
        //! @param rhs 右辺
        //! @return 減算の結果
        Iterator operator-(const POSITION &rhs) const
        {
            Iterator retval = *this;
            retval -= rhs;

            return retval;
        }

        //! @brief 参照演算子
        //! @return 指している先の参照
        T &operator*() const
        {
            return m_pGrid->Ref(m_position.X, m_position.Y);
        }

        //! @brief 指している先が範囲内か
        //! @return 範囲内ならtrue
        bool IsInner() const
        {
            return m_pGrid->IsInner(m_position.X, m_position.Y);
        }

        //! @brief インデックス取得
        //! @return インデックス
        int64_t GetIndex() const
        {
            return m_pGrid->GetIndex(m_position.X, m_position.Y);
        }

      private:
        Grid2D *m_pGrid;     //!< グリッドのポインタ
        POSITION m_position; //!< 指している座標
    };

  public:
    /**
        @brief    コンストラクタ

        @param[in]    height          高さ
        @param[in]    width           幅
        @param[in]    initialValue    初期値
    */
    Grid2D(int64_t height, int64_t width, T initialValue)
        : m_data(height * width, initialValue), m_width(width), m_height(height)
    {
    }

    //! @brief コピーコンストラクタ
    //! @param rhs コピー元
    Grid2D(const Grid2D<T> &rhs)
        : m_data(rhs.GetHeight() * rhs.GetWidth()), m_width(rhs.GetWidth()), m_height(rhs.GetHeight())
    {
        int64_t sz = GetWidth() * GetHeight();
        for (int64_t idx = 0; idx < sz; ++idx)
        {
            m_data[idx] = rhs.m_data[idx];
        }
    }

    //! @brief コピー代入演算子
    //! @param rhs コピー元
    //! @return 自身の参照
    Grid2D<T> &operator=(const Grid2D<T> &rhs)
    {
        m_width = rhs.GetWidth();
        m_height = rhs.GetHeight();

        int64_t sz = GetWidth() * GetHeight();
        m_data.resize(sz);

        for (int64_t idx = 0; idx < sz; ++idx)
        {
            m_data[idx] = rhs.m_data[idx];
        }

        return *this;
    }

    /**
        @brief            指定した座標の値にアクセスする

        @param[in]    x   X座標
        @param[in]    y   Y座標

        @return         目的の座標の参照
     */
    T &Ref(int64_t x, int64_t y)
    {
        return const_cast<T &>(Get(x, y));
    }

    /**
        @brief            指定した座標の値を読み取る

        @param[in]    x   X座標
        @param[in]    y   Y座標

        @return         目的の座標の参照
     */
    const T &Get(int64_t x, int64_t y) const
    {
        return m_data[GetIndex(x, y)];
    }

    /**
        @brief    高さの取得

        @return ���さ
     */
    int64_t GetHeight() const
    {
        return m_height;
    }

    /**
        @brief    幅の取得

        @return 幅
     */
    int64_t GetWidth() const
    {
        return m_width;
    }

    /**
        @brief    Indexの取得

        @param[in]    x       X座標
        @param[in]    y       Y座標

        @return     Index
     */
    int64_t GetIndex(int64_t x, int64_t y) const
    {
        assert(IsInner(x, y));

        return y * m_width + x;
    }

    /**
        @brief        X座標を取得する

        @param[in]    idx     インデックス

        @return     X座標
     */
    int64_t GetX(int64_t idx) const
    {
        assert(0 <= idx && idx < m_height * m_width);

        return idx % m_width;
    }

    /**
        @brief        Y座標を取得する

        @param[in]    idx     インデックス

        @return     Y座標
     */
    int64_t GetY(int64_t idx) const
    {
        assert(0 <= idx && idx < m_height * m_width);

        return idx / m_width;
    }

    /**
        @brief            座標がグリッドの内部か否か

        @param[in]    x       X座標
        @param[in]    y       Y座標

        @retval     true    グリッドの内部にいる
        @retval     false   グリッドの外側
     */
    bool IsInner(int64_t x, int64_t y) const
    {
        return 0 <= x && x < m_width && 0 <= y && y < m_height;
    }

    /**
        @brief        全てのマスに対して操作する

        @tparam     Func    関数の型

        @param[in]    func    操作する関数(引数としてidxとその地点の値が貰える)
     */
    template <class Func>
    void ForEach(Func func)
    {
        for (int i = 0; i < m_width * m_height; ++i)
        {
            func(i, m_data[i]);
        }
    }

    //! @brief 不等価演算子
    //! @param rhs 比較先
    //! @return 不一致ならtrue
    bool operator!=(const Grid2D<T> &rhs) const
    {
        if (GetHeight() != rhs.GetHeight() || GetWidth() != rhs.GetWidth())
        {
            return true;
        }
        for (int64_t y = 0; y < GetHeight(); ++y)
        {
            for (int64_t x = 0; x < GetWidth(); ++x)
            {
                if (Get(x, y) != rhs.Get(x, y))
                {
                    return true;
                }
            }
        }
        return false;
    }

    //! @brief 等価演算子
    //! @param rhs 比較先
    //! @return 一致したらtrue
    bool operator==(const Grid2D<T> &rhs) const
    {
        return !operator!=(rhs);
    }

    //! @brief イテレータ取得
    //! @param idx インデックス
    //! @return イテレータ
    Iterator GetItr(int64_t idx)
    {
        return GetItr(GetX(idx), GetY(idx));
    }

    //! @brief イテレータ取得
    //! @param x X座標
    //! @param y Y座標
    //! @return イテレータ
    Iterator GetItr(int64_t x, int64_t y)
    {
        return GetItr({x, y});
    }

    //! @brief イテレータ取得
    //! @param position 座標
    //! @return イテレータ
    Iterator GetItr(const POSITION &position)
    {
        return Iterator(*this, position);
    }

  private:
    std::vector<T> m_data; //!< 本体となる配列
    int64_t m_width;       //!< 幅
    int64_t m_height;      //!< 高さ

    template <class U>
    friend std::istream &operator>>(std::istream &stream, Grid2D<U> &dest);
};

/**
    @brief            入力ストリーム演算子

    @tparam    T       Grid2Dに格納する型
    @param[in]        stream  入力ストリーム
    @param[in]        dest    入力を受け付ける先のGrid2D

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

namespace std
{
/**
        @brief	2次元グリッドクラスのハッシュ値を計算する

        @tparam	 Grid2Dを指定
     */
template <class T>
struct hash<Grid2D<T>>
{
    /**
            @brief	呼び出し演算子

            @param[in]	val 対象
            @return ハッシュ値
         */
    size_t operator()(const Grid2D<T> &src) const
    {
        size_t retval = 0;

        for (int64_t y = 0; y < src.GetHeight(); ++y)
        {
            for (int64_t x = 0; x < src.GetWidth(); ++x)
            {
                retval <<= 7;
                retval ^= src.Get(x, y);
            }
        }
        return retval;
    }
};
} // namespace std

#endif //__INCLUDED_GRID2D__