#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define ENABLE_MULTICASE //!< マルチケース用スイッチ：コメントを外すとマルチケースになる

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
        int N;
        std::string S;
        In() >> N >> S;

        struct ELEM
        {
            char c;
            int64_t len;
        };
        std::vector<ELEM> comp;
        for (auto c : S)
        {
            if (comp.empty() || comp.back().c != c)
            {
                comp.push_back({c, 1});
            }
            else
            {
                ++comp.back().len;
            }
        }
        int64_t ans = N * 2;
        for (char i = '0'; i <= '1'; ++i)
        {
            int64_t instaAns = 0;
            auto base = comp.end();
            int64_t longest = 0;
            for (auto itr = comp.begin(); itr != comp.end(); ++itr)
            {
                if (longest < itr->len && itr->c == i)
                {
                    base = itr;
                    longest = itr->len;
                }
            }
            for (auto itr = comp.begin(); itr != comp.end(); ++itr)
            {
                if (itr == base)
                {
                    continue;
                }
                instaAns += itr->len * ((itr->c == i) ? 2 : 1);
            }
            ans = std::min(instaAns, ans);
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