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
    using MergeFuncType = std::function<T(T, T)>; //!< 比較関数の型

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
            position = (position - 1) / 2;                                                      // 1つ親に移動
            m_data[position] = m_mergeFunc(m_data[position * 2 + 1], m_data[position * 2 + 2]); // 2つの子を比較してFuncな方を選ぶ
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

        return m_mergeFunc(vl, vr);
    }

    /**
        @brief	            指定した範囲内でvalueよりFuncな最も右のインデックスを取得する

        @param[in]	l       範囲の左端
        @param[in]	r       範囲の右端
        @param[in]	cond    二分探索の条件
        @return             インデックス
     */
    template <class Condition>
    size_t FindRight(size_t l, size_t r, Condition cond)
    {
        return FindRightImpl(l, r, cond, 0, 0, m_size);
    }

    /**
        @brief        最右位置取得の本体部分

        @param[in]    queryL          クエリで与えられた左端
        @param[in]    queryR          クエリで与えられた右端
        @param[in]    cond            二分探索の条件
        @param[in]    currentIdx      今見ているインデックス
        @param[in]    rangeBegins     今見ている範囲が始まるインデックス
        @param[in]    rangeEnds       今見ている範囲が終わるインデックス

        @return     valueよりFuncな最も右のインデックス
     */
    template <class Condition>
    size_t FindRightImpl(size_t queryL, size_t queryR, Condition cond, size_t currentIdx, size_t rangeBegins, size_t rangeEnds)
    {
        // 自分の値が自分よりFuncであるor範囲外なら不正値を返す
        if (!cond(m_data[currentIdx]) || rangeEnds <= queryL || queryR <= rangeBegins)
        {
            return INVALID;
        }

        // 自分が葉ならその位置を返す
        if (currentIdx >= m_size - 1)
        {
            return currentIdx - (m_size - 1);
        }

        // 自分より右を見る
        size_t idxR = FindRightImpl(queryL, queryR, cond, currentIdx * 2 + 2, (rangeBegins + rangeEnds) / 2, rangeEnds);
        // 右にあったら返す
        if (idxR != INVALID)
        {
            return idxR;
        }
        // 無いなら左から返す
        return FindRightImpl(queryL, queryR, cond, currentIdx * 2 + 1, rangeBegins, (rangeBegins + rangeEnds) / 2);
    }

    /**
        @brief	            指定した範囲内でvalueよりFuncな最も左のインデックスを取得する

        @param[in]	l       範囲の左端
        @param[in]	r       範囲の右端
        @param[in]	cond    二分探索の条件
        @return             インデックス
    */
    template <class Condition>
    size_t FindLeft(size_t l, size_t r, Condition cond)
    {
        return FindLeftImpl(l, r, cond, 0, 0, m_size);
    }

    /**
        @brief        最左位置取得の本体部分

        @param[in]    queryL          クエリで与えられた左端
        @param[in]    queryR          クエリで与えられた右端
        @param[in]    cond            二分探索の条件
        @param[in]    currentIdx      今見ているインデックス
        @param[in]    rangeBegins     今見ている範囲が始まるインデックス
        @param[in]    rangeEnds       今見ている範囲が終わるインデックス

        @return     valueよりFuncな最も左のインデックス
     */
    template <class Condition>
    size_t FindLeftImpl(size_t queryL, size_t queryR, Condition cond, size_t currentIdx, size_t rangeBegins, size_t rangeEnds)
    {
        // 自分の値が自分よりFuncであるor範囲外なら不正値を返す
        if (!cond(m_data[currentIdx]) || rangeEnds <= queryL || queryR <= rangeBegins)
        {
            return INVALID;
        }

        // 自分が葉ならその位置を返す
        if (currentIdx >= m_size - 1)
        {
            return currentIdx - (m_size - 1);
        }

        // 自分より左を見る
        size_t idxL = FindLeftImpl(queryL, queryR, cond, currentIdx * 2 + 1, rangeBegins, (rangeBegins + rangeEnds) / 2);
        // 左にあったら返す
        if (idxL != INVALID)
        {
            return idxL;
        }
        // 無いなら右から返す
        return FindLeftImpl(queryL, queryR, cond, currentIdx * 2 + 2, (rangeBegins + rangeEnds) / 2, rangeEnds);
    }

private:
    std::vector<T> m_data;     //!< 管理されるデータ本体
    size_t m_size;             //!< 管理部分を除いた本体のサイズ
    const T LIMIT_VALUE;       //!< 単位元
    MergeFuncType m_mergeFunc; //!< 比較関数

public:
    inline static constexpr size_t INVALID = std::numeric_limits<size_t>::max(); //!< 不正を示す定数
};

#endif //___INCLUDED_SEGMENT_TREE___