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
    int left; int top; int right;
    int down;
    int buttom;
}DICE;

DICE dice;

typedef struct st2{
    int r;
    int c;
}RC;

RC queue[MAX * MAX];

void(*MOVE[6])(void);

void moveEast(){
    int tmp[6] = {dice.up, dice.left, dice.top, dice.right, dice.down, dice.buttom};

    dice.top = tmp[1];
    dice.right = tmp[2];
    dice.buttom = tmp[3];
    dice.left= tmp[5];
}

void moveWest(){
    int tmp[6] = {dice.up, dice.left, dice.top, dice.right, dice.down, dice.buttom};

    dice.top = tmp[3];
    dice.right = tmp[5];
    dice.buttom = tmp[1];
    dice.left= tmp[2];
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
    cin >> N >> M >> K;

    for(int r = 1; r <= N; r++){
        for(int c = 1; c <= M; c++){
            cin >> MAP[r][c];
        }
    }
}

int dr[] = {0, 0, 0, -1 ,1};
int dc[] = {0, 1, -1, 0, 0,};

int scoreBoard[MAX][MAX];

int BFS(int r, int c){
    int wp, rp, number;
    int visit[MAX][MAX] = {0};

    wp = rp = 0;

    queue[wp].r = r;
    queue[wp++].c = c;

    visit[r][c] = 1;
    number = MAP[r][c];

    while(wp > rp){
        RC out = queue[rp++];

        for(int i = 1; i <= 4; i++){
            int nr = out.r + dr[i];
            int nc = out.c + dc[i];

            if(nr <= 0 || nc <= 0 || nr > N || nc > M) continue;

            if(visit[nr][nc] == 0 && number == MAP[nr][nc]){
                queue[wp].r = nr;
                queue[wp++].c = nc;

                visit[nr][nc] = 1;
            }
        }
    }
    
    return wp * number;
}

int main(){

    int row, col, dir;
    int changeDir[5] = {0};
    int changeClock[5] = {0};
    int changeCounterClock[5] = {0};
    int score;

    input();

    MOVE[EAST] = moveEast;
    MOVE[WEST] = moveWest;
    MOVE[NORTH] = moveNorth;
    MOVE[SOUTH] = moveSouth;

    changeDir[EAST] = WEST;
    changeDir[WEST] = EAST;
    changeDir[NORTH] = SOUTH;
    changeDir[SOUTH] = NORTH;

    changeClock[EAST] = SOUTH;
    changeClock[SOUTH] = WEST;
    changeClock[WEST] = NORTH;
    changeClock[NORTH] = EAST;

    changeCounterClock[EAST] = NORTH;
    changeCounterClock[NORTH] = WEST;
    changeCounterClock[WEST] = SOUTH; 
    changeCounterClock[SOUTH] = EAST;

    for(int r = 1; r <= N; r++){
        for(int c = 1; c <= M; c++){
            scoreBoard[r][c] = BFS(r, c);
        }
    }

    dice.up = 2;
    dice.left = 4; dice.top = 1; dice.right = 3;
    dice.down = 5;
    dice.buttom = 6;

    row = 1, col = 1, dir = EAST;
    score = 0;

    for(int i = 0; i < K; i++){
        int nr, nc, A, B;

        nr = row + dr[dir];
        nc = col + dc[dir];

        if(nr <= 0 || nc <= 0 || nr > N || nc > M){
            dir = changeDir[dir];
            nr = row + dr[dir];
            nc = col + dc[dir];
        }

        MOVE[dir]();

        score += scoreBoard[nr][nc];

        A = dice.buttom;
        B = MAP[nr][nc];

        if(A > B) dir = changeClock[dir];
        else if(A < B) dir = changeCounterClock[dir];

        row = nr;
        col = nc;
    }

    cout<<score<<"\n";

    return 0;
}