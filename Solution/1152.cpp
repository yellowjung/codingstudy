#include <iostream>

using namespace std;

#define MAX (64 + 5)

int N, Q, MAP_SIZE;
int A[MAX][MAX];
int tmpA[MAX][MAX];

typedef struct st{
    int r;
    int c;
}QUEUE;

QUEUE queue[MAX * MAX];
int wp, rp;

void input(){
    cin >> N >> Q;

    MAP_SIZE = 1 << N;

    for(int r = 1; r <= MAP_SIZE; r++){
        for(int c = 1; c <= MAP_SIZE; c++){
            cin >> A[r][c];
        }
    }
}

void rotate(int map[MAX][MAX], int sr, int sc, int size){
    for(int r = 0; r < size; r++){
        for(int c = 0; c < size; c++){
            tmpA[r][c] = map[sr + size - 1 - c][sc + r];
        }
    }

    for(int r = 0; r < size; r++){
        for(int c = 0; c < size; c++){
            map[sr + r][sc + c] = tmpA[r][c];
        }
    }
}

int dr[] = {0, -1, 0, 1};
int dc[] = {-1, 0, 1, 0};

void meltIce(){
    int ICE[MAX][MAX] = { 0, };

    for(int r = 1; r <= MAP_SIZE; r++){
        for(int c = 1; c <= MAP_SIZE; c++){
            if(A[r][c] == 0) continue;

            int cnt = 0;

            for(int i = 0; i < 4; i++){
                int nr, nc;

                nr = r + dr[i];
                nc = c + dc[i];

                cnt += !A[nr][nc];
            }

            if(cnt >= 2) ICE[r][c] = 1;
        }
    }

    for(int r = 1 ; r <= MAP_SIZE; r++){
        for(int c = 1; c <= MAP_SIZE; c++){
            A[r][c] -= ICE[r][c];
        }
    }
}

int BFS(int r, int c, int visit[MAX][MAX]){
    int cnt;

    wp = rp = 0;

    cnt = 1;

    queue[wp].r = r;
    queue[wp++].c = c;

    visit[r][c] = 1;


    while(wp > rp){
        QUEUE out = queue[rp++];

        for(int i = 0; i < 4; i++){
            int nr = out.r + dr[i];
            int nc = out.c + dc[i];

            if(visit[nr][nc] == 0 && A[nr][nc] != 0){
                queue[wp].r = nr;
                queue[wp++].c = nc;

                visit[nr][nc] = 1;
                cnt++;
            }
        }
    }
    return cnt++;
}

int findBigIce(){
    int visit[MAX][MAX] = { 0 ,};

    int max = 0;
    
    for(int r = 1; r <= MAP_SIZE; r++){
        for(int c = 1; c <= MAP_SIZE; c++){
            if(A[r][c] == 0 || visit[r][c] == 1) continue;

            int tmp = BFS(r, c, visit);
            if(max < tmp) max = tmp;
        }
    }

    return max;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    input();

    for(int q = 0; q< Q; q++){
        int L;
        cin >> L;
        
        int divide = 1 << L;

        for(int r = 1; r <= MAP_SIZE; r += divide){
            for(int c = 1; c <= MAP_SIZE; c += divide){
                rotate(A, r, c, divide);
            }
        }

        meltIce();
    }

    int sum = 0;
    for(int r = 1; r <= MAP_SIZE; r++){
        for(int c = 1; c <= MAP_SIZE; c++){
            sum += A[r][c];
        }
    }

    cout<<sum<<"\n"<<findBigIce()<<"\n";

    return 0;
}