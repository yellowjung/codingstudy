//연구소
//14502번
//https://www.acmicpc.net/problem/14502
//기본 연습
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define MAX 11

using namespace std;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

vector<pair<int,int>> virus;

int N, M;
int MAP[MAX][MAX];
int Visited[MAX][MAX];

int BIG = 0;

void input(){
    cin>>N>>M;
    for(int y = 0; y < N; y++){
        for(int x = 0; x < M; x++){
            cin>>MAP[y][x];
            if(MAP[y][x] == 2){
                virus.push_back({y,x});
            }
        }
    }
}

void clear_visited(){
    for(int y = 0; y < MAX; y++){
        for(int x = 0; x < MAX; x++){
            Visited[y][x] = 0;
        }
    }
}

void bfs(){
    queue<pair<int,int>> q;
    clear_visited();
    for(int i = 0; i < virus.size(); i++){
        q.push(virus[i]);
        Visited[virus[i].first][virus[i].second] = 1;
    }
    
    while(!q.empty()){
        auto cur = q.front(); q.pop();

        for(int dir = 0; dir < 4; dir++){
            int ny = cur.first + dy[dir];
            int nx = cur.second + dx[dir];
            if(ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
            if(MAP[ny][nx] != 0 || Visited[ny][nx] != 0) continue;
            Visited[ny][nx] = 1;
            q.push({ny,nx});
        }
    }

    
}

void check_map(){
    int tmp_count = 0;
    for(int y = 0; y < N; y++){
        for(int x = 0; x < M; x++){
            if(MAP[y][x] == 0 && Visited[y][x] == 0){
                tmp_count++;
            }
        }
    }
    BIG = max(BIG, tmp_count);
}

void selected(int count){
    if(count == 3){
        bfs();
       check_map(); 
        return;
    }

    for(int y = 0; y < N; y++){
        for(int x = 0; x < M; x++){
            if(MAP[y][x] == 0){
                MAP[y][x] = 1;
                selected(count + 1);
                MAP[y][x] = 0;
            }
        }
    }
}

void run(){
    selected(0);
}

void solve(){
    input();
    run();
}

int main(){

    solve();
    cout<<BIG<<"\n";
    return 0;
}
