#include <iostream>

using namespace std;

#define MAX (100 + 50)

int T, N, M, K;

typedef struct st{
    int dir;
    int num;
    int maxNum;
}BIO;

BIO MAP[MAX][MAX];
BIO nextMAP[MAX][MAX];

int dr[] = {0, -1, 1, 0, 0};
int dc[] = {0, 0, 0, -1, 1};
int changeDir[5] = {0, 2, 1, 4, 3};

void input(){
    cin >> N >> M >> K;

    BIO init = {0};

    for(int r = 0; r < N; r++){
        for(int c = 0; c < N; c++){
            MAP[r][c] = init;
        }
    }

    for(int i = 0; i < K; i++){
        int r, c, num, dir;

        cin >> r >> c >> num >> dir;

        MAP[r][c].num = num;
        MAP[r][c].maxNum = num;
        MAP[r][c].dir = dir;
    }
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> T;

    for(int tc = 1; tc <= T; tc++){
        input();

        for(int m = 0; m < M; m++){
            for(int r = 0; r < N; r++){
                for(int c = 0; c < N; c++){
                    if(MAP[r][c].num == 0) continue;

                    int currentNum = MAP[r][c].num;

                    int nr, nc;

                    nr = r + dr[MAP[r][c].dir];
                    nc = c + dc[MAP[r][c].dir];

                    if(nr == 0 || nc == 0 || nr == N - 1 || nc == N - 1){
                        MAP[r][c].num /= 2;
                        MAP[r][c].dir = changeDir[MAP[r][c].dir];
                    }

                    if(nextMAP[nr][nc].num == 0){
                        nextMAP[nr][nc] = MAP[r][c];
                    }else if(nextMAP[nr][nc].maxNum > currentNum){
                        nextMAP[nr][nc].num += MAP[r][c].num;
                    }else{
                        nextMAP[nr][nc].maxNum = currentNum;
                        nextMAP[nr][nc].dir = MAP[r][c].dir;
                        nextMAP[nr][nc].num += MAP[r][c].num;
                    }
                }
            }

            BIO init = {0 };
            for(int r = 0; r < N; r++){
                for(int c = 0; c < N; c++){
                    MAP[r][c] = nextMAP[r][c];
                    MAP[r][c].maxNum = MAP[r][c].num;
                    nextMAP[r][c] = init;
                }
            }
        }

        int sum = 0;
        for(int r = 0; r < N; r++){
            for(int c = 0; c < N; c++){
                sum += MAP[r][c].num;
            }
        }

        cout<<"#"<<tc<<" "<<sum<<"\n";
    }

    return 0;
}