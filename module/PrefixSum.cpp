#ifndef ___INCLUDED_PREFIX_SUM___
#define ___INCLUDED_PREFIX_SUM___

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
    */
    template <class Iterator>
    PrefixSum(Iterator beginItr, Iterator endItr) : m_data()
    {
        int64_t size = std::distance(beginItr, endItr);
        m_data.resize(size + 1, 0);
        int64_t cur = 0;
        for (auto itr = beginItr; itr != endItr; itr = std::next(itr))
        {
            m_data[cur + 1] = m_data[cur] + *itr;
            ++cur;
        }
    }

    /**
        @brief        累積和の取得

        @param[in]    endPos     終了位置
        @param[in]    beginPos   開始位置
        @return       累積和
     */
    T GetSum(int64_t endPos, int64_t beginPos)
    {
        assert(0 <= endPos && endPos < m_data.size());
        assert(0 <= beginPos && beginPos < m_data.size());
        return m_data[endPos] - m_data[beginPos];
    }

  private:
    std::vector<T> m_data; //!< データ構造
};

#endif //___INCLUDED_PREFIX_SUM___