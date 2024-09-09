#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(int n, vector<vector<int>> roads, vector<int> sources, int destination) {
    vector<int> answer;
    vector<vector<int>> graph(n + 1);  // 각 지역의 인접 지역들을 저장할 그래프
    vector<int> dist(n + 1, -1);        // 각 지역에서 목적지까지의 최단 거리를 저장할 벡터
    bool visited[n + 1];                // 방문한 지역인지 확인하는 배열
    fill(visited, visited + n + 1, false); // 방문한 지역인지 확인하는 배열 초기화

    vector<int> current_nodes;  // 현재 탐색할 노드들
    current_nodes.push_back(destination); // 목적지부터 시작
    dist[destination] = 0; // 목적지까지의 거리는 0

    // roads 정보를 바탕으로 인접 리스트 그래프 구성
    for (auto& road : roads) { // road = {a, b}
        graph[road[0]].push_back(road[1]); // a 지역과 b 지역은 연결되어 있음
        graph[road[1]].push_back(road[0]); // b 지역과 a 지역은 연결되어 있음
    }
    
    while (!current_nodes.empty()) { // 다음 탐색할 노드가 없을 때까지 반복
        vector<int> next_nodes;  // 다음 탐색할 노드들
        for (int current : current_nodes) { // 현재 탐색할 노드들에 대해
            visited[current] = true; // 방문한 지역으로 표시
            for (int next : graph[current]) { // 현재 지역과 연결된 지역에 대해
                if (dist[next] == -1) {  // 아직 방문하지 않은 지역이라면
                    dist[next] = dist[current] + 1;  // 현재 지역까지의 거리 + 1
                    next_nodes.push_back(next);  // 다음에 탐색할 노드로 추가
                    visited[next] = false; // 방문한 지역 초기화
                } 
                // 이미 방문한 지역이지만 더 짧은 거리로 방문할 수 있다면
                else if (dist[next] > dist[current] + 1) {  // 현재 지역까지의 거리 + 1이 더 짧다면
                    dist[next] = dist[current] + 1; // 현재 지역까지의 거리 + 1로 업데이트
                    next_nodes.push_back(next);  // 다음에 탐색할 노드로 추가
                    visited[next] = false; // 방문한 지역 초기화
                }
            }

            if(!visited[current]) { // 방문한 지역이 아니라면
                visited[current] = true; // 방문한 지역으로 표시
            } else { // 방문한 지역이라면
                visited[current] = false; // 방문한 지역 초기화
                continue; // 다음 지역으로 넘어감
            }
        }

        if(next_nodes.empty()) { // 다음 탐색할 노드가 없다면 종료
            break; // 종료
        } else { // 다음 탐색할 노드가 있다면
            current_nodes = next_nodes;  // 다음 탐색할 노드들로 업데이트
        }
    }
    
    // 각 부대원이 위치한 sources에서 목적지까지의 거리 구하기
    for (int source : sources) { // 각 부대원이 위치한 지역에 대해
        answer.push_back(dist[source]); // 목적지까지의 거리를 구하고 정답에 추가
        visited[source] = false; // 방문한 지역 초기화
    }

    if (answer.empty()) { // 정답이 없다면
        answer.push_back(-1);  // -1 추가
        visited[destination] = false; // 방문한 지역 초기화
    }
    return answer;
}
