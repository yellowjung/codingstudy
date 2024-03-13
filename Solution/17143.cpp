#include <iostream>

#define MAX (100 + 20)
using namespace std;

int R, C, M;

typedef struct st{
    int speed;
    int dir;
    int size;
}SHARK;

SHARK shark[MAX][MAX];

void input(){
    cin >> R >> C >> M;

    for(int i = 0 ; i < M ; i++){
        int r, c, s, d, z;

        cin >> r >> c >> s >> d >> z;
        shark[r][c].speed = s;
        shark[r][c].dir = d;
        shark[r][c].size = z;
    }
}

int catchShark(int c){
    for(int r = 1; r <= R; r++){
        if(shark[r][c].size){
            int ret = shark[r][c].size;

            shark[r][c].size = 0;

            return ret;
        }
    }

    return 0;
}

int dr[] = {0, -1, 1, 0, 0};
int dc[] = {0, 0, 0, 1, -1};

void moveShark(){
    int changeDir[5] = {0, 2, 1, 4, 3};
    SHARK tmpShark[MAX][MAX] = {};

    for(int r = 1; r <= R; r++){
        for(int c = 1; c <= C; c++){
            if(shark[r][c].size == 0) continue;

            SHARK shk = shark[r][c];

            if(shk.dir <= 2){
                int move = shk.speed;
                int sr, dir;

                sr = r;
                dir = shk.dir;

                for(int m = 0; m < move; m++){
                    int nr;

                    nr = sr + dr[dir];

                    if(nr < 1){
                        dir = changeDir[dir];
                        sr = 2;
                        continue;
                    }

                    if(nr > R){
                        dir = changeDir[dir];
                        sr = R - 1;
                        continue;
                    }

                    sr = nr;
                }
                if(tmpShark[sr][c].size < shark[r][c].size){
                    tmpShark[sr][c] = shark[r][c];
                    tmpShark[sr][c].dir = dir;
                }
            }else{
                int move = shk.speed;
                int sc, dir;

                sc = c;
                dir = shk.dir;

                for(int m = 0; m < move; m++){
                    int nc;

                    nc = nc + dc[dir];

                    if(nc < 1){
                        dir = changeDir[dir];
                        sc = 2;
                        continue;
                    }

                    if(nc > C){
                        dir = changeDir[dir];
                        sc = C - 1;
                        continue;
                    }

                    sc = nc;
                }
                if(tmpShark[r][sc].size < shark[r][c].size){
                    tmpShark[r][sc] = shark[r][c];
                    tmpShark[r][sc].dir = dir;
                }
            }
        }
    }
    for(int r = 1; r <= R; r++){
        for(int c = 1; c <= C; c++){
            shark[r][c] = tmpShark[r][c];
        }
    }
}

int main(){

    int ans;

    input();

    ans = 0;
    for(int c = 1; c <= C; c++){
        ans += catchShark(c);
        moveShark();
    }

    cout << ans <<"\n";

    return 0;
}