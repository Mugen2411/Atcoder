#ifndef ___RANGE_SET___
#define ___RANGE_SET___

#include <algorithm>
#include <limits>
#include <set>

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
        // 新規範囲に被っている範囲を根こそぎ���す
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
#ifndef ___INCLUDED_BINARY_SEARCH___
#define ___INCLUDED_BINARY_SEARCH___

#include <cmath>
#include <cstdint>

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
#ifndef ___INCLUDED_BITMAN___
#define ___INCLUDED_BITMAN___

#include <iostream>

/**
    @brief	ビット管理型
 */
class BitManager
{
  public:
    /**
        @brief	デフォルトコンストラクタ
    */
    BitManager() : m_data(0ull) {};

    /**
        @brief	コンストラクタ

        @param[in]	val 初期値
     */
    BitManager(uint64_t val) : m_data(val) {};

    /**
        @brief	uint64_t型への変換を許可する

        @return uint64_t型に��換されたデータ
    */
    operator uint64_t() const
    {
        return m_data;
    }

    /**
        @brief	全てfalseで初期化されたビットマネージャを取得

        @return 全てfalseで初期化されたビットマネージャ
     */
    static BitManager AllFalse()
    {
        return Filled(0);
    }

    /**
        @brief	全てtrueで初期化されたビットマネージャを取得

        @return 全てtrueで初期化されたビットマネ��ジャ
     */
    static BitManager AllTrue()
    {
        return Filled(NUM_DIGIT);
    }

    /**
        @brief	差分で初期化されたビットマネージャ

        @param[in]	lhs 左辺
        @param[in]	rhs 右辺
        @return 左辺と右辺で異なるビットだけ立てたビットマネージャ
     */
    static BitManager Difference(const BitManager &lhs, const BitManager &rhs)
    {
        return BitManager(lhs.m_data ^ rhs.m_data);
    }

    /**
        @brief	下からnum個のビットをtrueで埋め、それ以外がfalseのビットマネージャ

        @param[in]	num ビットを立てる個数
        @return 概要通りのビットマネージャ
     */
    static BitManager Filled(int num)
    {
        _ValidateBitNum(num);

        BitManager retval = 0;
        for (int i = 0; i < num; ++i)
        {
            retval.Set(i, true);
        }
        return retval;
    }

    /**
        @brief	1つの要素だけtrue、��がfalseのビットマネージャ

        @param[in]	idx trueにするインデックス
        @return 概要を満たすビットマネージャ
     */
    static BitManager Onehot(int idx)
    {
        BitManager retval = AllFalse();
        retval.Set(idx, true);
        return retval;
    }

    /**
        @brief	コピーコンストラクタ

        @param[in]	rhs コピー元
     */
    BitManager(const BitManager &rhs) : m_data(rhs.m_data)
    {
    }

    /**
        @brief	コピー代入演算子

        @param[in]	rhs コピー元
        @return 自身の参照
     */
    BitManager &operator=(const BitManager &rhs)
    {
        m_data = rhs.m_data;
        return *this;
    }

    /**
        @brief	idx番目のビットが立っているか取得する

        @param[in]	idx インデックス
        @return idx番目のビット
     */
    bool Get(int idx)
    {
        _ValidateIndex(idx);
        return m_data & (1ull << idx);
    }

    /**
        @brief	idx番目のビットをvalにする

        @param[in]	idx インデックス
        @param[in]	val 適用する状態
     */
    void Set(int idx, bool val)
    {
        _ValidateIndex(idx);
        uint64_t filter = 1ull << idx;
        if (val)
        {
            m_data |= filter;
        }
        else
        {
            m_data &= ~filter;
        }
    }

    /**
        @brief	trueになっているビットの数を取得

        @return trueになっているビットの数
     */
    int GetCount()
    {
        int retval = 0;
        for (int i = 0; i < NUM_DIGIT; ++i)
        {
            if (Get(i))
            {
                ++retval;
            }
        }
        return retval;
    }

