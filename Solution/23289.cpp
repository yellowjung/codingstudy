#include <iostream>

using namespace std;

#define MAX (20 + 10)
#define RIGHT (1)
#define LEFT (2)
#define UP (3)
#define DOWN (4)

int dr[] = {0, 0, 0, -1 ,1};
int dc[] = {0, -1, -1, 0, 0};

int R, C, K, W;
int A[MAX][MAX];
int MAP[MAX][MAX];

typedef struct st1{
    int r;
    int c;
}RC;

RC checkPoint[MAX * MAX];
int ccnt;

typedef struct st2{
    int r;
    int c;
    int dir;
}HEATER;

HEATER heater[MAX * MAX];
int hcnt;

typedef struct st3{
    int r;
    int c;
    int temp;
}QUEUE;

typedef struct st4{
    int direction[5];
}WALL;

WALL wall[MAX][MAX];

void input(){
    cin >> R >> C >> K;

    for(int r = 1; r <= R; r++){
        for(int c = 1; c <= C; c++){
            cin >> A[r][c];

            if(A[r][c] == 5){
                checkPoint[ccnt].r = r;
                checkPoint[ccnt++].c = c;
            }else if(A[r][c] != 0){
                heater[hcnt].r = r;
                heater[hcnt].c = c;
                heater[hcnt++].dir = A[r][c];
            }
        }
    }

    cin >> W;

    for(int i = 0; i < W; i++){
        int r, c, t;

        cin >> r >> c >> t;

        if(t == 1){
            wall[r][c].direction[RIGHT] = 1;
            wall[r][c + 1].direction[LEFT] = 1;
        }else{
            wall[r][c].direction[UP] = 1;
            wall[r - 1][c].direction[DOWN] = 1;
        }
    }
}

void output(int map[MAX][MAX]){
    for(int r = 1; r <= R; r++){
        for(int c = 1; c <= C; c++){
            cout<<map[r][c]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

void heat(int r, int c, int dir){
    QUEUE queue[MAX * MAX];

    int visit[MAX][MAX] = {0};
    int wp, rp;
    int sr, sc, temp;

    temp = 5;
    sr = r, sc = c;

    wp = rp = 0;

    queue[wp].r = r;
    queue[wp].c = c;
    queue[wp++].temp = 5;

    visit[r][c] = 1;

    while(wp > rp){
        QUEUE out = queue[rp++];

        if(out.temp == 0) break;

        if(out.r <= 0 || out.c <= 0 || out.r > R || out.c > C) continue;

        MAP[out.r][out.c] += out.temp;

        if(dir == RIGHT || dir == LEFT){
            int nr, nc;

            nc = out.c + dc[dir];

            nr = out.r - 1;
            if(visit[nr][nc] == 0 && (wall[out.r][out.c].direction[UP] == 0) && (wall[nr][out.c].direction[dir] == 0)){
                queue[wp].r = nr;
                queue[wp].c = nc;
                queue[wp++].temp = out.temp - 1;

                visit[nr][nc] = 1;
            }

            nr = out.r;
            if(visit[nr][nc] == 0 && (wall[out.r][out.c].direction[dir] == 0)){
                queue[wp].r = nr;
                queue[wp].c = nc;
                queue[wp++].temp = out.temp - 1;

                visit[nr][nc] = 1;
            }

            nr = out.r + 1;
            if(visit[nr][nc] == 0 && (wall[out.r][out.c].direction[DOWN] == 0) && (wall[nr][out.c].direction[dir] == 0)){
                queue[wp].r = nr;
                queue[wp].c = nc;
                queue[wp++].temp = out.temp - 1;

                visit[nr][nc] = 1;
            }
        }else{
            int nr, nc;

            nr = out.r + dr[dir];

            nc = out.c - 1;
            if(visit[nr][nc] == 0 && (wall[out.r][out.c].direction[LEFT] == 0) && (wall[out.r][nc].direction[dir] == 0)){
                queue[wp].r = nr;
                queue[wp].c == nc;
                queue[wp++].temp = out.temp - 1;

                visit[nr][nc] = 1;
            }


            nc = out.c;
            if(visit[nr][nc] == 0 && (wall[out.r][out.c].direction[dir] == 0)){
                queue[wp].r = nr;
                queue[wp].c = nc;
                queue[wp].temp = out.temp - 1;

                visit[nr][nc] = 1;
            }

            nc = out.c + 1;
            if(visit[nr][nc] == 0 && (wall[out.r][out.c].direction[RIGHT] == 0) && (wall[out.r][nc].direction[dir] == 0)){
                queue[wp].r = nr;
                queue[wp].c = nc;
                queue[wp++].temp = out.temp - 1;

                visit[nr][nc] = 1;

            }
        }



    }
}

void controlTemperature(){
    int tmpMAP[MAX][MAX] = { 0 };

    for(int r = 1; r <= R; r++){
        for(int c = 1; c <= C; c++){
            if(MAP[r][c] > 0){
                int save = MAP[r][c];

                for(int dir = 1; dir <= 4; dir++){
                    int nr, nc;

                    nr = r + dr[dir];
                    nc = c + dc[dir];

                    if(nr <= 0 || nc <= 0 || nr > R || nc > C) continue;
                    if(wall[r][c].direction[dir] == 1) continue;
                    if(MAP[r][c] > MAP[nr][nc]){
                        int diff = (MAP[r][c] - MAP[nr][nc]) / 4;
                        save -= diff;
                        tmpMAP[nr][nc] += diff;
                    }
                }

                tmpMAP[r][c] += save;
            }
        }
    }

    for(int r= 1; r <= R; r++){
        for(int c = 1; c <= C; c++){
            MAP[r][c] = tmpMAP[r][c];
        }
    }
}

void decreaseTemperature(){
	if (MAP[1][1]) MAP[1][1]--;
	if (MAP[R][1]) MAP[R][1]--;
	if (MAP[1][C]) MAP[1][C]--;
	if (MAP[R][C]) MAP[R][C]--;

	for (int r = 2; r <= R - 1; r++)
		if (MAP[r][1]) MAP[r][1]--;

	for (int r = 2; r <= R - 1; r++)
		if (MAP[r][C]) MAP[r][C]--;

	for (int c = 2; c <= C - 1; c++)
		if (MAP[1][c]) MAP[1][c]--;

	for (int c = 2; c <= C - 1; c++)
		if (MAP[R][c]) MAP[R][c]--;
}

int testCheckPoint(){
    for(int i = 0; i < ccnt; i++){
        if(MAP[checkPoint[i].r][checkPoint[i].c] < K) return 0;
    }
    return 1;
}

int main(){

    input();
    
    int chocolate = 0;

    while(1){
        for(int i = 0; i < hcnt; i++){
            int r, c, dir;

            r = heater[i].r;
            c = heater[i].c;
            dir = heater[i].dir;

            heat(r + dr[dir], c + dc[dir], dir);
        }

        controlTemperature();

        chocolate++;

        if(testCheckPoint()) break;
        if(chocolate > 100)break;
    }

    cout<<chocolate<<"\n";

    return 0;
}