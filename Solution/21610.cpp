#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

#define MAX 55

int N, M, Answer;
int MAP[MAX][MAX];
bool Cloud_MAP[MAX][MAX];
vector<pair<int, int>> Cloud;
vector<pair<int, int>> Cmd;

int dx[] = { 0, 0, -1, -1, -1, 0, 1, 1, 1};
int dy[] = { 0, -1, -1, 0, 1, 1, 1, 0, -1};

void Input(){
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> MAP[i][j];
        }
    }
    for(int i = 0; i < M; i++){
        int a, b;
        cin >> a >> b;
        Cmd.push_back({a, b});
    }
}

void Init_Cloud(){
    Cloud.push_back({N - 2, 0});
    Cloud.push_back({N - 2, 1});
    Cloud.push_back({N - 1, 0});
    Cloud.push_back({N - 1, 1});
    Cloud_MAP[N - 2][0] = true;
    Cloud_MAP[N - 2][1] = true;
    Cloud_MAP[N - 1][0] = true;
    Cloud_MAP[N - 1][1] = true;
}

int Make_Range(int x){
    if(x < 0) return N - 1;
    if(x >= N) return 0;
    return x;
}

void Move_Cloud(int Idx){
    int Dir = Cmd[Idx].first;
    int Cnt = Cmd[Idx].second;

    memset(Cloud_MAP, false, sizeof(Cloud_MAP));
    for(int i = 0; i < Cloud.size(); i++){
        int x = Cloud[i].first;
        int y = Cloud[i].second;
        int nx = x;
        int ny = y;
        for(int j = 0; j < Cnt; j++){
            nx += dx[Dir];
            ny += dy[Dir];
            nx = Make_Range(nx);
            ny = Make_Range(ny);
        }
        Cloud[i].first = nx;
        Cloud[i].second = ny;
    }
    for(int i = 0; i < Cloud.size(); i++){
        int x = Cloud[i].first;
        int y = Cloud[i].second;
        Cloud_MAP[x][y] = true;
    }
}

void Make_Rain(){
    for(int i = 0; i < Cloud.size(); i++){
        int x = Cloud[i].first;
        int y = Cloud[i].second;
        MAP[x][y]++;
    }
}

void Water_Bug(){
    for(int i = 0; i < Cloud.size(); i++){
        int x = Cloud[i].first;
        int y = Cloud[i].second;
        int Cnt = 0;
        for(int j = 2; j <= 8; j += 2){
            int nx = x + dx[j];
            int ny = y + dy[j];
            if(nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
            if(MAP[nx][ny] >= 1) Cnt++;
        }
        MAP[x][y] += Cnt;
    }
}

void Delete_Cloud(){
    Cloud.clear();
}

void Make_Cloud(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(Cloud_MAP[i][j] == true) continue;
            if(MAP[i][j] < 2) continue;
            MAP[i][j] -= 2;
            Cloud.push_back({i, j});
        }
    }

    memset(Cloud_MAP, false, sizeof(Cloud_MAP));
    for(int i = 0; i < Cloud.size(); i++){
        int x = Cloud[i].first;
        int y = Cloud[i].second;
        Cloud_MAP[x][y] = true;
    }
}

void Find_Answer(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            Answer += MAP[i][j];
        }
    }
}

void Solution(){
    Init_Cloud();
    for(int i = 0; i < M; i++){
        Move_Cloud(i);
        Make_Rain();
        Water_Bug();
        Delete_Cloud();
        Make_Cloud();
    }
    Find_Answer();
    cout << Answer << "\n";
}

void Solve(){
    Input();
    Solution();
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Solve();

    return 0;
}