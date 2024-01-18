#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAX 25

using namespace std;

int N, M, K;

int MAP[MAX][MAX];
int Lab[MAX][MAX];
int Visit[MAX][MAX];

int dx[4] = {1, -1 ,0 , 0};
int dy[4] = {0, 0, 1, -1};

struct Block{
    int x;
    int y;
};

vector<Block> Team[6];
int Person[6];
int Point[6];

void Input(){
    cin >> N >> M >> K;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            cin >> MAP[i][j];
        }
    }
}


void Label(int x, int y, int L){
    for(int i = 0; i < 4; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx < 1 || ny < 1 || nx > N || ny > N) continue;
        if(Visit[nx][ny] == 1 || MAP[nx][ny] == 0) continue;

        if(Team[L].size() == 1 && MAP[nx][ny] != 2) continue;

        if(MAP[nx][ny] == 3) Person[L] = Team[L].size() + 1;

        Visit[nx][ny] = 1;
        Team[L].push_back({nx, ny});
        Label(nx, ny, L);
    }
}

void MakeTeam(){
    int L = 1;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            if(MAP[i][j] == 1 && Visit[i][j] == 0){
                Visit[i][j] = 1;
                Team[L].push_back({i, j});
                Label(i, j, L);
                L++;
            }
        }
    }

    for(int i = 1; i < L; i++){
        for(int j = 0; j < Team[i].size(); j++){
            Lab[Team[i][j].x][Team[i][j].y] = i;
        }
    }

    memset(Visit, 0, sizeof(Visit));
}

void Rotation(){
    for(int n = 1; n <= M; n++){
        int sz = Team[n].size();
        int tx = Team[n][sz - 1].x;
        int ty = Team[n][sz - 1].y;

        for(int i = sz - 1; i >= 1; i--){
            Team[n][i].x = Team[n][i - 1].x;
            Team[n][i].y = Team[n][i - 1].y;
        }
        Team[n][0].x = tx;
        Team[n][0].y = ty;

        for(int i = 0; i < Team[n].size(); i++){
            if(i == 0){
                MAP[Team[n][i].x][Team[n][i].y] = 1;
            }else if(i > 0 && i < Person[n] - 1){
                MAP[Team[n][i].x][Team[n][i].y] = 2;
            }else if(i == Person[n] - 1){
                MAP[Team[n][i].x][Team[n][i].y] = 3;
            }else{
                MAP[Team[n][i].x][Team[n][i].y] = 4;
            }
        }
    }
}

void State(int L, int x, int y){
    for(int i = 0; i < Team[L].size(); i++){
        if(Team[L][i].x == x && Team[L][i].y == y){
            Point[L] += (i + 1) * (i + 1);
        }
    }

    reverse(Team[L].begin(), Team[L].begin() + Person[L]);
    reverse(Team[L].begin() +  Person[L], Team[L].end());

    for(int i = 0; i < Team[L].size(); i++){
        if(i == 0){
            MAP[Team[L][i].x][Team[L][i].y] = 1;
        }else if(i > 0 && i < Person[L] - 1){
            MAP[Team[L][i].x][Team[L][i].y] = 2;
        }else if(i == Person[L] - 1){
            MAP[Team[L][i].x][Team[L][i].y] = 3;
        }else{
            MAP[Team[L][i].x][Team[L][i].y] = 4;
        }
    }
}

void Ball(int Round){
    int R = Round % (4 * N);
    if(R >= 1 && R <= N){
        for(int i = 1; i <= N; i++){
            if(MAP[R][i] == 0 || MAP[R][i] == 4) continue;
            State(Lab[R][i], R, i);
            break;
        }
    }

    if(R > N && R <= 2 * N){
        for(int i = N; i >= 1; i--){
            if(MAP[i][R - N] == 0 || MAP[i][R - N] == 4) continue;
            State(Lab[i][R - N], i, R - N);
            break;
        }
    }

    if(R > 2 * N && R <= 3 * N){
        for(int i = N; i>= 1; i--){
            if(MAP[3 * N - R + 1][i] == 0 || MAP[3 * N - R + 1][i] == 4) continue;
            State(Lab[3 * N - R + 1][i], 3 * N - R + 1 , i);
            break;
        }
    }
    if(R > 3 * N){
        for(int i = 1; i <= N; i++){
            if(MAP[i][4 * N - R + 1] == 0 || MAP[i][4 * N - R + 1] == 4) continue;
            State(Lab[i][4 * N - R +1], i, 4 * N - R + 1);
            break;
        }
    }

    if(R == 0){
        for(int i = 1; i <= N; i++){
            if(MAP[i][1] == 0 || MAP[i][1] == 4) continue;
            State(Lab[i][1], i, 1);
            break;
        }
    }
}

int Make_Ans(){
    int sum = 0;
    for(int i = 1; i <= M; i++){
        sum += Point[i];
    }
    return sum;
}

void Solution(){
    int Time = 1;
    while( Time <= K){
        Rotation();
        Ball(Time);
        Time++;
    }
    cout<<Make_Ans()<<"\n";
}


void Solve(){
    Input();
    MakeTeam();
    Solution();
}

int main(){
    Solve();
}