    /**
        @brief	フラグの内容をでバッグ出力する
        @note   提出などでは使わない想定
     */
    void DebugOutput()
    {
        for (int i = 0; i < NUM_DIGIT; ++i)
        {
            if ((m_data >> i) & 1)
            {
                std::cerr << 1;
            }
            else
            {
                std::cerr << 0;
            }
        }
        std::cerr << std::endl;
    }

    /**
        @brief	前置インクリメント演算子

        @return 自身の参照
     */
    BitManager &operator++()
    {
        ++m_data;
        return *this;
    }

    /**
        @brief	後置インクリメント演算子

        @return インクリ��ント前のコピー
     */
    BitManager operator++(int)
    {
        BitManager retval = *this;
        operator++();
        return retval;
    }

    /**
        @brief	等価演算子

        @param[in]	rhs 比較対象
        @return 自身と右辺が等しいか
     */
    bool operator==(const BitManager &rhs)
    {
        return m_data == rhs.m_data;
    }

    /**
        @brief	不等価演算子

        @param[in]	rhs 比較対象
        @return 自身と右��が等しくないか
     */
    bool operator!=(const BitManager &rhs)
    {
        return !operator==(rhs);
    }

  private:
    /**
        @brief	インデックスが正しいか検証する

        @param[in]	idx インデックス
     */
    static void _ValidateIndex(int idx)
    {
        if (idx < 0 || NUM_DIGIT <= idx)
        {
            std::cerr << "BitManager: Index Error!" << std::endl;
        }
    }

    /**
        @brief	ビットの個数指定が正しいか検証する

        @param[in]	num 個数
     */
    static void _ValidateBitNum(int num)
    {
        if (num < 0 || NUM_DIGIT < num)
        {
            std::cerr << "BitManager: Bit Num Error!" << std::endl;
        }
    }

  public:
    static constexpr int NUM_DIGIT = 64; //!< 桁数

  private:
    uint64_t m_data; //!< 本体
};

namespace std
{
/**
        @brief	ビット管理クラスのハッシュ値を計算する

        @tparam	 BitManagerを指定
     */
template <>
struct hash<BitManager>
{
    /**
            @brief	呼び出し演算子

            @param[in]	val 対象
            @return ハッシュ値
         */
    size_t operator()(const BitManager &val) const
    {
        return std::hash<uint64_t>()(val);
    }
};
} // namespace std

#endif //___INCLUDED_BITMAN___

#ifndef ___INCLUDED_FRACTION___
#define ___INCLUDED_FRACTION___

#include <cmath>
#include <cstdint>

/**
    @brief	    分数クラス
 */
class Fraction
{
  public:
    /**
        @brief	コンストラクタ

        @param[in]	numerator       分子
        @param[in]	denominator     分母
    */
    Fraction(int64_t numerator, int64_t denominator) : m_denominator(denominator), m_numerator(numerator)
    {
        _Reduce();
    }

    /**
        @brief	コンストラク���

        @param[in]	intValue       整数値
    */
    Fraction(int64_t intValue) : m_denominator(1), m_numerator(intValue)
    {
    }

    /**
        @brief	コピーコンストラクタ

        @param[in]  rhs     右辺
     */
    Fraction(const Fraction &rhs) : m_denominator(rhs.m_denominator), m_numerator(rhs.m_numerator)
    {
    }

    /**
        @brief	コピー代入

        @param[in]	rhs     右辺

        @return 自分の参照
     */
    Fraction &operator=(const Fraction &rhs)
    {
        m_denominator = rhs.m_denominator;
        m_numerator = rhs.m_numerator;

        return *this;
    }

    /**
        @brief	コピー代入演算子

        @param[in]	intValue       整数値
    */
    Fraction &operator=(int64_t intValue)
    {
        m_denominator = 1;
        m_numerator = intValue;
        return *this;
    }

    /**
        @brief	    等価演算子

        @param[in]	rhs     右辺

        @retval true        等しい
        @retval false       等しくない
     */
    bool operator==(const Fraction &rhs) const
    {
        return m_denominator == rhs.m_denominator && m_numerator == rhs.m_numerator;
    }

