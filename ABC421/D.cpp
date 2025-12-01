#include <iostream>
#include <string>
#include <sstream>
#include <list>

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
        struct COMMAND
        {
            int Direction;
            int64_t Duration;
        };

        // RLUD
        std::pair<int64_t, int64_t> dir[4] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};

        int64_t curTC;
        int64_t curTR;
        int64_t curAC;
        int64_t curAR;

        In() >> curTR >> curTC >> curAR >> curAC;
        int64_t N, M, L;
        In() >> N >> M >> L;

        std::list<COMMAND> cmdT;
        std::list<COMMAND> cmdA;

        auto convertDir = [](char dir)
        {
            switch (dir)
            {
            case 'R':
                return 0;
            case 'L':
                return 1;
            case 'U':
                return 2;
            case 'D':
                return 3;
            default:
                return -1;
            }
        };

        for (int i = 0; i < M; ++i)
        {
            COMMAND tmp = {};
            char dir;
            In() >> dir >> tmp.Duration;
            tmp.Direction = convertDir(dir);
            cmdT.push_back(tmp);
        }
        for (int i = 0; i < L; ++i)
        {
            COMMAND tmp = {};
            char dir;
            In() >> dir >> tmp.Duration;
            tmp.Direction = convertDir(dir);
            cmdA.push_back(tmp);
        }

        int64_t curTime = 0;
        int64_t ans = 0;

        int64_t curR = curAR - curTR;
        int64_t curC = curAC - curTC;
        int64_t baseR = curR;
        int64_t baseC = curC;

        while (curTime < N)
        {
            COMMAND &topT = cmdT.front();
            COMMAND &topA = cmdA.front();

            int64_t minDuration = std::min(topT.Duration, topA.Duration);

            COMMAND curT = COMMAND{topT.Direction, minDuration};
            COMMAND curA = COMMAND{topA.Direction, minDuration};

            topT.Duration -= minDuration;
            if (topT.Duration == 0)
            {
                cmdT.pop_front();
            }
            topA.Duration -= minDuration;
            if (topA.Duration == 0)
            {
                cmdA.pop_front();
            }

            int64_t curDir[2] = {dir[curA.Direction].first - dir[curT.Direction].first,
                                 dir[curA.Direction].second - dir[curT.Direction].second};

            int64_t nextR = curR + curDir[1] * minDuration;
            int64_t nextC = curC + curDir[0] * minDuration;

            if (curDir[0] == 0 && curDir[1] == 0)
            {
                if (curR == 0 && curC == 0)
                {
                    ans += minDuration;
                }
            }
            else if ((std::abs(curR) + std::abs(curC)) % 2 == 0)
            {
                int64_t halfMnDist = (std::abs(curR) + std::abs(curC)) / 2;
                if (0 < halfMnDist && halfMnDist <= minDuration)
                {
                    if (curR + curDir[1] * halfMnDist == 0 && curC + curDir[0] * halfMnDist == 0)
                    {
                        ++ans;
                    }
                }
            }

            curR = nextR;
            curC = nextC;

            curTime += minDuration;
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