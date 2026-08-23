#ifndef ___INCLUDED_MODINT___
#define ___INCLUDED_MODINT___

#include <cassert>
#include <cstdint>
#include <istream>

const int64_t MOD = 998244353; //!< 一番よく使うやつ

//! @brief 実行時に決まる法に対する余りを管理する整数型
class RuntimeModInt
{
  public:
    //! @brief デフォルトコンストラクタ
    RuntimeModInt() : m_value(0), m_modulo(0)
    {
    }

    //! @brief コンストラクタ
    //! @param value 値
    //! @param modulo 法
    RuntimeModInt(int64_t value, int64_t modulo) : m_value(value), m_modulo(modulo)
    {
        _ApplyModulo();
    }

    //! @brief コピーコンストラクタ
    //! @param rhs コピー元
    RuntimeModInt(const RuntimeModInt &rhs) : m_value(rhs.m_value), m_modulo(rhs.m_modulo)
    {
        _ApplyModulo();
    }

    //! @brief コピー代入演算子
    //! @param rhs コピー元
    //! @return 自身の参照
    RuntimeModInt &operator=(const RuntimeModInt &rhs)
    {
        m_value = rhs.m_value;
        m_modulo = rhs.m_modulo;
        _ApplyModulo();
        return *this;
    }

    //! @brief 整数値に変換
    operator int64_t() const
    {
        return m_value;
    }

    //! @brief 加算代入演算子
    //! @param rhs 右辺
    //! @return 自身の参照
    RuntimeModInt &operator+=(const int64_t rhs)
    {
        m_value += rhs;
        _ApplyModulo();
        return *this;
    }

    //! @brief 減算代入演算子
    //! @param rhs 右辺
    //! @return 自身の参照
    RuntimeModInt &operator-=(const int64_t rhs)
    {
        m_value -= rhs;
        _ApplyModulo();
        return *this;
    }

    //! @brief 乗算代入演算子
    //! @param rhs 右辺
    //! @return 自身の参照
    RuntimeModInt &operator*=(const int64_t rhs)
    {
        m_value *= rhs;
        _ApplyModulo();
        return *this;
    }

    //! @brief 除算代入演算子
    //! @param rhs 右辺
    //! @return 自身の参照
    //! @note ！m_moduloが素数の時にしか成立しない！
    RuntimeModInt &operator/=(const int64_t rhs)
    {
        RuntimeModInt inv = RuntimeModInt(rhs, m_modulo).GetPowered(m_modulo - 2);

        *this *= inv;
        return *this;
    }

    //! @brief 累乗
    //! @param exponent 指数
    //! @return 自身の参照
    RuntimeModInt &Pow(int64_t exponent)
    {
        RuntimeModInt ans(1, m_modulo);

        while (exponent)
        {
            if (exponent % 2)
            {
                ans *= *this;
            }
            *this *= *this;
            exponent >>= 1;
        }

        *this = ans;
        return *this;
    }

    //! @brief 加算演算子
    //! @param rhs 右辺
    //! @return 加算した後の値
    RuntimeModInt operator+(const int64_t rhs) const
    {
        RuntimeModInt retval = *this;
        retval += rhs;
        return retval;
    }

    //! @brief 減算演算子
    //! @param rhs 右辺
    //! @return 減算した後の値
    RuntimeModInt operator-(const int64_t rhs) const
    {
        RuntimeModInt retval = *this;
        retval -= rhs;
        return retval;
    }

    //! @brief 乗算演算子
    //! @param rhs 右辺
    //! @return 乗算した後の値
    RuntimeModInt operator*(const int64_t rhs) const
    {
        RuntimeModInt retval = *this;
        retval *= rhs;
        return retval;
    }

    //! @brief 除算演算子
    //! @param rhs 右辺
    //! @return 除算した後の値
    RuntimeModInt operator/(const int64_t rhs) const
    {
        RuntimeModInt retval = *this;
        retval /= rhs;
        return retval;
    }

    //! @brief 累乗した値を取得する
    //! @param exponent 指数
    //! @return 累乗した後の値
    RuntimeModInt GetPowered(int64_t exponent) const
    {
        RuntimeModInt retval = *this;
        retval.Pow(exponent);
        return retval;
    }

    //! @brief 等価演算子
    //! @param rhs 比較対象
    //! @return 等価ならtrue
    bool operator==(const RuntimeModInt &rhs) const
    {
        return m_value == rhs.m_value;
    }