    /**
        @brief	    不等価演算子

        @param[in]	rhs     右辺

        @retval true        等しくない
        @retval false       等しい
     */
    bool operator!=(const Fraction &rhs) const
    {
        return !(*this == rhs);
    }

    /**
        @brief	    加算代入演算子

        @param[in]	rhs     右辺
        @return     自分の参照
     */
    Fraction &operator+=(const Fraction &rhs)
    {
        m_denominator = m_denominator * rhs.m_denominator;
        m_numerator = m_numerator * rhs.m_denominator + rhs.m_numerator * rhs.m_denominator;
        _Reduce();
        return *this;
    }

    /**
        @brief	    減算代入演算子

        @param[in]	rhs     右辺
        @return     自分の参照
     */
    Fraction &operator-=(const Fraction &rhs)
    {
        m_denominator = m_denominator * rhs.m_denominator;
        m_numerator = m_numerator * rhs.m_denominator - rhs.m_numerator * rhs.m_denominator;
        _Reduce();
        return *this;
    }

    /**
        @brief	    乗算代入演算子

        @param[in]	rhs     右辺
        @return     自分の参照
     */
    Fraction &operator*=(const Fraction &rhs)
    {
        m_denominator = m_denominator * rhs.m_denominator;
        m_numerator = m_numerator * rhs.m_numerator;
        _Reduce();
        return *this;
    }

    /**
        @brief	    除算代入演算子

        @param[in]	rhs     右辺
        @return     自分の参照
     */
    Fraction &operator/=(const Fraction &rhs)
    {
        m_denominator = m_denominator * rhs.m_numerator;
        m_numerator = m_numerator * rhs.m_denominator;
        _Reduce();
        return *this;
    }

    /**
        @brief	    加算演算子

        @param[in]	rhs     右辺
        @return     コピー
     */
    Fraction operator+(const Fraction &rhs)
    {
        Fraction retval = *this;
        retval += rhs;

        return *this;
    }

    /**
        @brief	    減算演算子

        @param[in]	rhs     右辺
        @return     コピー
     */
    Fraction operator-(const Fraction &rhs)
    {
        Fraction retval = *this;
        retval -= rhs;

        return *this;
    }

    /**
        @brief	    乗算演算子

        @param[in]	rhs     右辺
        @return     コピー
     */
    Fraction operator*(const Fraction &rhs)
    {
        Fraction retval = *this;
        retval *= rhs;

        return *this;
    }

    /**
        @brief	    除算演算子

        @param[in]	rhs     右辺
        @return     コピー
     */
    Fraction operator/(const Fraction &rhs)
    {
        Fraction retval = *this;
        retval /= rhs;

        return *this;
    }

  private:
    /**
        @brief	    最大公約数を求める

        @param[in]	lhs     左辺
        @param[in]	rhs     右辺

        @retval     0       エラー
        @return     lhsとrhsの最大公約数
     */
    int64_t _CalcGCD(int64_t lhs, int64_t rhs)
    {
        // エラーチェック
        if (lhs == 0 || rhs == 0)
        {
            return 0;
        }

        lhs = std::abs(lhs);
        rhs = std::abs(rhs);

        // 大小関係を保証
        if (lhs < rhs)
        {
            int64_t ret = lhs;
            lhs = rhs;
            rhs = ret;
            ret = 0;
        }

        // ユークリッドの互除法
        int64_t tmp = lhs % rhs;
        while (tmp != 0)
        {
            lhs = rhs;
            rhs = tmp;
            tmp = lhs % rhs;
        }

        return rhs;
    }

    /**
        @brief	約分する
     */
    void _Reduce()
    {
        int64_t gcd = _CalcGCD(m_numerator, m_denominator);

        // ダメ���ら無効にする
        if (gcd == 0)
        {
            m_numerator = 0;
            m_denominator = 0;
            return;
        }

        m_numerator /= gcd;
        m_denominator /= gcd;
    }

  private:
    int64_t m_denominator; //!< 分母
    int64_t m_numerator;   //!< 分子
};

