#include <iostream>
#include <stack>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
using namespace std;

#define MAX 8

int map[MAX][MAX];
int visited[MAX][MAX];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
vector<pair<int,int>> virus;
int top = 0;

int r, c;

void input();
void print();
void init();
void solve();
void check();
void selected(int count);

int main(){
    input();
    selected(0);

    cout<<top<<"\n";

    return 0;
}

void selected(int count){
    if(count == 3){
        init();
        solve();
        check();
        return;
    }

    for(int y = 0; y < r; y++){
        for(int x = 0; x < c; x++){
            if(map[y][x] == 0){
                map[y][x] = 1;
                selected(count + 1);
                map[y][x] = 0;
            }
        }
    }
}

void check(){
    int tmp_count = 0;
    for(int y = 0; y < r; y++){
        for(int x = 0; x < c; x++){
            if(visited[y][x] == 0 && map[y][x] == 0){
                tmp_count++;
            }
        }
    }
    top = max(tmp_count, top);
}

void solve(){
    queue<pair<int,int>> q;
    for(int loop = 0; loop < virus.size(); loop++){
        q.push(virus[loop]);
        visited[virus[loop].first][virus[loop].second] = 1;
    }

    while(!q.empty()){
        auto cur = q.front(); q.pop();
        for(int dir = 0; dir < 4; dir++){
            int nx = cur.second + dx[dir];
            int ny = cur.first + dy[dir];
            if(nx < 0 || ny < 0 || nx >= c || ny >= r) continue;
            if(map[ny][nx] == 1 || visited[ny][nx] == 1) continue;
            visited[ny][nx] = 1;
            q.push({ny,nx});
        }
    }
}


void input(){
    cin >> r >> c;
    for(int y = 0; y < r; y++){
        for(int x = 0; x < c; x++){
            cin >> map[y][x];
            if(map[y][x] == 2){
                virus.push_back({y,x});
            }
        }
    }
}

void init(){
    for(int y = 0; y < r; y++){
        for(int x = 0; x < c; x++){
            visited[y][x] = 0;
        }
    }
}

void print(){
    cout<<"\n";
    for(int y = 0; y < r; y++){
        for(int x = 0; x < c; x++){
            cout << map[y][x] <<" ";
        }
        cout<<"\n";
    }
}