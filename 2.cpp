//https://www.acmicpc.net/problem/20056
//마법사 상어와 파이어 볼
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <queue>
#include <map>
using namespace std;

typedef struct FIRE{
    int r,c,m,s,d;
};

int nx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int ny[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int N,M,K;
int r,c,m,s,d;

vector<FIRE> MAP[51][51];
vector<FIRE> tmp_MAP[51][51];
vector<FIRE> fireballs;

int sum = 0;

void input();
void run();
void cal();
void move();
void check_map();
void calc_fireball(int r, int c);

int main(){

    input();
    run();
    cal();
    cout<<sum<<"\n";
    return 0;
}

void input(){
    // 1. 첫째 줄에 N,M,K가 주어진다
    cin>>N>>M>>K;
    // 2. 두번째 줄부터 M개 파이어볼 정보
    // r,c,m,s,d  (r, c) 방향, m 질량, d 방향, s 속력
    for(int i = 0; i < M; i++){
        cin>>r>>c>>m>>s>>d;
        FIRE newOne;
        newOne.r = r; newOne.c = c; newOne.m = m;
        newOne.s = s; newOne.d = d;
        fireballs.push_back(newOne);
        MAP[r][c].push_back(newOne);
    }
}

void run(){
    //1. 불 vector 보고 tmp 맵에 불 이동
    move();
    //2. 맵을 검사
    check_map();
    
    
}

void move(){
    for(int i = 0; i < fireballs.size(); i++){
        //1. 불 한개를 꺼낸다. (vector는 나중에 바꿀꺼라 괜찮)
        //   맵에서도 꺼내준다. 맵에는 한개만 있기 때문에 빼면 바로 없어짐
        FIRE cur = fireballs[i];
        MAP[cur.r][cur.c].pop_back();
        //2. 전체 움직일 거리 계산
        int direct = cur.d;
        int speed = cur.s;
        int total_move = direct * speed;
        //3. N으로 나누면 어차피 제자리기 때문에 나머지로만 계산
        total_move = total_move % N;
        //3-1. N을 넘을 경우
        //3-2. N을 안넘었을 경우
    }

    //불을 전부 옮겼기 때문에 초기화
    fireballs.clear();
}

void check_map(){
        //1. 맵을 검사 시 2개 있으면 1-2, 아니면 1-1
        for(int r = 0; r < N; r++){
            for(int c = 0; c < N; c++){
                if(tmp_MAP[r][c].size() > 1){
                    //1-2. 맵에서 전부 불을 빼고 계산 후 1개로 만들고
                    //     임시 불 vector에 넣어줌
                    calc_fireball(r,c);
                }else if(tmp_MAP[r][c].size() == 1){
                    //1-1. 임시 불 vector에 넣어줌 좌표 보고 실제 맵에 넣어줌
                    MAP[r][c].push_back(tmp_MAP[r][c][0]);
                    tmp_MAP[r][c].pop_back();
                }
            }
        }
        
        
        //     좌표 보고 실제 맵에 넣어줌
        //3번 반복하다가 다 끝나면
        //임시 큐를 vector로 옮겨줌
}

void calc_fireball(int r, int c){
    
}


void cal(){
    //전체 맵을 돌면서 size가 0이 아니면 불이 있는 것이기 때문에
    //질량을 전체에서 더해준다.
    for(int r = 0; r < N; r++){
        for(int c = 0; c < N; c++){
            if(!MAP[r][c].empty()){
                sum += MAP[r][c][0].m;
            }
        }
    }
}