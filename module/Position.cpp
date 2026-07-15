#ifndef ___INCLUDED_POSITION___
#define ___INCLUDED_POSITION___

#include <array>
#include <cstdint>

//! @brief 座標型
struct POSITION
{
    //! @brief 右移動の差分を取得
    //! @return 右移動の差分
    static POSITION R()
    {
        return POSITION(1, 0);
    }

    //! @brief 左移動の差分を取得
    //! @return 左移動の差分
    static POSITION L()
    {
        return POSITION(-1, 0);
    }

    //! @brief 下移動の差分を取得
    //! @return 下移動の差分
    static POSITION D()
    {
        return POSITION(0, 1);
    }

    //! @brief 上移動の差分を取得
    //! @return 上移動の差分
    static POSITION U()
    {
        return POSITION(0, -1);
    }

    //! @brief 前移動の差分を取得
    //! @return 前移動の差分
    static POSITION F()
    {
        return POSITION(0, 0, 1);
    }

    //! @brief 後移動の差分を取得
    //! @return 後移動の差分
    static POSITION B()
    {
        return POSITION(0, 0, -1);
    }

    //! @brief RLDUから座標差分を取得する
    //! @param dir R,L,D,Uの文字
    //! @return 対応する方向
    static POSITION RLDU(char dir)
    {
        switch (dir)
        {
        case 'R':
            return R();
        case 'L':
            return L();
        case 'D':
            return D();
        case 'U':
            return U();
        default:
            return POSITION();
        }
    }

    //! @brief RLDU文字配列を取得
    //! @return RLDUが入った配列
    static const std::array<char, 4> GetDirectionChars()
    {
        return {'R', 'L', 'D', 'U'};
    }

    //! @brief テンキーから座標差分を取得する
    //! @param dir 1~9の文字(数値ではなく文字コード)
    //! @return 対応する方向
    static POSITION Tenkey(char dir)
    {
        switch (dir)
        {
        case '1':
            return L() + D();
        case '2':
            return D();
        case '3':
            return R() + D();
        case '4':
            return L();
        case '6':
            return R();
        case '7':
            return L() + U();
        case '8':
            return U();
        case '9':
            return R() + U();
        default:
            return POSITION();
        }
    }

    //! @brief テンキーで使う文字一覧を取得
    //! @return 文字一覧
    static const std::array<char, 8> GetTenkeyChars()
    {
        return {'1', '2', '3', '4', '6', '7', '8', '9'};
    }

  public:
    //! @brief デフォルトコンストラクタ
    POSITION() : X(0), Y(0), Z(0)
    {
    }

    //! @brief コンストラクタ
    //! @param x
    //! @param y
    //! @param z
    POSITION(int64_t x, int64_t y, int64_t z = 0) : X(x), Y(y), Z(z)
    {
    }

    //! @brief コピーコンストラクタ
    //! @param rhs コピー元
    POSITION(const POSITION &rhs) : X(rhs.X), Y(rhs.Y), Z(rhs.Z)
    {
    }

    //! @brief コピー代入演算子
    //! @param rhs コピー元
    //! @return 自身の参照
    POSITION &operator=(const POSITION &rhs)
    {
        X = rhs.X;
        Y = rhs.Y;
        Z = rhs.Z;

        return *this;
    }

    //! @brief 加算代入演算子
    //! @param rhs 右辺
    //! @return 自身の参照
    POSITION &operator+=(const POSITION &rhs)
    {
        X += rhs.X;
        Y += rhs.Y;
        Z += rhs.Z;

        return *this;
    }

    //! @brief 減算代入演算子
    //! @param rhs 右辺
    //! @return 自身の参照
    POSITION &operator-=(const POSITION &rhs)
    {
        X -= rhs.X;
        Y -= rhs.Y;
        Z -= rhs.Z;

        return *this;
    }

    //! @brief 乗算代入演算子
    //! @param rhs 右辺
    //! @return 自身の参照
    POSITION &operator*=(const POSITION &rhs)
    {
        X *= rhs.X;
        Y *= rhs.Y;
        Z *= rhs.Z;

        return *this;
    }

    //! @brief 加算演算子
    //! @param rhs 右辺
    //! @return 加算した結果
    POSITION operator+(const POSITION &rhs) const
    {
        POSITION retval = *this;
        retval += rhs;

        return retval;
    }

    //! @brief 減算演算子
    //! @param rhs 右辺
    //! @return 減算した結果
    POSITION operator-(const POSITION &rhs) const
    {
        POSITION retval = *this;
        retval -= rhs;

        return retval;
    }

    //! @brief 乗算演算子
    //! @param rhs 右辺
    //! @return 乗算した結果
    POSITION operator*(const POSITION &rhs) const
    {
        POSITION retval = *this;
        retval *= rhs;

        return retval;
    }

  public:
    int64_t X; //!< X座標
    int64_t Y; //!< Y座標
    int64_t Z; //!< Z座標
};

#endif //___INCLUDED_POSITION___