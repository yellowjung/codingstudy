#include <iostream>

using namespace std;

#define MAX ( 20 + 5 )
#define EAST (1)
#define WEST (2)
#define NORTH (3)
#define SOUTH (4)

int N, M, K;
int MAP[MAX][MAX];

typedef struct st1{
    int up;
    int left;
    int top;
    int right;
    int down;
    int bottom;
}DICE;

DICE dice;

typedef struct st2{
    int r;
    int c;
}RC;

RC queue[MAX * MAX];

void(*MOVE[6])(void);

void input(){
    cin >> N >> M >> K;

    for(int r = 1; r <= N; r++){
        for(int c = 1; c <= M; c++){
            cin >> MAP[r][c];
        }
    }
}

int main(){

    return 0;
}