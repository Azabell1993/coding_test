#include <vector>
#include <algorithm>

using namespace std;

long long solution(int n, int m, int x, int y, vector<vector<int>> queries) {
    long long answer = 0;
    
    long long x1 = x, y1 = y, x2 = x, y2 = y;
    
    for (int i = queries.size() - 1; i >= 0; --i) {
        int command = queries[i][0];
        int distance = queries[i][1];
        
        switch (command) {
            case 0:  // 왼쪽으로 이동
                if(y1 != 0) y1 += distance;
                y2 = min((long long)m - 1, y2 + distance);
                break;
                
            case 1:  // 오른쪽으로 이동
                if(y2 != m-1) y2 -= distance;
                y1 = max(0LL, y1 - distance);
                break;
                
            case 2:  // 위쪽으로 이동
                if(x1 != 0) x1 += distance;
                x2 = min((long long)n - 1, x2 + distance);
                break;
                
            case 3:  // 아래쪽으로 이동
                if(x2 != n-1) x2 -= distance;
                x1 = max(0LL, x1 - distance);
                break;
        }
        
        if (x1 > x2 || y1 > y2) {
            return 0;
        }
    }
    
    answer = (x2 - x1 + 1) * (y2 - y1 + 1);
    return answer;
}
