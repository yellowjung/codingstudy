#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

int N, M;
int Map[16][16];
int Visit[16][16];
int dist[16][16];

int PX;
int PY;

int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};

struct BaseCamp{
    int x;
    int y;
};

vector<BaseCamp> vector_camp;

struct Store{
    int x; 
    int y;
    int full;
};

vector<Store> vector_store;

struct Person{
    int x;
    int y;
};

vector<Person> vector_person;

void input(){
    cin >> N >> M;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            cin >> Map[i][j];
            if(Map[i][j] == 1){
                vector_camp.push_back({i, j});
            }
        }
    }

    for(int i = 1; i <= M; i++){
        int x, y;
        cin >> x >> y;
        vector_store.push_back({x ,y, false});
    }
}

void Clear_Dist(){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            dist[i][j] = 9999;
        }
    }
}

void Bfs(int x, int y){
    queue<pair<pair<int,int>,int>>Q;
    Q.push({{x, y}, 0});
    dist[x][y] = 0;

    while(!Q.empty()){
        int px = Q.front().first.first;
        int py = Q.front().first.second;
        int time = Q.front().second;
        Q.pop();

        for(int i = 0; i < 4; i++){
            int nx = px + dx[i];
            int ny = py + dy[i];

            if(nx < 1 || ny < 1 || nx > N || ny > N) continue;
            if(Visit[nx][ny] == 1) continue;
            if(dist[nx][ny] != 9999) continue;

            dist[nx][ny] = time + 1;
            Q.push({{nx, ny}, time + 1});
        }
    }
}

void Move(int n){
    int gx = vector_store[n].x;
    int gy = vector_store[n].y;
    Bfs(gx, gy);

    int px = vector_person[n].x;
    int py = vector_person[n].y;
    int Min = 9999;

    for(int i = 0; i < 4; i++){
        int nx = px + dx[i];
        int ny = py + dy[i];

        if(nx < 1 || ny < 1 || nx > N || ny > N) continue;
        if(Visit[nx][ny] == 1) continue;

        if(dist[nx][ny] < Min){
            Min = dist[nx][ny];
            vector_person[n].x = nx;
            vector_person[n].y = ny;
        }
    }
}

void go_conv(){
    for(int i = 0; i < vector_person.size(); i++){
        if(vector_store[i].full == true)continue;
        Clear_Dist();
        Move(i);
    }
}

void arrive(){
    for(int i = 0; i < vector_person.size(); i++){
        if(vector_store[i].full == true) continue;

        if(vector_person[i].x == vector_store[i].x && vector_person[i].y == vector_store[i].y){
            vector_store[i].full = true;
            Visit[vector_store[i].x][vector_store[i].y] = 1;
        }
    }
}

bool Check_Full(){
    for(auto E : vector_store){
        if(E.full == false) return false;
    }
    return true;
}

void insertPeople(int time){
    PX = vector_store[time].x;
    PY = vector_store[time].y;

    Clear_Dist();
    Bfs(PX, PY);

    int Min = 9999;
    int X;
    int Y;

    for(int i = N; i >= 1; i--){
        for(int j = N; j >= 1; j--){
            if(Map[i][j] == 1 && dist[i][j] <= Min){
                Min = dist[i][j];
                X = i;
                Y = j;
            }
        }
    }

    vector_person.push_back({X, Y});
    Visit[X][Y] = 1;
}

void solution(){
    int Time = 0;
    while(true){
        go_conv();

        arrive();

        if(Check_Full() == true){
            break;
        }

        if(Time < M){
            insertPeople(Time);
        }

        Time++;
    }
}

void solve(){
    input();
    solution();
}

int main() {
    // 여기에 코드를 작성해주세요.
    solve();
    return 0;
}