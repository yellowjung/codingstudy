#include <iostream>

#define MAX (20 + 5)
using namespace std;

int N, M, X, Y, K;
int MAP[MAX][MAX];
int command[1000 + 50];

typedef struct st{
    int up;
    int left; int top; int right;
    int down;
    int buttom;
}DICE;

DICE dice;

void(*MOVE[6])(void);

void moveEast(){
    int tmp[6] = {dice.up, dice.left, dice.top, dice.right, dice.down, dice.buttom};

    dice.top = tmp[1];
    dice.right = tmp[2];
    dice.buttom = tmp[3];
    dice.left = tmp[5];
}

void moveWest(){
    int tmp[6] = {dice.up, dice.left, dice.top, dice.right, dice.down, dice.buttom};

    dice.top = tmp[3];
    dice.right = tmp[5];
    dice.buttom = tmp[1];
    dice.left = tmp[2];
}

void moveNorth(){
    int tmp[6] = {dice.up, dice.left, dice.top, dice.right, dice.down, dice.buttom};

    dice.up = tmp[2];
    dice.top = tmp[4];
    dice.down = tmp[5];
    dice.buttom = tmp[0];
}

void moveSouth(){
    int tmp[6] = {dice.up, dice.left, dice.top, dice.right, dice.down, dice.buttom};

    dice.up = tmp[5];
    dice.top = tmp[0];
    dice.down = tmp[2];
    dice.buttom = tmp[4];
}

void input(){
    cin >> N >> M >> X >> Y >> K;

    for(int r = 0; r < N; r++){
        for(int c = 0; c < M; c++){
            cin >> MAP[r][c];
        }
    }

    for(int i = 0; i < K; i++){
        cin >> command[i];
    }
}

int dr[] = {0, 0, 0, -1, 1};
int dc[] = {0, 1, -1, 0, 0};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    input();

    MOVE[1] = moveEast;
    MOVE[2] = moveWest;
    MOVE[3] = moveNorth;
    MOVE[4] = moveSouth;

    for(int i = 0; i < K; i++){
        int cmd = command[i];

        if(X + dr[cmd] < 0 || X + dr[cmd] > N - 1 || Y + dc[cmd] < 0 || Y + dc[cmd] > M - 1) continue;

        X = X + dr[cmd];
        Y = Y + dc[cmd];

        MOVE[cmd]();

        if(MAP[X][Y] == 0) MAP[X][Y] = dice.buttom;
        else{
            dice.buttom = MAP[X][Y];
            MAP[X][Y] = 0;
        }

        cout<<dice.top<<"\n";
    }

    return 0;
}