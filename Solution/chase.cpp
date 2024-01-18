#include <iostream>
#include <vector>
#define MAX 100

using namespace std;

struct Info{
    int x, y, dir;
};

Info sullae;

bool namu[MAX][MAX] = {0, };
vector<int> runnerMap[MAX][MAX];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int N, M, H, K;
bool opposite = false;
int len, cnt;

int curLen = 1;

void input(){
    curLen = 1;
    len = 0;
    cnt = 0;

    cin >> N >> M >> H >> K;
    sullae = { (N - 1) / 2 , (N - 1) / 2, 0};

    for(int i = 0; i < M; i++){
        int x, y, d;
        cin >> x >> y >> d;
        runnerMap[x - 1][y - 1].push_back(d);
    }

    for(int i = 0; i < H; i++){
        int x, y;
        cin >> x >> y;
        namu[x - 1][y - 1] = 1;
    }
}

void moveRunner(){
    vector<int> tmpRunnerMap[MAX][MAX];

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < runnerMap[i][j].size(); k++){
                int d = runnerMap[i][j][k];
                int dis = abs(i - sullae.x) + abs(j - sullae.y);
                if(dis > 3){
                    tmpRunnerMap[i][j].push_back(runnerMap[i][j][k]);
                    continue;
                }

                int nx = i + dx[d];
                int ny = j + dy[d];

                if(nx < 0 || ny < 0 || nx >= N || ny >= N){
                    if(d < 2) d += 2;
                    else d -= 2;

                    nx = i + dx[d];
                    ny = j + dy[d];
                }

                if(nx == sullae.x && ny == sullae.y){
                    nx = nx - dx[d];
                    ny = ny - dy[d];
                }

                tmpRunnerMap[nx][ny].push_back(d);
            }
        }
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            runnerMap[i][j].clear();
            runnerMap[i][j] = tmpRunnerMap[i][j];
        }
    }
}

int catchRunner(){
    int x = sullae.x;
    int y = sullae.y;
    int dir = sullae.dir;

    int cnt = 0;
    for(int i = 0; i < 3; i++){
        int nx = x + dx[dir] * i;
        int ny = y + dy[dir] * i;

        if(namu[nx][ny]) continue;
        if(nx < 0 || ny < 0 || nx >= N || ny >= N) break;

        if(runnerMap[nx][ny].size() > 0){
            cnt += runnerMap[nx][ny].size();
            runnerMap[nx][ny].clear();
        }
    }
    return cnt;
}

void moveSullae(){
    int x = sullae.x;
    int y = sullae.y;
    int dir = sullae.dir;

    int nx = x + dx[dir];
    int ny = y + dy[dir];

    len++;

    if(len == curLen){
        len = 0;
        cnt++;
        if(opposite == false){
            if(dir == 3){
                dir = 0;
            }else{
                dir++;
            }
        }else{
            if(dir == 0){
                dir = 3;
            }else{
                dir--;
            }
        }

        if(cnt == 2){
            cnt = 0;
            if(!opposite) curLen++;
            else curLen--;
        }
    }

    if(nx == 0 && ny == 0){
        opposite = true;
        curLen = N - 1;
        dir = 2;
        cnt = -1;
        len = 0;
    }else if(nx == (N - 1) / 2 && ny == (N - 1) / 2){
        opposite = false;
        curLen = 1;
        dir = 0;
        cnt = 0;
        len = 0;
    }

    sullae = {nx, ny, dir};
}

int solve(){
    int score = 0;

    for(int i = 1; i <= K; i++){
        moveRunner();
        moveSullae();
        score += i * catchRunner();
    }

    return score;
}

void solution(){
    input();
    cout << solve() <<"\n";
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solution();

    return 0;
}