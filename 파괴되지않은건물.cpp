#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    int answer = 0;
    int n = board.size();
    int m = board[0].size();

    // impact 배열 초기화(영향을 미칠 범위를 저장)
    vector<vector<int>> impact(n + 1, vector<int>(m + 1, 0));

    // 스킬 적용
    for (auto& s : skill) {
        int type = s[0];
        int r1 = s[1], c1 = s[2], r2 = s[3], c2 = s[4], degree = s[5];
        int effect = (type == 1) ? -degree : degree;

    /**
     * 1. (r1, c1)에서 (r2, c2)까지의 영향을 미친다는 것은
     *   (r1, c1)에서 (r2, c2)까지의 영향을 미치는 사각형의 네 꼭지점을 찾아야 한다.
     * 2. (r1, c1)에서 (r2, c2)까지의 영향을 미치는 사각형의 네 꼭지점은
     *  (r1, c1), (r1, c2 + 1), (r2 + 1, c1), (r2 + 1, c2 + 1)이다.
    */
        impact[r1][c1] += effect;   // 시작 행과 열 인덱스에 effect 값을 더함
        impact[r1][c2 + 1] -= effect; // 시작 행과 열 인덱스에서 c2 + 1 위치에 effect 값을 뺌
        impact[r2 + 1][c1] -= effect; // 끝 행 다음 위치와 시작 열 인덱스에 effect 값을 뺌
        impact[r2 + 1][c2 + 1] += effect; // 끝 행 다음 위치와 끝 열 다음 위치에 effect 값을 더함
    }

    // 누적합 계산
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            impact[i][j] += impact[i][j - 1];   // 열에 대한 누적합 계산
        }
    }
    for (int j = 0; j < m; ++j) {
        for (int i = 1; i < n; ++i) {
            impact[i][j] += impact[i - 1][j]; // 행에 대한 누적합 계산
        }
    }

    // 최종 board 계산 및 파괴되지 않은 건물 개수 세기
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            board[i][j] += impact[i][j];
            if (board[i][j] > 0) {
                answer++;
            }
        }
    }

    return answer;
}
