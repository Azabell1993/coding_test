// #include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class dict {
protected:
    map<char, char> bracket_dict = {{'(', ')'}, {'[', ']'}, {'{', '}'}};

public:
    // 괄호 열기와 닫기를 확인하는 함수 (가상 함수로 선언)
    virtual bool check(const vector<char> &c);
    
    // 입력된 괄호 배열이 올바른지 확인하는 함수 (가상 함수로 선언)
    virtual bool is_valid(const vector<char>& s);
    
    // 임시 배열을 사용하여 괄호 배열을 확인하는 함수 (가상 함수로 선언)
    virtual bool temp_return(const vector<char>& s, vector<char> temp_s);
    
    // 순수 가상 함수로 선언된 solution 함수, 파생 클래스에서 구현해야 함
    virtual int solution(const string& s) = 0;
};

bool dict::check(const vector<char>& s) {
    // 만약 첫번째 문자가 닫는 괄호이면 false 반환
    if (s[0] == ')' || s[0] == ']' || s[0] == '}') {
        return false;
    }

    // 만약 마지막 문자가 여는 괄호이면 false 반환
    if (s[s.size() - 1] == '(' || s[s.size() - 1] == '[' || s[s.size() - 1] == '{') {
        return false;
    }
    return true;  // 위 조건을 만족하지 않으면 true 반환
}

bool dict::temp_return(const vector<char>& s, vector<char> temp_s) {
    while (!temp_s.empty()) {
        // check 함수로 괄호가 올바른지 확인, 올바르지 않으면 false 반환
        if (!check(temp_s))
            return false;

        // 첫번째 괄호에 대응하는 닫는 괄호를 temp에 저장
        char temp = bracket_dict[temp_s[0]];
        
        // 첫번째 문자를 temp_s 벡터에서 제거
        temp_s.erase(temp_s.begin());

        // temp_s 벡터에서 temp와 일치하는 닫는 괄호를 찾아 제거
        for (size_t i = 0; i < temp_s.size(); ++i) {
            if (temp == temp_s[i]) {
                temp_s.erase(temp_s.begin() + i);
                break;
            }
        }
    }
    return true;  // 모든 괄호가 올바르게 짝지어졌다면 true 반환
}

bool dict::is_valid(const vector<char>& s) {
    // 입력된 벡터를 temp_s로 복사
    vector<char> temp_s = s;

    // 여는 괄호와 닫는 괄호의 위치가 올바른지 확인, 올바르지 않으면 false 반환
    if (!check(temp_s)) {
        return false;
    }

    // temp_return 함수를 호출하여 괄호 배열이 올바른지 추가로 확인
    return temp_return(s, temp_s);
}

template <typename T>
class solution_dict : public dict {
public:
    // solution 함수 재정의
    T solution(const string& s) override {
        int answer = 0;
        
        // 문자열 길이가 홀수이면 유효하지 않은 괄호 배열이므로 0 반환
        if (s.length() % 2 != 0) {
            return answer;
        }

        // 문자열을 문자 벡터로 변환
        vector<char> s_vec(s.begin(), s.end());

        // 문자열을 회전시키며 유효한 괄호 배열인지 확인
        for (size_t i = 0; i < s_vec.size(); ++i) {
            vector<char> rotated(s_vec.begin() + i, s_vec.end());
            rotated.insert(rotated.end(), s_vec.begin(), s_vec.begin() + i);

            // 회전된 배열이 유효하다면 answer를 증가시킴
            if (is_valid(rotated)) {
                ++answer;
            }
        }

        return answer;  // 유효한 괄호 배열의 수 반환
    }
};

int solution(string s) {
    solution_dict<int> sol;
    return sol.solution(s);
}

// int main() {
//     solution_dict<int> sol;  // solution_dict 클래스를 int 타입으로 인스턴스화
//     string s = "[](){}";
//     int result = sol.solution(s);  // 첫 번째 문자열에 대한 solution 호출
//     cout << "The result is: " << result << endl;  // 결과 출력

//     string s2 = "}]()[{";
//     string s3 = "[)(]";
//     int result2 = sol.solution(s2);  // 두 번째 문자열에 대한 solution 호출
//     int result3 = sol.solution(s3);  // 세 번째 문자열에 대한 solution 호출
//     cout << "The result is: " << result2 << endl;  // 결과 출력
//     cout << "The result is: " << result3 << endl;  // 결과 출력

//     return 0;  // 프로그램 종료
// }
