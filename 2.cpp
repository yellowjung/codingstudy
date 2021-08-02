//https://www.acmicpc.net/problem/20056
//마법사 상어와 파이어 볼
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <queue>
#include <map>
using namespace std;

typedef struct fireball{
    int r,c,m,s,d;
};

int nx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int ny[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int N,M,K;
int r,c,m,s,d;

vector<fireball> MAP[51][51];
vector<fireball> fireballs;

void input();
void move();
void cal();

int main(){

    input();
    move();
    cal();

    return 0;
}

void input(){
    // 1. 첫째 줄에 N,M,K가 주어진다
    cin>>N>>M>>K;
    // 2. 두번째 줄부터 M개 파이어볼 정보
    // r,c,m,s,d  (r, c) 방향, m 질량, d 방향, s 속력
    for(int i = 0; i < M; i++){
        cin>>r>>c>>m>>s>>d;
        fireball newOne;
        newOne.r = r; newOne.c = c; newOne.m = m;
        newOne.s = s; newOne.d = d;
        fireballs.push_back(newOne);
        MAP[r][c].push_back(newOne);
    }
}

void move(){
    //1. 불 vector 보고 tmp 맵에 불 이동
    //2. 맵을 검사
    //3. 맵을 검사 시 2개 있으면 3-2, 아니면 3-1
    //3-1. 임시 불 vector에 넣어줌 좌표 보고 실제 맵에 넣어줌
    //3-2. 맵에서 전부 불을 빼고 계산 후 1개로 만들고
    //     임시 불 vector에 넣어줌
    //     좌표 보고 실제 맵에 넣어줌
    //3번 반복하다가 다 끝나면
    //임시 큐를 vector로 옮겨줌
    
}