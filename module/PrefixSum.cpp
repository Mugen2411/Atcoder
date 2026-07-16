#ifndef ___INCLUDED_PREFIX_SUM___
#define ___INCLUDED_PREFIX_SUM___

#include "Grid3D.cpp"
#include <algorithm>
#include <cassert>
#include <iterator>
#include <vector>

/**
    @brief        累積和

    @tparam     T 管理する数値型(整数ほぼ前提？)
 */
template <class T>
class PrefixSum
{
  public:
    /**
        @brief    コンストラクタ

        @param[in]    rawData     元となるデータ
        @note         旧互換用。1次元データ
    */
    template <class Iterator>
    PrefixSum(Iterator beginItr, Iterator endItr) : m_data(2, std::distance(beginItr, endItr) + 1, 2, 0)
    {
        int64_t curIdx = 0;
        for (auto itr = beginItr; itr != endItr; ++itr)
        {
            m_data.Ref(curIdx + 1, 1, 1) = *itr;
            ++curIdx;
        }
        _Prepare();
    }

    //! @brief コンストラクタ
    //! @param input 元となるデータ
    PrefixSum(Grid3D<T> &input) : m_data(input.GetHeight() + 1, input.GetWidth() + 1, input.GetDepth() + 1, 0)
    {
        for (int z = 0; z < input.GetDepth(); ++z)
        {
            for (int y = 0; y < input.GetHeight(); ++y)
            {
                for (int x = 0; x < input.GetWidth(); ++x)
                {
                    m_data.Ref(x + 1, y + 1, z + 1) = input.Ref(x, y, z);
                }
            }
        }

        _Prepare();
    }

    //! @brief 累積和の取得
    //! @param Rx 終点のX
    //! @param Lx 始点のX
    //! @param Ry 終点のY
    //! @param Ly 始点のY
    //! @param Rz 終点のZ
    //! @param Lz 始点のZ
    //! @return 指定した区間の累積和
    T GetSum(int64_t Rx, int64_t Lx, int64_t Ry, int64_t Ly, int64_t Rz, int64_t Lz)
    {
        T a = m_data.Get(Rx, Ry, Rz);
        T b = m_data.Get(Rx, Ry, Lz);
        T c = m_data.Get(Rx, Ly, Rz);
        T d = m_data.Get(Lx, Ry, Rz);
        T e = m_data.Get(Rx, Ly, Lz);
        T f = m_data.Get(Lx, Ly, Rz);
        T g = m_data.Get(Lx, Ry, Lz);
        T h = m_data.Get(Lx, Ly, Lz);

        return a - b - c - d + e + f + g - h;
    }

    //! @brief 累積和の取得
    //! @param Rx 終点のX
    //! @param Lx 始点のX
    //! @param Ry 終点のY
    //! @param Ly 始点のY
    //! @return 指定した区間の累積和
    T GetSum(int64_t Rx, int64_t Lx, int64_t Ry, int64_t Ly)
    {
        return GetSum(Rx, Lx, Ry, Ly, 1, 0);
    }

    //! @brief 累積和の取得
    //! @param Rx 終点のX
    //! @param Lx 始点のX
    //! @return 指定した区間の累積和
    T GetSum(int64_t Rx, int64_t Lx)
    {
        return GetSum(Rx, Lx, 1, 0, 1, 0);
    }

  private:
    //! @brief 準備
    void _Prepare()
    {
        for (int z = 0; z < m_data.GetDepth(); ++z)
        {
            for (int y = 0; y < m_data.GetHeight(); ++y)
            {
                for (int x = 0; x < m_data.GetWidth() - 1; ++x)
                {
                    m_data.Ref(x + 1, y, z) += m_data.Ref(x, y, z);
                }
            }
        }
        for (int z = 0; z < m_data.GetDepth(); ++z)
        {
            for (int x = 0; x < m_data.GetWidth(); ++x)
            {
                for (int y = 0; y < m_data.GetHeight() - 1; ++y)
                {
                    m_data.Ref(x, y + 1, z) += m_data.Ref(x, y, z);
                }
            }
        }
        for (int y = 0; y < m_data.GetHeight(); ++y)
        {
            for (int x = 0; x < m_data.GetWidth(); ++x)
            {
                for (int z = 0; z < m_data.GetDepth() - 1; ++z)
                {
                    m_data.Ref(x, y, z + 1) += m_data.Ref(x, y, z);
                }
            }
        }
    }

  private:
    Grid3D<T> m_data; //!< データ構造
};

#endif //___INCLUDED_PREFIX_SUM___