#endif //___INCLUDED_FRACTION___
#ifndef __INCLUDED_GRID2D__
#define __INCLUDED_GRID2D__

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

/**
    @brief    二次元のグリッドを表すクラス

    @tparam    T   格納する型
 */
template <class T>
class Grid2D
{
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

    /**
        @brief            指定した座標の値にアクセスする

        @param[in]    x   X座標
        @param[in]    y   Y座標

        @return         目的の座標の参照
     */
    T &Ref(int64_t x, int64_t y)
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

#endif //__INCLUDED_GRID2D__
#ifndef ___INCLUDED_PREFIX_SUM___
#define ___INCLUDED_PREFIX_SUM___

#include <algorithm>
#include <cassert>
#include <iterator>
#include <vector>

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
    PrefixSum(Iterator beginItr, Iterator endItr) : m_data()
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

        @param[in]    targetIdx   加算を終了する��ンデックス
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

#ifndef ___INCLUDED_SEGMENT_TREE___
#define ___INCLUDED_SEGMENT_TREE___

#include <cstdint>
#include <functional>
#include <limits>
#include <vector>

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
            position = (position - 1) / 2; // 1つ親に移動
            m_data[position] =
                m_mergeFunc(m_data[position * 2 + 1], m_data[position * 2 + 2]); // 2つの子を比較してFuncな方を選ぶ
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
        @param[in]    currentIdx      今見���いるインデックス
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
        @brief        最右位置取��の本体部分

        @param[in]    queryL          クエリで与えられた左端
        @param[in]    queryR          クエリで与えられた右端
        @param[in]    cond            二分探索の条件
        @param[in]    currentIdx      今見ているインデックス
        @param[in]    rangeBegins     今見ている範囲が始まるインデックス
        @param[in]    rangeEnds       今見ている範囲が終わるインデックス

        @return     valueよりFuncな最も右のインデックス
     */
    template <class Condition>
    size_t FindRightImpl(size_t queryL, size_t queryR, Condition cond, size_t currentIdx, size_t rangeBegins,
                         size_t rangeEnds)
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
        @param[in]    rangeEnds       今見てい���範囲が終わるインデックス

        @return     valueよりFuncな最も左のインデックス
     */
    template <class Condition>
    size_t FindLeftImpl(size_t queryL, size_t queryR, Condition cond, size_t currentIdx, size_t rangeBegins,
                        size_t rangeEnds)
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
        size_t idxL =
            FindLeftImpl(queryL, queryR, cond, currentIdx * 2 + 1, rangeBegins, (rangeBegins + rangeEnds) / 2);
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
    static const size_t INVALID; //!< 不正を示す定数
};

template <class T>
const size_t SegmentTree<T>::INVALID = std::numeric_limits<size_t>::max();

#endif //___INCLUDED_SEGMENT_TREE___
#ifndef ___INCLUDED_UNIONFIND___
#define ___INCLUDED_UNIONFIND___

#include <cstddef>
#include <cstdint>
#include <vector>

/**
    @brief        UnionFind
 */
class UnionFind final
{
  public:
    /**
        @brief       コンストラクタ

        @param[in]   size        要素数
     */
    UnionFind(size_t size) : m_data(size, NO_PARENT), m_size(size, 1)
    {
    }

    /**
        @brief    デストラクタ
     */
    ~UnionFind()
    {
    }

    /**
        @brief        親のインデックスを取得する

        @param[in]  index       対象とするインデックス

        @return     親のインデックス
     */
    int64_t Find(int64_t index)
    {
        if (m_data[index] == NO_PARENT)
        {
            return index;
        }
        return m_data[index] = Find(m_data[index]);
    }

