#include <iostream>
#include <string>
#include <sstream>

#ifndef __INCLUDED_GRID2D__
#define __INCLUDED_GRID2D__

#include <vector>
#include <cassert>
#include <cstdint>
#include <iostream>

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

        @return 高さ
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
    BitManager()
        : m_data(0ull) {};

    /**
        @brief	コンストラクタ

        @param[in]	val 初期値
     */
    BitManager(uint64_t val)
        : m_data(val) {};

    /**
        @brief	uint64_t型への変換を許可する

        @return uint64_t型に変換されたデータ
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

        @return 全てtrueで初期化されたビットマネージャ
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
        @brief	1つの要素だけtrue、他がfalseのビットマネージャ

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
    BitManager(const BitManager &rhs)
        : m_data(rhs.m_data)
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

        @return インクリメント前のコピー
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
        @return 自身と右辺が等しくないか
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
}

#endif //___INCLUDED_BITMAN___

#define ENABLE_MULTICASE //!< マルチケース用スイッチ：コメントを外すとマルチケースになる

#include <array>

/**
    @brief	Atcoderの解答を行うのに便利なクラス
 */
class AtcoderSolveHelper
{
private:
    //----------- 編集エリア -----------------------------
    /**
        @brief	実際に問題を解く関数
        @note   マルチケースの場合はケースごとに呼ばれます
     */
    void Solve()
    {
        int H, W;
        In() >> H >> W;
        Grid2D<char> S(H, W, '\0');
        In() >> S;

        Grid2D<char> C(H - 1, W - 1, '\0');
        for (int y = 0; y < C.GetHeight(); ++y)
        {
            for (int x = 0; x < C.GetWidth(); ++x)
            {
                if (S.Ref(x, y) == '#' && S.Ref(x + 1, y) == '#' && S.Ref(x, y + 1) == '#' && S.Ref(x + 1, y + 1) == '#')
                {
                    C.Ref(x, y) = '#';
                }
                else
                {
                    C.Ref(x, y) = '.';
                }
            }
        }

        auto _GetX = [H](int idx)
        {
            return idx % (H - 2);
        };
        auto _GetY = [H](int idx)
        {
            return idx / (H - 2);
        };

        BitManager end = BitManager::Onehot((H - 2) * (W - 2));

        int ans = H * W;

        int dir[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};

        for (BitManager cur = BitManager::AllFalse(); cur != end; ++cur)
        {
            Grid2D<char> tmp = C;
            for (int i = 0; i < tmp.GetHeight() * tmp.GetWidth(); ++i)
            {
                if (cur.Get(i))
                {
                    for (auto d : dir)
                    {
                        int nx = _GetX(i) + d[0];
                        int ny = _GetY(i) + d[1];
                        if (tmp.IsInner(nx, ny))
                        {
                            tmp.Ref(nx, ny) = '.';
                        }
                    }
                }
            }
            bool isAns = true;
            for (int y = 0; y < tmp.GetHeight(); ++y)
            {
                for (int x = 0; x < tmp.GetWidth(); ++x)
                {
                    if (tmp.Ref(x, y) == '#')
                    {
                        isAns = false;
                    }
                }
            }
            if (isAns)
            {
                ans = std::min(ans, cur.GetCount());
            }
        }

        Out() << ans << std::endl;
    }

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