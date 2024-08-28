#include <string>
#include <vector>

using namespace std;

long long find(vector<long long>& rooms, long long room) {
    if (room >= rooms.size()) {
        return room;
    }

    if (rooms[room] == 0) {
        return room;
    }

    return rooms[room] = find(rooms, rooms[room]);
}

vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;
    vector<long long> rooms;

    for (long long room : room_number) {
        long long current_room = find(rooms, room);
        answer.push_back(current_room);

        if (current_room >= rooms.size()) {
            rooms.resize(current_room + 1, 0);
        }
        rooms[current_room] = current_room + 1;
    }

    return answer;
}

//////////////

#include <string>
#include <vector>
#include <memory>

using namespace std;

long long find(unique_ptr<vector<long long>>& rooms, long long room) {
    // 벡터의 크기를 넘는 경우 바로 방 번호를 반환
    if (room >= rooms->size()) {
        return room;
    }
    // 방이 비어있는 경우 방 번호를 반환
    if ((*rooms)[room] == 0) {
        return room;
    }
    // 경로 압축을 적용하여 다음 방 번호를 재귀적으로 찾음
    return (*rooms)[room] = find(rooms, (*rooms)[room]);
}

vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;
    auto rooms = make_unique<vector<long long>>(1, 0); // unique_ptr로 벡터 생성

    for (long long room : room_number) {
        long long current_room = find(rooms, room);
        answer.push_back(current_room);

        // 방 번호가 벡터 크기를 넘는 경우 확장
        if (current_room >= rooms->size()) {
            rooms->resize(current_room + 1, 0);
        }
        // 방이 차면 다음 방을 가리키도록 설정
        (*rooms)[current_room] = current_room + 1;
    }

    return answer;
}