    /**
        @brief                右辺と左辺を同じグループとする

        @param[in]  lhs     左辺のインデックス
        @param[in]  rhs     右辺のインデックス
     */
    void Merge(int64_t lhs, int64_t rhs)
    {
        // 先に親まで繋げておく
        lhs = Find(lhs);
        rhs = Find(rhs);

        // 同じグループならば何もしない
        if (lhs == rhs)
        {
            return;
        }

        // 常に左辺がサイズ小さい方とする
        if (m_size[lhs] < m_size[rhs])
        {
            std::swap(lhs, rhs);
        }

        m_size[rhs] += m_size[lhs];
        m_data[lhs] = rhs;
    }

    /**
        @brief            親が共通かどうか

        @param[in]  lhs     左辺のインデックス
        @param[in]  rhs     右辺のインデックス

        @retval     true    両辺の親が共通
        @retval     false   両辺の親が異なる
     */
    bool IsSame(int64_t lhs, int64_t rhs)
    {
        int64_t parentL = Find(lhs);
        int64_t parentR = Find(rhs);

        return parentL == parentR;
    }

  private:
    const int64_t NO_PARENT = -1; //!< 親がいない(=自分が親)であることを示す定数
    std::vector<int64_t> m_data;  //!< 本体となる配列
    std::vector<int64_t> m_size;  //!< 木のサイズ
};

#endif //___INCLUDED_UNIONFIND___

#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

#include <iostream>
#include <sstream>
#include <string>

// #define ENABLE_MULTICASE //!< マルチケース用スイッチ：コメントを外すとマルチケースになる

/**
    @brief	Atcoderの解答を行うのに便利なクラス
 */
class AtcoderSolveHelper
{
  private:
    //----------- 編集エリア -----------------------------
    /**
        @brief	実際に問題を解く関数
        @note   マルチケ���スの場合はケースごとに呼ばれます
     */
    void Solve();

    //----------- 以下編集の必要なし ----------------------

  public:
    /**
        @brief	各種処理の起点になる窓口
     */
    void Run()
    {
        int64_t numTestCases = 1;
#ifdef ENABLE_MULTICASE
        In() >> numTestCases;
#endif
        while (numTestCases--)
        {
            Solve();
        }

        std::cout << Out().str();
    }

  private:
    /**
        @brief	対象とするコンテナの各要素に入力を受け取る

        @tparam	TargetContainerType 対象とするコンテナの型
        @param[in]	targetContainer 対象とするコンテナ
     */
    template <class TargetContainerType>
    void EachInput(TargetContainerType &targetContainer)
    {
        for (auto &&target : targetContainer)
        {
            In() >> target;
        }
    }

    /**
        @brief	入力ストリームを取得

        @return 入力ストリーム
     */
    std::istream &In()
    {
        return std::cin;
    }

    /**
        @brief	出力ストリームを取得

        @return 出力ストリーム
     */
    std::stringstream &Out()
    {
        return m_outStream;
    }

    /**
        @brief	エラー出力ストリームを取得

        @return エラー出力ストリーム
     */
    std::ostream &Error()
    {
        return std::cerr;
    }

    /**
        @brief	Yesと1行出力する
     */
    void Yes()
    {
        Out() << "Yes" << std::endl;
    }

    /**
        @brief	Noと1行出力する
     */
    void No()
    {
        Out() << "No" << std::endl;
    }

    /**
        @brief	渡されたbool値に応じてYesかNoを出力する

        @param[in]	isYes Yesを出力するかどうか
     */
    void YesNo(bool isYes)
    {
        if (isYes)
        {
            Yes();
        }
        else
        {
            No();
        }
    }

  private:
    std::stringstream m_outStream; //!< 出力を一時的に貯めておけるストリーム
};

/**
    @brief	エントリポイント

    @return ステータスコード(atcoderにおいては基本0)
 */
int main()
{
    AtcoderSolveHelper solver;
    solver.Run();
    return 0;
}

//----------------------編集スペースここから--------------------------

void AtcoderSolveHelper::Solve()
{
    int64_t D, F;
    In() >> D >> F;

    int64_t diff = D % 7;
    int64_t ans = F - diff;
    if (ans <= 0)
    {
        ans += 7;
    }
    Out() << ans;
}

//----------------------編集スペースここまで--------------------------

#endif //___INCLUDED_MAIN___