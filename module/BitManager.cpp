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
        @brief	コンストラクタ

        @param[in]	val 初期値
     */
    BitManager(uint64_t val)
        : m_data(val) {};

    /**
        @brief	全てfalseで初期化されたビットマネージャを取得

        @return 全てfalseで初期化されたビットマネージャ
     */
    static BitManager AllFalse()
    {
        return BitManager(0ull);
    }

    /**
        @brief	全てtrueで初期化されたビットマネージャを取得

        @return 全てtrueで初期化されたビットマネージャ
     */
    static BitManager AllTrue()
    {
        return BitManager(0xffffffffffffffffull);
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

private:
    /**
        @brief	インデックスが正しいか検証する

        @param[in]	idx インデックス
     */
    void _ValidateIndex(int idx)
    {
        if (idx >= NUM_DIGIT)
        {
            std::cerr << "BitManager: Index Error!" << std::endl;
        }
    }

public:
    static constexpr int NUM_DIGIT = 64; //!< 桁数

private:
    uint64_t m_data; //!< 本体
};

#endif //___INCLUDED_BITMAN___