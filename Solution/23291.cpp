#include <iostream>

using namespace std;

#define MAX (100 + 10)

int N, K;
int FISH[MAX][MAX];

void input(){
    cin >> N >> K;

    for(int i = 1; i <= N; i++){
        int f;

        cin >> f;
        FISH[N][i] = f;
    }
}

void addFish(){
    int min = 0x7fff0000;
    for(int r = 1; r <= N; r++){
        for(int c = 1; c <= N; c++){
            if(FISH[r][c] == 0) continue;
            if(FISH[r][c] < min) min = FISH[r][c];
        }
    }

    for(int r = 1; r <= N; r++){
        for(int c = 1; c <= N; c++){
            if(FISH[r][c] == min) FISH[r][c]++;
        }
    }
}

void move(){
    int start, width, height;

    start = width = height = 1;

    int i = 0;
    while(1){
        if(start + width + height - 1 > N) break;

        for(int c = start; c < start + width; c++){
            for(int r = N; r > N - height; r--){
                int nr, nc;

                nr = N - width + c - start;
                nc = start + width + N -r;

                FISH[nr][nc] = FISH[r][c];
                FISH[r][c] = 0;
            }
        }

        if(i % 2)width++;
        else height++;

        start += (i / 2 + 1);
        i++;
    }
}

int dr[] = {0, 0, 0, -1, 1};
int dc[] = {0, 1, -1, 0, 0};

void spreadFish(){
    int tmpFISH[MAX][MAX] = {0};
    for(int r = 1; r <= N; r++){
        for(int c = 1; c <= N; c++){
            if(FISH[r][c] > 0){
                int save = FISH[r][c];

                for(int dir = 1; dir <= 4; dir++){
                    int nr, nc;

                    nr = r + dr[dir];
                    nc = c + dc[dir];

                    if(FISH[nr][nc] == 0) continue;

                    if(FISH[r][c] > FISH[nr][nc]){
                        int diff = (FISH[r][c] - FISH[nr][nc]) / 5;

                        save -= diff;
                        tmpFISH[nr][nc] += diff;
                    }
                }

                tmpFISH[r][c] += save;
            }
        }
    }

    for(int r = 1; r <= N; r++){
        for(int c = 1; c <= N; c++){
            FISH[r][c] = tmpFISH[r][c];
        }
    }
}

void fishSort(){
    int idx;
    int tmpFISH[MAX][MAX] = {0};

    idx = 1;

    for(int c = 1; c <= N; c++){
        if(FISH[N][c] == 0) continue;

        int row = N;
        while(1){
            if(FISH[row][c] == 0) break;

            tmpFISH[N][idx++] = FISH[row][c];
            row--;
        }
    }

    for(int r = 1; r <= N; r++){
        for(int c = 1; c <= N; c++){
            FISH[r][c] = tmpFISH[r][c];
        }
    }
}

void fold(){
    int sc = N / 2 + 1;
    for(int c = N / 2; c >= 1; c--) FISH[N - 1][sc++] = FISH[N][c];
    for(int c = N / 2; c >= 1; c--) FISH[N][c] = 0;

    for(int r = N - 1; r <= N; r++){
        int ec = N / 4 * 3;
        int fix = N;
        for(int c = N / 2 + 1; c <= ec; c++){
            int nr, nc;

            nr = 2 * N - r - 3;
            nc = fix--;

            FISH[nr][nc] = FISH[r][c];
            FISH[r][c] = 0;
        }
    }
}

int check(){
    int max = 0;
    int min = 0x7fff0000;
    for(int r = 1; r <= N; r++){
        for(int c = 1; c <= N; c++){
            if(FISH[r][c] == 0) continue;
            if(FISH[r][c] < min) min = FISH[r][c];
            if(FISH[r][c] > max) max = FISH[r][c];

        }
    }

    if(max - min <= K) return 1;
    return 0;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    input();

    int count = 0;

    while(1){
        addFish();
        move();
        spreadFish();
        fishSort();
        fold();
        spreadFish();
        fishSort();
        count++;
    }

    cout<<count<<"\n";

    return 0;
}