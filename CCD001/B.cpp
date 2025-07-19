#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

// #define ENABLE_MULTICASE //!< マルチケース用スイッチ：コメントを外すとマルチケースになる

#ifndef ___INCLUDED_PREFIX_SUM___
#define ___INCLUDED_PREFIX_SUM___

#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>

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
    PrefixSum(Iterator beginItr, Iterator endItr)
        : m_data()
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

        @param[in]    targetIdx   加算を終了するインデックス
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
        int64_t N;
        In() >> N;
        std::vector<int64_t> A(N);
        EachInput(A);

        PrefixSum<decltype(A.begin())> pres(A.begin(), A.end());
        std::vector<int64_t> mx(N + 1, 0);
        for (int i = 1; i <= N; ++i)
        {
            mx[i] = pres.GetSum(i, 0);
        }
        for (int i = 1; i <= N; ++i)
        {
            mx[i] = std::max(mx[i], mx[i - 1]);
        }

        int64_t ans = 0;
        int64_t idx = 0;
        int64_t cur = 0;
        for (int i = 1; i <= N; ++i)
        {
            ans = std::max(ans, cur + mx[i]);
            cur += pres.GetSum(i, 0);
        }
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