#include <iostream>
#include <vector>
#include <algorithm>
#include <memory> // for unique_ptr

using namespace std;

// 현재 배열에서 최소 거리를 계산하고, 제거된 바위의 수를 반환
int min_distance(const vector<int>& rocks, int distance, int mid) {
    int prev = 0; // 이전 바위의 위치
    int min_dist = distance; // 거리의 최솟값 초기화
    int removeCount = 0; // 제거한 바위의 수

    for (int i = 0; i < rocks.size(); i++) {
        if (rocks[i] - prev < mid) {
            // 바위 간 거리가 mid보다 작으면 바위를 제거
            removeCount++;
        } else {
            // 바위를 제거하지 않고 이전 바위 위치를 업데이트
            min_dist = min(min_dist, rocks[i] - prev);
            prev = rocks[i];
        }
    }

    return removeCount;
}

int solution(int distance, vector<int> rocks, int n) {
    // 바위들의 위치를 정렬합니다.
    sort(rocks.begin(), rocks.end());

    // 도착지점 추가
    rocks.push_back(distance);
    
    // 이분 탐색을 위한 변수 설정
    int left = 1;
    int right = distance;
    int answer = 0;
    
    while (left <= right) {
        int mid = (left + right) / 2; // 현재 최소 거리의 후보

        int removeCount = min_distance(rocks, distance, mid);

        if (removeCount > n) {
            // 제거한 바위의 수가 n보다 많으면 최소 거리를 줄인다.
            right = mid - 1;
        } else {
            // 제거한 바위의 수가 n 이하라면 최소 거리를 늘려도 된다.
            answer = mid;
            left = mid + 1;
        }
    }

    return answer;
}
