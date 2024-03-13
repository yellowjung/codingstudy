#include <iostream>

using namespace std;

#define MAX (25 + 5)

int N;
int MAP[MAX][MAX];
int visit[MAX][MAX];

typedef struct st{
    int r;
    int c;
}QUEUE;

QUEUE queue[MAX * MAX];

int ANS[MAX * MAX];
int wp, rp;

int dr[] = {0, -1, 0, 1};
int dc[] = {-1, 0, 1, 0};

void input(){
    cin >> N;
    for(int r = 1; r <= N; r++){
        string tmp;
        cin >> tmp;
        for(int c = 1; c <= N; c++){
            MAP[r][c] = tmp[c - 1] - '0'; 
        }
    }
}

int BFS(int r, int c){
    int cnt = 0;

    wp =  rp = 0;

    cnt = 1;

    queue[wp].r = r;
    queue[wp++].c = c;

    visit[r][c] = 1;

    while(wp > rp){
        QUEUE out = queue[rp++];
    
        for(int i = 0; i < 4; i++){
            int nr = out.r + dr[i];
            int nc = out.c + dc[i];

            if(visit[nr][nc] == 0 && MAP[nr][nc] == 1){
                queue[wp].r = nr;
                queue[wp++].c = nc;

                visit[nr][nc] = 1;
                cnt++;
            }
        }
    }
    return cnt;
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int ans; 

    input();

    ans = 0;

    for(int r = 1; r <= N; r++){
        for(int c = 1; c <= N; c++){
            if(MAP[r][c] == 1 && visit[r][c] == 0) ANS[ans++] = BFS(r, c);
        }
    }

    cout << ans <<"\n";

    for(int i = 0; i < ans - 1; i++){
        for(int k = i + 1; k < ans; k++){
            if(ANS[i] > ANS[k]){
                int tmp = ANS[i];
                ANS[i] = ANS[k];
                ANS[k] = tmp;
            }
        }
    }

    for(int i = 0; i < ans; i++){
        cout<<ANS[i]<<"\n";
    }

    return 0;
}