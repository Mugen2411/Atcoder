#ifndef ___INCLUDED_SEGMENT_TREE___
#define ___INCLUDED_SEGMENT_TREE___

#include <vector>
#include <limits>
#include <cstdint>
#include <functional>

/**
    @brief            セグメント木

    @tparam    T       管理する型
 */
template <class T>
class SegmentTree
{
public:
    using MergeFuncType = std::function<bool(T, T)>; //!< 比較関数の型

    /**
        @brief    コンストラクタ

        @param[in]    size          要素数
        @param[in]    limitValue    最もcompareFuncではない値
        @param[in]    compareFunc   比較関数
    */
    SegmentTree(size_t size, T limitValue, MergeFuncType compareFunc)
        : m_data(size * 4, limitValue), m_size(0), LIMIT_VALUE(limitValue), m_mergeFunc(compareFunc)
    {
        int x = 1;
        while (size > x)
        {
            x *= 2;
        }
        m_size = x;
    }

    /**
        @brief        更新

        @param[in]    position    更新する位置
        @param[in]    value       更新する値
     */
    void Update(size_t position, T value)
    {
        position += m_size - 1; // 配列上の位置に移動
        m_data[position] = value;
        while (position > 0)
        {
            position = (position - 1) / 2;                                                  // 1つ親に移動
            m_data[position] = _Merge(m_data[position * 2 + 1], m_data[position * 2 + 2]); // 2つの子を比較してFuncな方を選ぶ
        }
    }

    /**
        @brief            クエリ

        @param[in]    l   範囲の左端
        @param[in]    r   範囲の右端

        @return         範囲内で最もFuncな値
     */
    T Query(size_t l, size_t r)
    {
        return QueryImpl(l, r, 0, 0, m_size);
    }

    /**
        @brief        クエリの本体部分

        @param[in]    queryL          クエリで与えられた左端
        @param[in]    queryR          クエリで与えられた右端
        @param[in]    currentIdx      今見ているインデックス
        @param[in]    rangeBegins     今見ている範囲が始まるインデックス
        @param[in]    rangeEnds       今見ている範囲が終わるインデックス

        @return     右半分と左半分にFuncを適用した値
     */
    T QueryImpl(size_t queryL, size_t queryR, size_t currentIdx, size_t rangeBegins, size_t rangeEnds)
    {
        if (rangeEnds <= queryL || queryR <= rangeBegins)
        {
            return LIMIT_VALUE;
        }

        if (queryL <= rangeBegins && rangeEnds <= queryR)
        {
            return m_data[currentIdx];
        }

        // 今見ている範囲の左の子の値
        T vl = QueryImpl(queryL, queryR, currentIdx * 2 + 1, rangeBegins, (rangeBegins + rangeEnds) / 2);
        // 今見ている範囲の右の子の値
        T vr = QueryImpl(queryL, queryR, currentIdx * 2 + 2, (rangeBegins + rangeEnds) / 2, rangeEnds);

        return _Merge(vl, vr);
    }

    /**
        @brief	            指定した範囲内でvalueよりFuncな最も右のインデックスを取得する

        @param[in]	l       範囲の左端
        @param[in]	r       範囲の右端
        @param[in]	value   比較する値
        @return             インデックス
     */
    size_t FindRightest(size_t l, size_t r, T value)
    {
    }

    /**
        @brief        最右位置取得の本体部分

        @param[in]    queryL          クエリで与えられた左端
        @param[in]    queryR          クエリで与えられた右端
        @param[in]    value           比較対象の値
        @param[in]    currentIdx      今見ているインデックス
        @param[in]    rangeBegins     今見ている範囲が始まるインデックス
        @param[in]    rangeEnds       今見ている範囲が終わるインデックス

        @return     右半分と左半分にFuncを適用した値
     */
    size_t FindRightestImpl(size_t queryL, size_t queryR, T value, size_t currentIdx, size_t rangeBegins, size_t rangeEnds)
    {
        if (rangeEnds <= queryL || queryR <= rangeBegins)
        {
            return LIMIT_VALUE;
        }

        if (queryL <= rangeBegins && rangeEnds <= queryR)
        {
            return m_data[currentIdx];
        }
    }

private:
    T _Merge(T lhs, T rhs)
    {
        if (m_mergeFunc(lhs, rhs))
        {
            return lhs;
        }
        else
        {
            return rhs;
        }
    }

private:
    std::vector<T> m_data;  //!< 管理されるデータ本体
    size_t m_size;          //!< 管理部分を除いた本体のサイズ
    const T LIMIT_VALUE;    //!< 単位元
    MergeFuncType m_mergeFunc; //!< 比較関数
};

#endif //___INCLUDED_SEGMENT_TREE___

#include <iostream>

int main()
{
    int64_t N, Q;
    std::cin >> N >> Q;

    SegmentTree<uint64_t> segTree(N, std::numeric_limits<uint64_t>::min(), [](uint64_t lhs, uint64_t rhs)
                                  { return lhs > rhs; });
    while (Q--)
    {
        int cmd;
        std::cin >> cmd;
        switch (cmd)
        {
        case 1:
        {
            int64_t pos, x;
            std::cin >> pos >> x;
            --pos;

            segTree.Update(pos, x);
        }
        break;
        case 2:
        {
            int64_t l, r;
            std::cin >> l >> r;
            --l, --r;

            std::cout << segTree.Query(l, r) << std::endl;
        }
        break;
        }
    }

    return 0;
}