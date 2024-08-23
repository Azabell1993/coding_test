#include <string>
#include <vector>
#include <map>

using namespace std;

// 괄호 문자열의 첫 번째와 마지막 문자를 검사하여 올바른 괄호 문자열의 가능성을 확인하는 함수
bool check(const vector<char>& s) {
    // 첫 번째 문자가 닫는 괄호이면 올바른 문자열이 될 수 없으므로 false 반환
    if (s[0] == ')' || s[0] == ']' || s[0] == '}') {
        return false;
    }
    // 마지막 문자가 여는 괄호이면 올바른 문자열이 될 수 없으므로 false 반환
    if (s[s.size() - 1] == '(' || s[s.size() - 1] == '[' || s[s.size() - 1] == '{') {
        return false;
    }
    // 위 조건을 모두 통과하면 true 반환
    return true;
}

// 주어진 문자열이 올바른 괄호 문자열인지 확인하는 함수
bool is_valid(const vector<char>& s) {
    // 여는 괄호와 닫는 괄호의 짝을 저장한 map 자료구조를 생성
    map<char, char> dict = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
    // 원본 문자열을 수정하지 않기 위해 temp_s라는 임시 벡터로 복사
    vector<char> temp_s = s;
    
    // 먼저, 문자열의 첫 번째와 마지막 문자가 올바른지 확인
    if (!check(temp_s)) {
        return false;
    }

    // temp_s 문자열을 처음부터 끝까지 순회하면서 검증
    for (size_t i = 0; i < temp_s.size(); ++i) {
        // 현재 문자가 여는 괄호가 아닌 경우 (닫는 괄호 또는 문자)
        if (dict.find(temp_s[i]) == dict.end()) {
            // 바로 앞의 문자가 여는 괄호이고 현재 문자가 그에 해당하는 닫는 괄호가 아니면 false 반환
            if (i > 0 && dict.find(temp_s[i - 1]) != dict.end() && temp_s[i] != dict[temp_s[i - 1]]) {
                return false;
            }
        }
    }
    
    // 문자열이 남아있는 동안 반복하여 짝을 지어 제거
    while (!temp_s.empty()) {
        // 현재 문자열의 첫 번째와 마지막 문자가 올바른지 확인
        if (!check(temp_s)) {
            return false;
        }
        
        // 첫 번째 여는 괄호와 매칭되는 닫는 괄호를 temp에 저장
        char temp = dict[temp_s[0]];
        // 첫 번째 여는 괄호를 제거
        temp_s.erase(temp_s.begin());
        
        // 남아있는 문자열에서 해당 닫는 괄호를 찾아 제거
        for (size_t i = 0; i < temp_s.size(); ++i) {
            if (temp == temp_s[i]) {
                temp_s.erase(temp_s.begin() + i);
                break;
            }
        }
    }
    
    // 모든 검사를 통과하면 true 반환 (올바른 괄호 문자열임)
    return true;
}

// 주어진 문자열을 회전시켜 가능한 올바른 괄호 문자열의 개수를 세는 함수
int solution(const string s) {
    int answer = 0;
    
    // 문자열 길이가 홀수이면 짝이 맞을 수 없으므로 0 반환
    if (s.length() % 2 != 0) {
        return answer;
    }

    // 문자열을 벡터로 변환
    vector<char> s_vec(s.begin(), s.end());

    // 문자열을 한 칸씩 회전시키면서 올바른 괄호 문자열인지 검사
    for (size_t i = 0; i < s_vec.size(); ++i) {
        // 회전된 문자열을 만들기 위해 s_vec을 두 부분으로 나눠 결합
        vector<char> rotated(s_vec.begin() + i, s_vec.end());
        rotated.insert(rotated.end(), s_vec.begin(), s_vec.begin() + i);
        
        // 회전된 문자열이 올바른 괄호 문자열이면 answer 증가
        if (is_valid(rotated)) {
            ++answer;
        }
    }
    
    // 최종적으로 올바른 괄호 문자열의 개수 반환
    return answer;
}
