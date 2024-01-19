#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define MAX 30

using namespace std;

struct pos{
    int x, y;
};

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int N;
int map[MAX][MAX] = {0, };
int group[MAX][MAX] = {0, };
int touch[MAX * MAX][MAX * MAX] = {0, };

void input(){
    cin >> N;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> map[i][j];
        }
    }
}

void calcTouch(){
    memset(touch, 0, sizeof(touch));

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            int from = group[i][j];
            for(int k = 1; k <= 2; k++){
                int nx = i + dx[k];
                int ny = j + dy[k];

                if(nx < 0 || ny < 0 || nx >= N || ny >= N || group[nx][ny] == from) continue;
                touch[from][group[nx][ny]]++;
            }
        }
    }
}

int calcScore(){
    memset(group, 0, sizeof(group));

    int groupCnt = 1;
    int groupSize[MAX * MAX] = { 0, };
    int groupIdx[MAX * MAX] = {0, };
    queue<pos> q;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(group[i][j] == 0){
                q.push({i, j});
                group[i][j] = groupCnt;
                groupIdx[groupCnt] = map[i][j];
                groupCnt += 1;
            }
            while(!q.empty()){
                int x = q.front().x;
                int y = q.front().y;
                q.pop();

                groupSize[group[x][y]]++;

                for(int k = 0; k < 4; k++){
                    int nx = x + dx[k];
                    int ny = y + dy[k];

                    if(nx < 0 || ny < 0 || nx >= N || ny >= N || group[nx][ny] != 0) continue;
                    if(map[nx][ny] != map[x][y]) continue;

                    q.push({nx, ny});
                    group[nx][ny] = group[x][y];
                }
            }
        }
    }

    calcTouch();
    int score = 0;
    for(int i = 1; i < groupCnt; i++){
        for(int j = i + 1; j <= groupCnt; j++){
            score += (groupSize[i] + groupSize[j]) * (touch[i][j]  + touch[j][i]) * groupIdx[i] * groupIdx[j];
        }
    }
    return score;
}

void rotate(int x, int y){
    int len = (N - 1) / 2;

    int tmp[MAX][MAX] = {0 ,};

    for(int i = 0; i < len; i++){
        for(int j = 0; j < len; j++){
            tmp[j][len - 1 - i] = map[x + i][y + j];
        }
    }

    for(int i = 0; i < len; i++){
        for(int j = 0; j < len; j++){
            map[x + i][y + j] = tmp[i][j];
        }
    }
}

void rotate(){
    int len = (N - 1) / 2 + 1;

    rotate(0, 0);
    rotate(0, len);
    rotate(len, 0);
    rotate(len, len);

    int tmp[MAX] = {0, };
    len -= 1;

    for(int i=0;i<len;i++)  tmp[i] = map[i][len];
    for(int i=0;i<len;i++)  map[i][len] = map[len][N-1-i];
    for(int i=0;i<len;i++)  map[len][N-1-i]= map[N-1-i][len];
    for(int i=0;i<len;i++)  map[N-1-i][len]=map[len][i];
    for(int i=0;i<len;i++)  map[len][i]=tmp[i];
}

void Solve(){
    int score = 0;

    score += calcScore();

    for(int i = 0; i < 3; i++){
        rotate();
        score += calcScore();
    }

    cout<<score<<"\n";
}

void Solution(){
    input();

    Solve();
}

int main(){

    Solution();

    return 0;
}