#include <iostream>

using namespace std;

#define MAX (15 + 5)

int T, N, W, H;
int MAP[MAX][MAX];
int MINANS;

void input(){
    cin >> N >> W>> H;

    for(int r = 0; r <= H + 1; r++){
        for(int c = 0; c <= W + 1; c++){
            MAP[r][c] = -1;
        }
    }

    for(int r = 1; r <= H; r++){
        for(int c = 1; c <= W; c++){
            cin >> MAP[r][c];
        }
    }
}

int count(int map[MAX][MAX]){
    int sum = 0;
    for(int r = 1; r <= H; r++){
        for(int c = 1; c <= W; c++){
            sum += !!map[r][c];
        }
    }

    return sum;
}

int check(int column, int map[MAX][MAX]){
    for(int row = 1; row <= H; row++){
        if(map[row][column]) return row;
    }
    return -1;
}

int dr[] = {0, -1, 0, 1};
int dc[] = {-1, 0, 1, 0};

void crash(int sr, int sc, int map[MAX][MAX]){
    int size = map[sr][sc];

    map[sr][sc] = 0;

    for(int dir = 0; dir < 4; dir++){
        for(int i = 1; i < size; i++){
            int nr, nc;

            nr = sr + dr[dir] * i;
            nc = sc + dc[dir] * i;

            if(MAP[nr][nc] == -1) break;

            if(MAP[nr][nc] > 0 ) crash(nr, nc, map);
        }
    }
}

void move(int map[MAX][MAX]){
    for(int c = 1; c <= W; c++){
        int list[MAX] = {0};
        int lcnt = 0;

        for(int r = H; r >= 1; r--){
            if(map[r][c]){
                list[lcnt++] = map[r][c];
                map[r][c] = 0;
            }
        }

        int sr = H;
        for(int i = 0; i <lcnt; i++){
            map[sr--][c] = list[i];
        }
    }
}

void copy(int dest[MAX][MAX], int src[MAX][MAX]){
    for(int r = 0; r <= H + 1; r++){
        for(int c = 0; c <= W + 1; c++){
            dest[r][c] = src[r][c];
        }
    }
}



void DFS(int L, int map[MAX][MAX]){
    if(L == N){
        int tmp = count(map);
        if(tmp < MINANS) MINANS = tmp;
        return;
    }

    for(int col = 1; col <= W; col++){
        int sr = check(col, map);
        if(sr == -1){
            DFS(L + 1, map);
            continue;
        }

        int tmpMAP[MAX][MAX] = {0};

        copy(tmpMAP, map);
        crash(sr, col, tmpMAP);
        move(tmpMAP);

        DFS(L + 1, tmpMAP);
    }
}

int main(){

    cin >> T;
    for(int tc = 1; tc <= T; tc++){
        input();

        MINANS = 0x7fff0000;

        DFS(0, MAP);

        cout<<"#"<<tc<<" "<<MINANS<<"\n";
    }

    return 0;
}