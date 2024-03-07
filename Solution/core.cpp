#include <iostream>

using namespace std;

#define MAX (10 + 5)

int T, N;
int MAP[MAX][MAX];

typedef struct st{
    int r;
    int c;
}RC;

RC core[MAX * MAX];
int ccnt;

int FLAG, FAIL_COUNT;
int MINANS = 0x7fff0000;

int dr[] = {0, -1, 0, 1};
int dc[] = {-1 ,0, 1, 0};

int countLink(int map[MAX][MAX]){
    int sum = 0;
    for(int r = 1; r <= N; r++){
        for(int c = 1; c <= N; c++){
            if(map[r][c] == 3) sum++;
        }
    }

    return sum;
}

int checkLink(int sr, int sc, int dir, int map[MAX][MAX]){
    if(dir == 4) return 1;

    int nr, nc;

    nr = sr; nc = sc;

    while(1){
        nr += dr[dir];
        nc += dc[dir];

        if(map[nr][nc] == 1 || map[nr][nc] == 3) return 0;
        else if(map[nr][nc] == 2) return 1;
    }

    return -1;
}

void setLink(int sr, int sc, int dir, int map[MAX][MAX]){
    int nr, nc;

    nr = sr; nc = sc;
    while(1){
        nr += dr[dir];
        nc += dc[dir];

        if(map[nr][nc] == 2)return;

        map[nr][nc] = 3;
    }
}

void deleteLink(int sr, int sc, int dir, int map[MAX][MAX]){
    int nr, nc;

    nr = sr; nc = sc;
    while(1){
        nr += dr[dir];
        nc += dc[dir];

        if(map[nr][nc] == 2)return;

        map[nr][nc] = 0;
    }
}

void DFS(int L, int failCount, int map[MAX][MAX]){
    if(failCount > FAIL_COUNT) return;

    if(L == ccnt){
        if(failCount == FAIL_COUNT){
            FLAG = 1;

            int tmp = countLink(map);
            if(MINANS > tmp) MINANS = tmp;
        }

        return;
    }

    int tmpMAP[MAX][MAX] = {0 };

    for(int r = 0; r <= N + 1; r++){
        for(int c = 0; c <= N + 1; c++){
            tmpMAP[r][c] = map[r][c];
        }
    }

    for(int dir = 0; dir < 4; dir++){
        if(checkLink(core[L].r, core[L].c, dir, tmpMAP)){
            setLink(core[L].r, core[L].c, dir, tmpMAP);
            DFS(L + 1, failCount, tmpMAP);
            deleteLink(core[L].r, core[L].c, dir, tmpMAP);
        }
    }

    DFS(L + 1, failCount + 1, tmpMAP);
}

int isBoundary(int r, int c){
    for(int i = 0; i < 4; i++){
        int nr, nc; 

        nr = r + dr[i];
        nc = c + dc[i];

        if(MAP[nr][nc] == 2) return 1;
    }

    return 0;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> T;
    for(int tc = 1; tc <= T; tc++){
        ccnt = FLAG = 0;
        MINANS = 0x7fff0000;

        for(int r = 1; r <= N; r++){
            for(int c = 1; c <= N; c++){
                if(MAP[r][c] == 1 && isBoundary(r, c) == 0){
                    core[ccnt].r = r;
                    core[ccnt++].c =c;
                }
            }
        }

        for(int fail = 0; fail < ccnt; fail++){
            FAIL_COUNT = fail;
            DFS(0, 0, MAP);
            if(FLAG) break;
        }

    }

    return 0;
}