#include <iostream>

using namespace std;

#define MAX (50 + 5)

int N, M;
int MAP[MAX][MAX];

int dr[] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
int dc[] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
int drr[] = {-1, -1, 1, 1};
int dcc[] = {-1, 1, 1, -1};
typedef struct st{
    int r;
    int c;
}RC;

RC cloud[MAX * MAX] = { 0 };
int ccnt;

void input(){
    cin >> N >> M;

    for(int r = 1; r <= N; r++){
        for(int c = 1; c <= N; c++){
            cin >> MAP[r][c];
        }
    }

    cloud[0].r = N; cloud[0].c = 1;
    cloud[1].r = N; cloud[1].c = 2;
    cloud[2].r = N - 1; cloud[2].c = 1;
    cloud[3].r = N - 1; cloud[3].c = 2;
    ccnt = 4;
}

void moveCloud(int dir, int size){
    for(int i = 0; i < ccnt; i++){
        for(int s = 0; s < size; s++){
            int nr, nc;

            nr = cloud[i].r + dr[dir];
            nc = cloud[i].c + dc[dir];

            if(nr == N + 1) nr = 1;
            if(nr == 0) nr = N;
            if(nc == N + 1) nc = 1;
            if(nc == 0) nc = N;

            cloud[i].r = nr;
            cloud[i].c = nc;
        }
    }
}

void addWater(){
    for(int i = 0; i < ccnt; i++){
        MAP[cloud[i].r][cloud[i].c]++;
    }
}

void copyWater(){
    for(int i = 0; i < ccnt; i++){
        int countCloud = 0;
        for(int dir = 0; dir < 4; dir++){
            int nr, nc;
            
            nr = cloud[i].r + drr[dir];
            nc = cloud[i].c + dcc[dir];

            countCloud += !!MAP[nr][nc];
        }

        MAP[cloud[i].r][cloud[i].c] += countCloud;
    }
}

int checkCloud(int r, int c){
    for(int i  = 0; i < ccnt; i++){
        if(cloud[i].r == r && cloud[i].c == c) return 1;
    }

    return 0;
}

void makeCloud(){
    RC newCloud[MAX * MAX] = { 0 };
    int ncnt = 0;

    for(int r = 1; r <= N; r++){
        for(int c = 1; c <= N; c++){
            if(MAP[r][c] < 2) continue;

            if(checkCloud(r, c)) continue;

            MAP[r][c] -= 2;

            newCloud[ncnt].r = r;
            newCloud[ncnt++].c = c;
        }
    }

    for(int i = 0; i < ncnt; i++){
        cloud[i] = newCloud[i];
    }

    ccnt = ncnt;

}

int main(){
    input();

    for(int i = 0; i < M; i++){
        int d, s;

        cin >> d >> s;

        moveCloud(d, s);
        addWater();
        copyWater();
        makeCloud();
    }

    int sum = 0;
    for(int r = 1; r <= N; r++){
        for(int c = 1; c <= N; c++){
            sum += MAP[r][c];
        }
    }

    cout<<sum<<"\n";
    return 0;
}