//https://www.acmicpc.net/problem/1926
//그림
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <queue>
using namespace std;

int n, m;
int map[501][501];
int visited[501][501];
int m_size = 0;
int picture = 0;
int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

void input();
void run();
void bfs(int i, int j);
void print_map();

int main(){
    
    input();
    //print_map();
    run();
    cout<<picture<<"\n";
    cout<<m_size<<"\n";
    return 0;
}

void input(){
    cin>>n>>m;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin>>map[i][j];
        }
    }
}

void run(){
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < m; j++){
            if(map[i][j] != 0 && visited[i][j] == 0){
                bfs(i, j);
                picture++;
            }
        }
    }
}

void bfs(int i, int j){
    visited[i][j] = 1;
    queue<pair<int,int>> q;
    q.push({i,j});
    int cur_size = 0;
    while(!q.empty()){
        auto cur = q.front();
        q.pop();
        cur_size++;
        for(int dir = 0; dir < 4; dir++){
            int nx = cur.first + dx[dir];
            int ny = cur.second + dy[dir];
            if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
            if(visited[nx][ny] == 1 || map[nx][ny] == 0) continue;
            visited[nx][ny] = 1;
            q.push({nx,ny});
        }
    }
    // cout<<cur_size<<"\n";
    m_size = max(m_size, cur_size);
}

void print_map(){
    cout<<"map\n";
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout<<map[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}