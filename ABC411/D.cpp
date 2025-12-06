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
        int64_t N, Q;
        In() >> N >> Q;

        struct COMMAND
        {
            int type;
            int dst;
            std::string val;
        };

        std::vector<COMMAND> cmd;
        for (int i = 0; i < Q; ++i)
        {
            COMMAND tmp;
            In() >> tmp.type;
            if (tmp.type == 2)
            {
                In() >> tmp.dst >> tmp.val;
            }
            else
            {
                In() >> tmp.dst;
            }
            std::reverse(tmp.val.begin(), tmp.val.end());
            cmd.push_back(tmp);
        }

        std::reverse(cmd.begin(), cmd.end());

        std::string server;
        int64_t serverIdx = -1;

        for (auto &c : cmd)
        {
            switch (c.type)
            {
            case 1:
            {
                if (c.dst == serverIdx)
                {
                    serverIdx = -1;
                }
            }
            break;
            case 2:
            {
                if (serverIdx == c.dst)
                {
                    server += c.val;
                }
            }
            break;
            case 3:
            {
                if (serverIdx == -1)
                {
                    serverIdx = c.dst;
                }
            }
            break;
            }
        }

        std::reverse(server.begin(), server.end());
        Out() << server << std::endl;
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