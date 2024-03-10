#include <iostream>

using namespace std;

#define MAX (500)
#define OFFSET (250)

int T, N, M, K;
int MAP[MAX][MAX];

typedef struct st{
    int r;
    int c;
    int life;
    int time;
}CELL;

CELL cell[MAX * MAX];
CELL liveCell[MAX * MAX];
CELL spreadCell[MAX * MAX];
CELL deadCell[MAX * MAX];
int ccnt, lcnt, scnt, dcnt;

int dr[] = {0, -1, 0, 1};
int dc[] = {-1, 0, 1, 0};

void input(){
    cin >> N >> M >> K;

    for(int r = 0; r < MAX; r++){
        for(int c = 0; c < MAX; c++){
            MAP[r][c] = 0;
        }
    }

    ccnt = 0;
    for(int r = 0; r < N; r++){
        for(int c = 0; c < M; c++){
            int life;

            cin >> life;
            MAP[r + OFFSET][c + OFFSET] = life;

            if(life){
                cell[ccnt].r = r + OFFSET;
                cell[ccnt].c = c + OFFSET;
                cell[ccnt].life = life;
                cell[ccnt++].time = life;
            }
        }
    }
}

int main(){

    cin >> T;

    for(int tc = 1; tc <= T; tc++){
        input();

        for(int time = 0; time < K; time++){
            lcnt = scnt = 0;

            int indexMAP[MAX][MAX] = { 0 };
            for(int i = 0; i < ccnt; i++){
                if(cell[i].time){
                    cell[i].time--;
                    liveCell[lcnt++] = cell[i];
                }else{
                    deadCell[dcnt] = cell[i];
                    dcnt++;

                    for(int dir = 0; dir < 4; dir++){
                        int nr, nc;

                        nr = cell[i].r + dr[dir];
                        nc = cell[i].c + dc[dir];

                        if(MAP[nr][nc]) continue;

                        spreadCell[scnt].r = nr;
                        spreadCell[scnt].c = nc;
                        spreadCell[scnt].life = cell[i].life;
                        spreadCell[scnt++].time = cell[i].life;
                    }
                }
            }

            int ddcnt = 0;
            for(int i = 0; i < dcnt; i++){
                deadCell[i].life--;
                if(deadCell[i].life){
                    deadCell[ddcnt++] = deadCell[i];
                }
            }

            dcnt = ddcnt;

            for(int i = 0; i < scnt; i++){
                int nr, nc;

                nr = spreadCell[i].r;
                nc = spreadCell[i].c;

                if(MAP[nr][nc] == 0){
                    MAP[nr][nc] = spreadCell[i].life;
                    indexMAP[nr][nc] = i;
                }else if(MAP[nr][nc] < spreadCell[i].life){
                    spreadCell[indexMAP[nr][nc]].life = 0;
                    MAP[nr][nc] = spreadCell[i].life;
                    indexMAP[nr][nc] = i;
                }else{
                    spreadCell[i].time = 0;
                }
            }

            for(int i = 0; i < scnt; i++){
                if(spreadCell[i].time){
                    liveCell[lcnt++] = spreadCell[i];
                }
            }

            for(int i = 0; i < lcnt; i++){
                cell[i] = liveCell[i];
            }

            ccnt = lcnt;
        }

        cout<<"#"<<tc<<" "<<lcnt + dcnt<<"\n";
    }

    return 0;
}