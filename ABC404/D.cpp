#include <iostream>
#include <string>
#include <sstream>

// #define ENABLE_MULTICASE //!< マルチケース用スイッチ：コメントを外すとマルチケースになる

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

#include <vector>
#include <unordered_set>

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
        int64_t N, M;
        In() >> N >> M;
        std::vector<int64_t> C(N);
        EachInput(C);

        std::vector<std::unordered_set<int64_t>> zoo(N);

        for (int i = 0; i < M; ++i)
        {
            int64_t K;
            In() >> K;

            for (int j = 0; j < K; ++j)
            {
                int64_t A;
                In() >> A;
                zoo[A - 1].insert(i);
            }
        }

        int64_t ans = 999999999999;

        auto dfs = [&](auto self, int idx, int64_t curCost, std::vector<int64_t> curResult) -> void
        {
            if (idx == N)
            {
                return;
            }

            for (int i = 0; i < 3; ++i)
            {
                std::vector<int64_t> newResult = curResult;
                int64_t newCost = curCost;

                for (auto &z : zoo[idx])
                {
                    newResult[z] += i;
                }

                newCost += C[idx] * i;

                bool isAnswer = true;
                for (int j = 0; j < M; ++j)
                {
                    if (newResult[j] < 2)
                    {
                        isAnswer = false;
                        break;
                    }
                }

                if (isAnswer)
                {
                    ans = std::min(ans, newCost);
                }

                self(self, idx + 1, newCost, newResult);
            }
        };

        dfs(dfs, 0, 0, std::vector<int64_t>(M));

        Out() << ans;
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