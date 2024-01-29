#include <iostream>

using namespace std;

#define MAX_N 51
#define MAX_P 31

int n, m, p, c, d;
int points[MAX_P];
pair<int, int> pos[MAX_P];
pair<int, int> rudolf;

int board[MAX_N][MAX_N];
bool is_live[MAX_P];
int stun[MAX_P];

const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void input(){
    cin >> n >> m >> p >> c >> d;
    cin >> rudolf.first >> rudolf.second;
    board[rudolf.first][rudolf.second] = -1;

    for(int i = 1; i <= p; i++){
        int id;
        cin >> id;
        cin >> pos[id].first >> pos[id].second;
        board[pos[id].first][pos[id].second] = id;
        is_live[id] = true;
    }
}

bool is_inrange(int x, int y){
    return 1 <= x && x <= n && 1 <= y && y <= n;
}

void solve(){
    for(int t = 1; t <= m; t++){
        int closestX = 10000, closestY = 10000, closestIdx = 0;
        for(int i = 1; i<= p; i++){
            if(!is_live[i]) continue;

            pair<int, pair<int, int>> currentBest = { (closestX - rudolf.first) * (closestX - rudolf.first) + (closestY - rudolf.second) * (closestY - rudolf.second), {-closestX, -closestY}};
            pair<int, pair<int, int>> currentValue = {(pos[i].first - rudolf.first) * (pos[i].first - rudolf.first) + (pos[i].second - rudolf.second) * (pos[i].second - rudolf.second), {-pos[i].first, -pos[i].second}};

            if(currentValue < currentBest){
                closestX = pos[i].first;
                closestY = pos[i].second;
                closestIdx = i;
            }
        }

        if(closestIdx){
            pair<int, int> prevRudolf = rudolf;
            int moveX = 0;
            if(closestX > rudolf.first) moveX = 1;
            else if(closestX < rudolf.first) moveX = -1;

            int moveY = 0;
            if(closestY > rudolf.second) moveY = 1;
            else if(closestY < rudolf.second) moveY = -1;

            rudolf.first += moveX;
            rudolf.second += moveY;
            board[prevRudolf.first][prevRudolf.second] = 0;

            if(rudolf.first == closestX && rudolf.second == closestY){
                int firstX = closestX + moveX * c;
                int firstY = closestY + moveY * c; 
                int lastX = firstX;
                int lastY = firstY;

                stun[closestIdx] = t + 1;

                while(is_inrange(lastX, lastY) and board[lastX][lastY] > 0){
                    lastX += moveX;
                    lastY += moveY;
                }

                while(!(lastX == firstX and lastY == firstY)){
                    int beforeX = lastX - moveX;
                    int beforeY = lastY - moveY;

                    if(!is_inrange(beforeX, beforeY)) break;

                    int idx = board[beforeX][beforeY];

                    if(!is_inrange(lastX, lastY)){
                        is_live[idx] = false;
                    }else{
                        board[lastX][lastY] = board[beforeX][beforeY];
                        pos[idx] = {lastX, lastY};
                    }

                    lastX = beforeX;
                    lastY = beforeY;
                }

                points[closestIdx] += c;
                pos[closestIdx] = {firstX, firstY};
                if(is_inrange(firstX, firstY)){
                    board[firstX][firstY] = closestIdx;
                }else{
                    is_live[closestIdx] = false;
                }
            }
        }

        board[rudolf.first][rudolf.second] = -1;

        for(int i = 1; i <= p; i++){
            if(!is_live[i] || stun[i] >= t) continue;

            int minDist = (pos[i].first - rudolf.first) * (pos[i].first - rudolf.first) + (pos[i].second - rudolf.second) * (pos[i].second - rudolf.second);
            int moveDir = -1;

            for(int dir = 0; dir < 4; dir++){
                int nx = pos[i].first + dx[dir];
                int ny = pos[i].second + dy[dir];

                if(!is_inrange(nx, ny ) || board[nx][ny] > 0) continue;

                int dist = (nx - rudolf.first) * (nx - rudolf.first) + (ny - rudolf.second) * (ny - rudolf.second);
                if(dist < minDist) {
                    minDist = dist;
                    moveDir = dir;
                }
            }

            if(moveDir != -1){
                int nx = pos[i].first + dx[moveDir];
                int ny = pos[i].second + dy[moveDir];

                if(nx == rudolf.first && ny == rudolf.second) {
                    stun[i] = t + 1;

                    int moveX = -dx[moveDir];
                    int moveY = -dy[moveDir];

                    int firstX = nx + moveX * d;
                    int firstY = ny + moveY * d;
                    int lastX = firstX;
                    int lastY = firstY;

                    if(d == 1) {
                        points[i] += d;
                    }
                    else {
                        // 만약 이동한 위치에 산타가 있을 경우, 연쇄적으로 이동이 일어납니다.
                        while(is_inrange(lastX, lastY) and board[lastX][lastY] > 0) {
                            lastX += moveX;
                            lastY += moveY;
                        }

                        // 연쇄적으로 충돌이 일어난 가장 마지막 위치에서 시작해,
                        // 순차적으로 보드판에 있는 산타를 한칸씩 이동시킵니다.
                        while(!(lastX == firstX and lastY == firstY)) {
                            int beforeX = lastX - moveX;
                            int beforeY = lastY - moveY;

                            if(!is_inrange(beforeX, beforeY)) break;

                            int idx = board[beforeX][beforeY];

                            if(!is_inrange(lastX, lastY)) {
                                is_live[idx] = false;
                            }
                            else {
                                board[lastX][lastY] = board[beforeX][beforeY];
                                pos[idx] = {lastX, lastY};
                            }

                            lastX = beforeX;
                            lastY = beforeY;
                        }

                        points[i] += d;
                        board[pos[i].first][pos[i].second] = 0;
                        pos[i] = {firstX, firstY};
                        if(is_inrange(firstX, firstY)) {
                            board[firstX][firstY] = i;
                        }
                        else {
                            is_live[i] = false;
                        }
                    }470
                }
                else {
                    board[pos[i].first][pos[i].second] = 0;
                    pos[i] = {nx, ny};
                    board[nx][ny] = i;
                }
            }
        }
        for(int i = 1; i <= p; i++){
            if(is_live[i])points[i]++;
        }
    }

    for(int i = 1; i <= p; i++){
        cout<< points[i]<<" ";
    }
}

void solution(){
    input();
    solve();
}

int main(){

    solution();

    return 0;
}