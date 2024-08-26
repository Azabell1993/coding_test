#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

int robber(const vector<int>& money, int start, int end) {
    // 코드를 더 짧고 간결하게 하기 위해 unique_ptr<int> 로직 채택 또 tie 채택
    // include와 exclude라는 두 개의 unique_ptr<int> 변수 초기화

    // include : 현재 집 털때 금액
    // exclude : 현재 집을 털지 않을때 금액
    auto include = make_unique<int>(0);
    auto exclude = make_unique<int>(0);

    // start부터 end까지의 인덱스를 순회하며 최대 금액 계산
    for (int i = start; i <= end; ++i) {
        // 현재 집을 털거나 안 털 때의 최댓값을 동시에 계산
        // tie는 여러 변수를 튜플의 형태로 묶어서, 그 값들을 동시에 업데이트할 수 있다.
        // tie(a, b) = make_tuple(x, y);는 a = x;와 b = y;를 동시에 수행하는 것과 동일
        tie(*include, *exclude) = make_tuple(*exclude + money[i], max(*include, *exclude));
    }

    // 최종적으로 얻을 수 있는 최대 금액 반환
    return max(*include, *exclude);
}

int solution(vector<int> money) {
    int n = money.size();
    if (n == 1) return money[0];  // 집이 하나일 경우, 그 집의 돈만 반환

    // 첫 번째 집을 포함하고 마지막 집을 포함하지 않는 경우의 최대 금액 계산
    int case1 = robber(money, 0, n - 2);

    // 첫 번째 집을 포함하지 않고 마지막 집을 포함하는 경우의 최대 금액 계산
    int case2 = robber(money, 1, n - 1);

    return max(case1, case2);
}
