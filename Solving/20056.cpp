#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

typedef struct{
    int y, x, m, s, d;
}FIRE;

int N,  M, K;
vector<FIRE> MAP[51][51];
vector<FIRE> fires;
int mx[8] = {0, 1, 1, 1, 0 , -1, -1, -1};
int my[8] = {-1, -1, 0 , 1, 1, 1, 0, -1};

void move(){
    for(int i = 0; i < fires.size(); i++){
        FIRE cur = fires[i];
        int ny = (my[cur.d] * cur.s % N) + cur.y; 
        int nx = (mx[cur.d] * cur.s % N) + cur.x;
        if(ny >= N){
            ny = N - ny;   
        }else if(ny < 0){
            ny = N + ny;
        }
        
        if(nx >= N){
            nx = N - nx;
        }else if(ny < 0){
            ny = N + ny;
        }

        cur.x = nx;
        cur.y = ny;

        MAP[cur.y][cur.x].push_back(cur);
    }
    fires.clear();
}

void cal_fire(int y, int x){
    int size = MAP[y][x].size();
    int sum_m = 0, sum_s = 0;
    bool odd = false,  even = false;
    for(int i = 0; i < size; i++){
        FIRE cur = MAP[y][x][i];
        sum_m += cur.m;
        sum_s += cur.s;
        if(cur.d % 2 == 0){
            odd = true;
        }else{
            even = true;
        }
    }
    sum_m = sum_m / 5;
    sum_s = sum_s / MAP[y][x].size();
    if(sum_m == 0){
        MAP[y][x].clear();
        return;
    }

    if(odd == false || even == false){
        for(int i = 0; i <= 6; i += 2){
            fires.push_back({y,x,sum_m,sum_s,i});
        }
    }else{
        for(int i = 1; i <= 7; i += 2){
            fires.push_back({y,x,sum_m,sum_s,i});
        }
    }

    MAP[y][x].clear();
}

void check_map(){
    for(int y = 0; y < N; y++){
        for(int x = 0; x < N; x++){
            if(MAP[y][x].size() >= 2){
                cal_fire(y,x);
            }else{
                fires.push_back(MAP[y][x][0]);
                MAP[y][x].clear();
            }
        }
    }
}
void run(){
    //TODO : k만큼아돌려야함
    //1. move
    move();
    //2. firebal check
    check_map();
}

void input(){
    cin>>N>>M>>K;
    for(int i = 0; i < M; i++){
        int y, x, m, d, s;
        cin>>y>>x>>m>>d>>s;
        FIRE fire = {y,x,m,d,s};
        fires.push_back(fire);
    }
}

void solve(){
    void input();
    void run();
}

int main(){

    solve();

    return 0;
}