#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

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
        @note   マルチケースの場合はケースごとに呼ばれます
     */
    void Solve()
    {
        int64_t H, W, N;
        In() >> H >> W >> N;
        struct ELEM
        {
            int64_t x, y;
        };
        std::vector<ELEM> input;
        std::vector<int64_t> x;
        std::vector<int64_t> y;
        x.push_back(0);
        y.push_back(0);
        for (int i = 0; i < N; ++i)
        {
            ELEM tmp;
            In() >> tmp.x >> tmp.y;
            input.push_back(tmp);
            y.push_back(tmp.y);
            x.push_back(tmp.x);
        }
        std::sort(x.begin(), x.end());
        std::sort(y.begin(), y.end());
        {
            auto itr = std::unique(x.begin(), x.end());
            x.erase(itr, x.end());
        }
        {
            auto itr = std::unique(y.begin(), y.end());
            y.erase(itr, y.end());
        }
        for (int i = 0; i < N; ++i)
        {
            auto itrX = std::lower_bound(x.begin(), x.end(), input[i].x);
            auto itrY = std::lower_bound(y.begin(), y.end(), input[i].y);
            Out() << itrX - x.begin() << " " << itrY - y.begin() << std::endl;
        }
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