    //! @brief 不等価演算子
    //! @param rhs 比較対象
    //! @return 不等価ならtrue
    bool operator!=(const RuntimeModInt &rhs) const
    {
        return !operator==(rhs);
    }

  private:
    //! @brief 法を適用する
    void _ApplyModulo()
    {
        // 死なれたら困りそう
        if (m_modulo == 0)
        {
            return;
        }
        m_value %= m_modulo;
        // 負の値の時も想定した結果が出るようにする
        if (m_value < 0)
        {
            m_value += m_modulo;
        }
    }

  protected:
    int64_t m_value;  //!< 値
    int64_t m_modulo; //!< 法
};

// 前方参照
template <int64_t MODULO>
class ModInt;

//! @brief コンパイル時に決まる法に対する余りを管理する整数型
template <int64_t MODULO>
class ModInt : public RuntimeModInt
{
  public:
    //! @brief デフォルトコンストラクタ
    ModInt() : RuntimeModInt(0, MODULO)
    {
    }

    //! @brief コンストラクタ
    //! @param value 値
    ModInt(int64_t value) : RuntimeModInt(value, MODULO)
    {
    }

    //! @brief コピーコンストラクタ
    //! @param rhs コピー元
    ModInt(const ModInt &rhs) : RuntimeModInt(rhs)
    {
    }

    //! @brief コピー代入演算子
    //! @param rhs コピー元
    //! @return 自身の参照
    ModInt &operator=(const ModInt &rhs)
    {
        RuntimeModInt::operator=(rhs);
        return *this;
    }

    //! @brief 加算代入演算子
    //! @param rhs 右辺
    //! @return 自身の参照
    ModInt &operator+=(const int64_t rhs)
    {
        RuntimeModInt::operator+=(rhs);
        return *this;
    }

    //! @brief 減算代入演算子
    //! @param rhs 右辺
    //! @return 自身の参照
    ModInt &operator-=(const int64_t rhs)
    {
        RuntimeModInt::operator-=(rhs);
        return *this;
    }

    //! @brief 乗算代入演算子
    //! @param rhs 右辺
    //! @return 自身の参照
    ModInt &operator*=(const int64_t rhs)
    {
        RuntimeModInt::operator*=(rhs);
        return *this;
    }

    //! @brief 除算代入演算子
    //! @param rhs 右辺
    //! @return 自身の参照
    //! @note ！m_moduloが素数の時にしか成立しない！
    ModInt &operator/=(const int64_t rhs)
    {
        RuntimeModInt::operator/=(rhs);
        return *this;
    }

    //! @brief 累乗
    //! @param exponent 指数
    //! @return 自身の参照
    ModInt &Pow(int64_t exponent)
    {
        RuntimeModInt::Pow(exponent);
        return *this;
    }

    //! @brief 加算演算子
    //! @param rhs 右辺
    //! @return 加算した後の値
    ModInt operator+(const int64_t rhs) const
    {
        ModInt retval = *this;
        retval += rhs;
        return retval;
    }

    //! @brief 減算演算子
    //! @param rhs 右辺
    //! @return 減算した後の値
    ModInt operator-(const int64_t rhs) const
    {
        ModInt retval = *this;
        retval -= rhs;
        return retval;
    }

    //! @brief 乗算演算子
    //! @param rhs 右辺
    //! @return 乗算した後の値
    ModInt operator*(const int64_t rhs) const
    {
        ModInt retval = *this;
        retval *= rhs;
        return retval;
    }

    //! @brief 除算演算子
    //! @param rhs 右辺
    //! @return 除算した後の値
    ModInt operator/(const int64_t rhs) const
    {
        ModInt retval = *this;
        retval /= rhs;
        return retval;
    }

    //! @brief 累乗した値を取得する
    //! @param exponent 指数
    //! @return 累乗した後の値
    ModInt GetPowered(int64_t exponent) const
    {
        ModInt retval = *this;
        retval.Pow(exponent);
        return retval;
    }

  private:
    template <int64_t M>
    friend std::istream &operator>>(std::istream &stream, ModInt<M> &dest);
};

//! @brief 入力ストリーム演算子
//! @param stream ストリーム
//! @param dest 入力対象
//! @return ストリーム
template <int64_t MODULO>
std::istream &operator>>(std::istream &stream, ModInt<MODULO> &dest)
{
    stream >> dest.m_value;
    return stream;
}

using ModInt998 = ModInt<MOD>; //!< よく使うので短縮名にしておく

#endif //___INCLUDED_MODINT___