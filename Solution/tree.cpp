#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 20

using namespace std;

struct info{
    int cnt, x, y;
};

int dx[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};

int N, M, K, C;
int MAP[MAX][MAX] = {0, };
int herbicide[MAX][MAX] = {0, };
int res = 0;

void input(){
    cin >> N >> M >> K >> C;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> MAP[i][j];
        }
    }
}

void growthTree(){
    int addTree[MAX][MAX] = {0, };
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(MAP[i][j] <= 0) continue;
            int cnt = 0;
            for(int k = 0; k < 8; k+=2){
                int nx = i + dx[k];
                int ny = j + dy[k];

                if(nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
                if(MAP[ny][nx] <= 0) continue;
                cnt++;
            }
            addTree[i][j] = cnt;
        }
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            MAP[i][j] += addTree[i][j];
        }
    }
}

void breedTree(){
    int addTree[MAX][MAX] = {0, };

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(MAP[i][j] <= 0) continue;
            int cnt = 0;
            for(int k = 0; k < 8; k += 2){
                int nx = i + dx[k];
                int ny = j + dy[k];
                if(nx < 0 || ny < 0 || nx >= N || ny >= N || MAP[nx][ny] != 0 || herbicide[nx][ny] != 0) continue;
                cnt++;
            }

            for(int k = 0; k < 8; k+= 2){
                int nx = i + dx[k];
                int ny = j + dy[k];
                if(nx < 0 || ny < 0 || nx >= N || ny >= N || MAP[nx][ny] != 0 || herbicide[nx][ny] != 0) continue;
                addTree[nx][ny] += MAP[i][j]/cnt;
            }
        }
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            MAP[i][j] += addTree[i][j];
        }
    }
}

void deleteHerb(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(herbicide[i][j] == 0) continue;
            herbicide[i][j] -= 1;
        }
    }
}

bool comp(info A, info B){
    if(A.cnt > B.cnt) {
        return true;
    }else if(A.cnt < B.cnt){
        return false;
    }

    if(A.x < B.x){
        return true;
    }else if(A.x > B.x){
        return false;
    }

    if(A.y < B.y){
        return true;
    }

    return false;
}

void dieTree(){
    vector<info> die;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(MAP[i][j] <= 0) continue;
            int cnt = MAP[i][j];
            for(int d = 1; d < 8; d += 2){
                for(int l = 1; l <= K; l++){
                    int nx = i + dx[d] * l;
                    int ny = j + dy[d] * l;
                    if( nx < 0 || ny < 0 || nx >= N || ny >= N || MAP[nx][ny] <= 0) break;
                    cnt += MAP[nx][ny];
                }
            }
            if(cnt > 0) die.push_back({cnt, i, j});
        }
    }

    if(die.size() == 0) return;

    sort(die.begin(), die.end(), comp);

    res += die[0].cnt;
    int x = die[0].x;
    int y = die[0].y;

    if(MAP[x][y] > 0){
        MAP[x][y] = 0;
        herbicide[x][y] = C;

        for(int d = 1; d < 8; d+= 2){
            for(int l = 1; l <= K; l++){
                int nx = x + dx[d] * l;
                int ny = y + dy[d] * l;
                if( nx < 0 || ny < 0 || nx >= N || ny >= N || MAP[nx][ny] < 0 ) break;

                herbicide[nx][ny] = C;

                if(MAP[nx][ny] == 0){
                    break;
                }else{
                    MAP[nx][ny] = 0;
                }
            }
        }
    }
}

void Solution(){
    for(int i = 0; i < M; i++){
        growthTree();
        breedTree();
        deleteHerb();
        dieTree();
    }

    cout << res << "\n";
}

void Solve(){
    input();
    Solution();
}

int main(){

    Solve();

    return 0;
}