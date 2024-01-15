#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

#define MAX 8

int visited[MAX][MAX];
int map[MAX][MAX];
vector<pair<int,int>> virus;
int answer = 0;

int N, M;
int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

void input(){
    cin >> N >> M;
    for(int y = 0; y < N; y++){
        for (int x = 0; x < M; x++){
            cin>>map[y][x];
            if(map[y][x] == 2){
                virus.push_back({y,x});
            }
        }
    }
}

void init(){
    for(int y = 0; y < N; y++){
        for(int x = 0; x < M; x++){
            visited[y][x] = 0;
        }
    }
}

void check(){
    int tmp_count = 0;
    for(int y = 0; y < N; y++){
        for(int x = 0; x < M; x++){
            if(visited[y][x] == 0 && map[y][x] == 0) tmp_count++;
        }
    }

    answer = max(answer, tmp_count);
}

void bfs(){
    queue<pair<int,int>> q;
    for(int i = 0; i < virus.size(); i++){
        q.push(virus[i]);
        visited[virus[i].first][virus[i].second] = 1;
    }

    while(!q.empty()){
        auto now = q.front();
        q.pop();

        for(int dir = 0; dir < 4; dir++){          
            int nx = now.second + dx[dir];
            int ny = now.first + dy[dir];
            if(nx < 0 || ny < 0 || nx >= M || ny >= N) continue;
            if(visited[ny][nx] == 1 || map[ny][nx] == 1) continue;
            visited[ny][nx] = 1;
            q.push({ny, nx});
        }
    }

    check();
}

void solution(int count){
    if(count == 3){
        init();
        bfs();
        return;
    }

    for(int y = 0; y < N ; y++){
        for(int x = 0; x < M; x++){
            if(map[y][x] == 0){
                map[y][x] = 1;
                solution(count + 1);
                map[y][x] = 0;
            }
        }
    }


}

int main(){

    input();
    solution(0);
    cout<<answer<<"\n";
    return 0;
}