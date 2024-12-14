#ifndef ___INCLUDED_PREFIX_SUM___
#define ___INCLUDED_PREFIX_SUM___

#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>

/**
    @brief	    累積和

    @tparam     Iterator   範囲指定に使用するイテレータの型
 */
template <class Iterator>
class PrefixSum
{
public:
    using T = typename std::iterator_traits<Iterator>::value_type; //!< 格納する型

    /**
        @brief	コンストラクタ

        @param[in]	rawData     元となるデータ
    */
    PrefixSum(Iterator beginItr, Iterator endItr)
        : m_data()
    {
        int size = std::distance(beginItr, endItr);
        m_data.resize(size + 1, 0);
        int cur = 0;
        for (decltype(beginItr) itr = beginItr; itr != endItr; itr = std::next(itr))
        {
            m_data[cur + 1] = m_data[cur] + *itr;
            ++cur;
        }
    }

    /**
        @brief	    累積和の取得

        @param[in]	targetIdx   加算を終了するインデックス
        @param[in]	offsetIdx   加算を開始するインデックス
        @return                 累積和
     */
    T GetSum(size_t targetIdx, size_t offsetIdx)
    {
        assert(0 <= targetIdx && targetIdx < m_data.size());
        assert(0 <= offsetIdx && offsetIdx < m_data.size());
        return m_data[targetIdx] - m_data[offsetIdx];
    }

private:
    std::vector<T> m_data; //!< データ構造
};

#endif //___INCLUDED_PREFIX_SUM___

#include <iostream>
#include <vector>

int main()
{
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> A(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A[i];
    }
    PrefixSum acm(A.begin(), A.end());

    while (Q--)
    {
        int L, R;
        std::cin >> L >> R;
        --L, R;
        std::cout << acm.GetSum(R, L) << std::endl;
    }
    return 0;
}