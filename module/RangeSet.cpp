#ifndef ___RANGE_SET___
#define ___RANGE_SET___

#include <set>
#include <limits>
#include <algorithm>

//! @brief	区間をsetで管理する奴
//! @tparam	T 管理する型(整数型のみ)
template <class T>
class RangeSet
{
public:
    //! @brief	区間(閉区間)
    struct Range
    {
        T Left;  //!< 左端
        T Right; //!< 右端

        //! @brief 小なり演算子
        //! @param rhs 右辺
        //! @return 自身 < rhsならtrue
        bool operator<(const Range &rhs) const
        {
            return Left < rhs.Left || !(Left < rhs.Left) && Right < rhs.Right;
        }

        //! @brief 等価演算子
        //! @param rhs 右辺
        //! @return 自身 == rhsならtrue
        bool operator==(const Range &rhs) const
        {
            return Left == rhs.Left && Right == rhs.Right;
        }

        //! @brief 不等価演算子
        //! @param rhs 右辺
        //! @return 自身 != rhsならtrue
        bool operator!=(const Range &rhs) const
        {
            return !(operator==(rhs));
        }
    };

public:
    static const T INF;               //!< 無限大
    static const Range INVALID_RANGE; //!< 無効区間

public:
    //! @brief デフォルトコンストラクタ
    RangeSet()
    {
        m_rangeSet.insert(Range{.Left = INF, .Right = INF});
        m_rangeSet.insert(Range{.Left = -INF, .Right = -INF});
    }

    //! @brief 指定した範囲が含まれるか取得
    //! @param left 範囲の左端
    //! @param right 範囲の右端
    //! @return 含まれていたらtrue
    bool IsCovered(T left, T right)
    {
        Range nearest = GetCoveredBy(left, right);
        return nearest != INVALID_RANGE;
    }

    //! @brief 指定した範囲を含む範囲を取得
    //! @param left 範囲の左端
    //! @param right 範囲の右端
    //! @return 含まれていればその範囲、含まれていなければ{-INF, -INF}
    Range GetCoveredBy(T left, T right)
    {
        auto itr = _GetNearest(left + 1);
        if (itr->Left <= left && right <= itr->Right)
        {
            return *itr;
        }
        return INVALID_RANGE;
    }

    //! @brief 区間を追加する
    //! @param left 区間の左端
    //! @param right 区間の右端
    //! @return 追加することにより増えた範囲の要素数
    T Insert(T left, T right)
    {
        // 完全に既存の範囲に含まれている
        if (IsCovered(left, right))
        {
            return T(0);
        }

        T sumErased = T(0); // 削除された要素数の合計
        T newLeft = left;   // 追加する範囲の左端
        T newRight = right; // 追加する範囲の左端

        auto itr = _GetNearest(left + 1);
        // 近くにある区間の右側が新規範囲に被っているパターン
        if (itr->Left <= left && left <= itr->Right + 1)
        {
            newLeft = itr->Left;
            sumErased += itr->Right - itr->Left + 1;

            // 新規区間の左側を既存の範囲に合わせて、既存のは消してしまう
            itr = m_rangeSet.erase(itr);
        }
        else
        {
            // 一つ右の範囲を見に行く
            itr = std::next(itr);
        }
        // 新規範囲に被っている範囲を根こそぎ消す
        while (right > itr->Right)
        {
            sumErased += itr->Right - itr->Left + 1;
            itr = m_rangeSet.erase(itr);
        }
        // 範囲の左端が新規範囲に被っているパターン
        if (itr->Left <= right && right <= itr->Right)
        {
            sumErased += itr->Right - itr->Left + 1;
            newRight = itr->Right;

            // 新規区間の右側を既存の範囲に合わせて、既存のは消してしまう
            m_rangeSet.erase(itr);
        }

        // 既存の範囲との論理和範囲を追加する
        m_rangeSet.insert(Range{.Left = newLeft, .Right = newRight});
        return newRight - newLeft + 1 - sumErased;
    }

    //! @brief 範囲を削除する
    //! @param left 範囲の左端
    //! @param right 範囲の右端
    //! @return 削除したことにより減った要素数
    T Erase(T left, T right)
    {
        auto itr = _GetNearest(left + 1);

        // 完全に既存の範囲の内側
        if (IsCovered(left, right))
        {
            // 範囲の左側ちょっと残る
            if (itr->Left >= left)
            {
                m_rangeSet.insert(Range{.Left = itr->Left, .Right = left - 1});
            }
            // 範囲の右側ちょっと残る
            if (right >= itr->Right)
            {
                m_rangeSet.insert(Range{.Left = right + 1, .Right = itr->Right});
            }
            m_rangeSet.erase(itr);
            return right - left + 1;
        }

        T sumErased = T(0);
        // 近くにある区間の右側が新規範囲に被っているパターン
        if (itr->Left <= left && left <= itr->Right + 1)
        {
            sumErased += itr->Right - left + 1;
            if (itr->Left < left)
            {
                m_rangeSet.insert(Range{.Left = itr->Left, .Right = left - 1});
            }
            itr = m_rangeSet.erase(itr);
        }
        else
        {
            // 一つ右の範囲を見に行く
            itr = std::next(itr);
        }
        // 新規範囲に被っている範囲を根こそぎ消す
        while (right > itr->Right)
        {
            sumErased += itr->Right - itr->Left + 1;
            itr = m_rangeSet.erase(itr);
        }
        // 範囲の左端が新規範囲に被っているパターン
        if (itr->Left <= right && right <= itr->Right)
        {
            sumErased += right - itr->Left + 1;
            if (right < itr->Right)
            {
                m_rangeSet.insert(Range{.Left = right + 1, .Right = itr->Right});
            }
            itr = m_rangeSet.erase(itr);
        }

        return sumErased;
    }

private:
    //! @brief 指定した点から最も近い位置にある範囲を取得
    //! @param pivot 指定した点
    //! @return 最も近い範囲を指すイテレータ
    typename std::set<Range>::iterator _GetNearest(T pivot)
    {
        return std::prev(m_rangeSet.lower_bound(Range{.Left = pivot, .Right = pivot}));
    }

private:
    std::set<Range> m_rangeSet; //!< 区間が入るコンテナ
};

template <class T>
const T RangeSet<T>::INF = std::numeric_limits<T>::max() / 2;

template <class T>
const typename RangeSet<T>::Range RangeSet<T>::INVALID_RANGE = {.Left = INF, .Right = INF};

#endif //___RANGE_SET___