#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> cookie) {
    int answer = 0;
    int n = cookie.size();

    // 각 m에 대해 l에서 m까지, m+1에서 r까지의 합을 비교
    for (int m = 0; m < n - 1; ++m) {
        int leftSum = cookie[m];
        int rightSum = cookie[m + 1];

        int l = m;
        int r = m + 1;

        while (true) {
            if (leftSum == rightSum) {
                answer = max(answer, leftSum);
            }
            if (l > 0 && leftSum <= rightSum) {
                l--;
                leftSum += cookie[l];
            } else if (r < n - 1 && leftSum >= rightSum) {
                r++;
                rightSum += cookie[r];
            } else {
                break;
            }
        }
    }

    return answer;
}
