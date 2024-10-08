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

        impact[r1][c1] += effect; 
        impact[r1][c2 + 1] -= effect;
        impact[r2 + 1][c1] -= effect;
        impact[r2 + 1][c2 + 1] += effect;
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
