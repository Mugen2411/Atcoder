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
        @brief	コンストラクタ

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

        // ダメなら無効にする
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