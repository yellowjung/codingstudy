#include <iostream>

using namespace std;

#define MAX (20 + 5)

int N, M, K;

typedef struct st1{
    int number;
    int current;
    int time;
}INFO;

INFO MAP[MAX][MAX];

typedef struct st2{
    int r;
    int c;
    int dir;
    int priority[5][5];
    int dead;
}SHARK;

SHARK shark[MAX * MAX];

void input(){
    cin >> N >> M >> K;

    for(int r = 0; r <= N + 1; r++){
        for(int c = 0; c <= N + 1; c++){
            MAP[r][c].number = -1;
        }
    }

    for(int r = 1; r <= N; r++){
        for(int c = 1; c <= N; c++){
            MAP[r][c].number = 0;
        }
    }

    for(int r = 1; r <= N; r++){
        for(int c = 1; c <= N; c++){
            int in;

            cin >> in;

            if(in){
                shark[in].r = r;
                shark[in].c = c;
            }
        }
    }

    for(int i = 1; i <= M; i++){
        int dir;
        cin >> dir;
        shark[i].dir = dir;
    }

    for(int i = 1; i <= M; i++){
        for(int d = 1; d <= 4; d++){
            cin >> shark[i].priority[d][1] >> shark[i].priority[d][2] >> shark[i].priority[d][3] >> shark[i].priority[d][4];
        }
    }
}

int dr[] = {0, -1, 1, 0, 0};
int dc[] = {0, 0, 0, -1, 1};

int findDirection(SHARK shark, int number){
    int currentDir = shark.dir;

    for(int d = 1; d <= 4; d++){
        int nr, nc, nextDir;

        nextDir = shark.priority[currentDir][d];
        nr = shark.r + dr[nextDir];
        nc = shark.c + dc[nextDir];

        if(MAP[nr][nc].number == -1)continue;;
        if(MAP[nr][nc].time == 0) return nextDir;
    }

    for(int d = 1; d <= 4; d++){
        int nr, nc, nextDir;

        nextDir = shark.priority[currentDir][d];
        nr = shark.r + dr[nextDir];
        nc = shark.c + dc[nextDir];

        if(MAP[nr][nc].number == number) return nextDir;
    }

    cout<<"Impossible case\n";
    return -1;
}

int simulate(){
    int sharkCount = M;
    for(int t = 1; t <= 1000; t++){
        for(int s = 1; s <= M; s++){
            if(shark[s].dead) continue;

            MAP[shark[s].r][shark[s].c].number = s;
            MAP[shark[s].r][shark[s].c].time = K;
        }

        for(int s = 1; s <= M; s++){
            if(shark[s].dead) continue;

            int nr, nc, dir;

            dir = findDirection(shark[s], s);

            nr = shark[s].r + dr[dir];
            nc = shark[s].c + dc[dir];

            if(MAP[nr][nc].current){
                int alreadySharkNumber = MAP[nr][nc].current;

                sharkCount--;

                if(alreadySharkNumber < s) shark[s].dead = 1;
                else{
                    shark[alreadySharkNumber].dead = 1;

                    shark[s].r = nr;
                    shark[s].c = nc;
                    shark[s].dir = dir;

                    MAP[nr][nc].current = s;
                    MAP[nr][nc].number = s;
                }
            }else{
                shark[s].r = nr;
                shark[s].c = nc;
                shark[s].dir = dir;

                MAP[nr][nc].current = s;
                MAP[nr][nc].number =s;
            }
        }

        for(int s = 1; s <= M; s++){
            MAP[shark[s].r][shark[s].c].current = 0;
        }

        if(sharkCount == 1) return t;

        for(int r = 1; r <= N; r++){
            for(int c = 1; c <= N; c++){
                if(MAP[r][c].time) MAP[r][c].time--;
            }
        }
    }
    return -1;
}

int main(){
    input();

    cout << simulate() <<"\n";

    return 0;
}