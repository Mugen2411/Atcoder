#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

void AtcoderSolveHelper::Solve()
{
    int N;
    In() >> N;
    std::vector<int64_t> A(N);
    EachInput(A);

    std::priority_queue<int64_t> pri;
    pri.push(A[0]);
    pri.push(A[1]);

    for (int i = 2; i < N; ++i)
    {
        pri.push(A[i]);

        int64_t cur0 = pri.top();
        pri.pop();
        int64_t cur1 = pri.top();
        pri.pop();
        Out() << pri.top() << std::endl;
        pri.push(cur1);
        pri.push(cur0);
    }
    return;
}

#endif //___INCLUDED_MAIN___