#ifndef ___INCLUDED_BINARY_SEARCH___
#define ___INCLUDED_BINARY_SEARCH___

#include <cstdint>
#include <cmath>

template <class F>
int64_t BinarySearch(int64_t ng, int64_t ok, F comp)
{
    int64_t mid;
    while (std::abs(ng - ok) > 1)
    {
        mid = (ng + ok) / 2;
        if (comp(mid))
        {
            ok = mid;
        }
        else
        {
            ng = mid;
        }
    }
    return ok;
}

#endif //___INCLUDED_BINARY_SEARCH___

#ifndef ___INCLUDED_PREFIX_SUM___
#define ___INCLUDED_PREFIX_SUM___

#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>

/**
    @brief        累積和

    @tparam     Iterator   範囲指定に使用するイテレータの型
 */
template <class Iterator>
class PrefixSum
{
public:
    using T = typename std::iterator_traits<Iterator>::value_type; //!< 格納する型

    /**
        @brief    コンストラクタ

        @param[in]    rawData     元となるデータ
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
        @brief        累積和の取得

        @param[in]    targetIdx   加算を終了するインデックス
        @param[in]    offsetIdx   加算を開始するインデックス
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
#include <algorithm>

int main()
{
    int64_t N, S;
    std::cin >> N >> S;
    int64_t orgS = S;
    std::vector<int64_t> A(N);
    int64_t sum = 0;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A[i];
        sum += A[i];
    }
    PrefixSum acm(A.begin(), A.end());
    PrefixSum revAcm(A.rbegin(), A.rend());

    S %= sum;

    for (int i = 0; i <= N; ++i)
    {
        int64_t backSum = acm.GetSum(i, 0);
        if (backSum > S)
        {
            break;
        }
        int64_t result = BinarySearch(N + 1, -1, [&](int64_t cur)
                                      { return (revAcm.GetSum(cur, 0)) <= S - backSum; });
        if (0 <= result && result <= N && backSum + revAcm.GetSum(result, 0) == S)
        {
            std::cout << "Yes" << std::endl;
            return 0;
        }
    }

    if (orgS <= sum)
    {
        std::cout << "No" << std::endl;
        return 0;
    }
    S += sum;
    for (int i = 0; i <= N; ++i)
    {
        int64_t backSum = acm.GetSum(i, 0);
        if (backSum > S)
        {
            break;
        }
        int64_t result = BinarySearch(N + 1, -1, [&](int64_t cur)
                                      { return (revAcm.GetSum(cur, 0)) <= S - backSum; });
        if (0 <= result && result <= N && backSum + revAcm.GetSum(result, 0) == S)
        {
            std::cout << "Yes" << std::endl;
            return 0;
        }
    }
    std::cout << "No" << std::endl;

    return 0;
}