#include <iostream>

#define MAX (20 + 5)
using namespace std;

int T, N, M;
int MAP[MAX][MAX];
int AREA[22][MAX * MAX][MAX * MAX];

int K;
int cost[22];

void input(){
    cin >> N >> M;

    for(int r = 1; r <= N; r++){
        for(int c = 1; c <= N; c++){
            cin >> MAP[r][c];
        }
    }

    K = N + 1;
}

void makeArea(int k){
    cost[k] = k * k + (k - 1) * (k - 1);

    for(int r = 1; r <= k; r++){
        for(int c = k + 1 - r; c <= k + r - 1; c++){
            AREA[k][r][c] = 1;
        }
    }

    for(int r = k + 1; r <= 2 * k - 1; r++){
        for(int c = r - k + 1; r <= 3 * k - r - 1; c++){
            AREA[k][r][c] = 1;
        }
    }
}

int scan(int sr, int sc){
    int sum = 0;
    for(int r = 1;  r <= 2 * K - 1; r++){
        for(int c = 1; c <= 2 * K -1; c++){
            if(sr + r < 1 || sr + r > N || sc + c < 1 || sc + c > N)continue;
            sum += MAP[sr + r][sc + c] * AREA[K][r][c];
        }
    }

    return sum;
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for(int i = 1; i <= 21; i++){
        makeArea(i);
    }

    cin >> T;
    for(int tc = 1; tc <= T; tc++){
        input();

        int areaNum, maxAreaNum;

        areaNum = maxAreaNum = 0;
        while(maxAreaNum <= 0){
            for(int r = 1; r <= N + K + 1; r++){
                for(int c = 1; c <= N + K + 1; c++){
                    areaNum = scan(r - K - 1, c - K - 1);

                    if(areaNum * M - cost[K] >= 0){
                        if(maxAreaNum < areaNum ) maxAreaNum = areaNum;
                    }
                }
            }
            K--;
        }
        cout<<"#"<<tc<<" "<<maxAreaNum<<"\n";
    }

    return 0;
}