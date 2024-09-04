#include <vector>
#include <functional>

using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
int answer = 0;

int solution(int n, vector<vector<int>> lighthouse) {
    // adj : 인접 행렬 변수
    adj = vector<vector<int>>(n+1); 
    // visited : 방문 여부 변수
    visited = vector<bool>(n+1, false);

    // 인접 행렬 생성 
    // for(const auto& row : lighthouse) {
    //     // 양방향 그래프이므로 양쪽 노드에 서로를 추가
    //     adj[row[0]].push_back(row[1]); 
    //     adj[row[1]].push_back(row[0]);
    // }
    for(const auto& row : lighthouse) adj[row[0]].push_back(row[1]), adj[row[1]].push_back(row[0]);

    // 깊이 우선 탐색 
    function<bool(int)> dfs = [&](int node) {
        // 방문한 노드로 표시
        visited[node] = true;
        // 불을 켜야하는지 여부
        bool turn_on = false;

        // 인접 노드들을 탐색
        for(auto node : adj[node]) {
            // 방문하지 않은 노드라면
            if(!visited[node]) {
                // 방문하지 않은 노드가 더 이상 방문할 노드가 없다면
                if(!dfs(node))
                    // 불을 켜야한다.
                    turn_on = true;
            }
        }

        // 불을 켜야한다면 
        if(turn_on)
            answer++;

        return turn_on;
    };

    // 1번 노드부터 시작 
    dfs(1);

    return answer;
}
