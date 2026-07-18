#ifndef __INCLUDED_GRID2D__
#define __INCLUDED_GRID2D__

#include "Grid3D.cpp"

//! @brief 二次元のグリッドを表すクラス
//! @tparam T 格納する型
template <class T>
class Grid2D : public Grid3D<T>
{
    using BaseClass = Grid3D<T>;

  public:
    using Iterator = BaseClass::Iterator; //!< イテレータの型

  public:
    //! @brief デフォルトコンストラクタ
    Grid2D() : BaseClass()
    {
    }

    /**
        @brief    コンストラクタ

        @param[in]    height          高さ
        @param[in]    width           幅
        @param[in]    initialValue    初期値
    */
    Grid2D(int64_t H, int64_t W, T initialValue) : BaseClass(H, W, 1, initialValue)
    {
    }

    /**
        @brief            指定した座標の値にアクセスする

        @param[in]    x   X座標
        @param[in]    y   Y座標

        @return         目的の座標の参照
     */
    T &Ref(int64_t x, int64_t y)
    {
        return const_cast<T &>(BaseClass::Get(x, y, 0));
    }

    /**
        @brief            指定した座標の値を読み取る

        @param[in]    x   X座標
        @param[in]    y   Y座標

        @return         目的の座標の参照
     */
    const T &Get(int64_t x, int64_t y) const
    {
        return BaseClass::Get(x, y, 0);
    }

    /**
        @brief    Indexの取得

        @param[in]    x       X座標
        @param[in]    y       Y座標

        @return     Index
     */
    int64_t GetIndex(int64_t x, int64_t y) const
    {
        return BaseClass::GetIndex(x, y, 0);
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
        return BaseClass::IsInner(x, y, 0);
    }

    //! @brief イテレータ取得
    //! @param x X座標
    //! @param y Y座標
    //! @return イテレータ
    Iterator GetItr(int64_t x, int64_t y)
    {
        return GetItr({x, y, 0});
    }

    using BaseClass::GetItr;
};

#endif //__INCLUDED_GRID2D__