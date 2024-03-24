#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_T 25
#define MAX_N 4
#define DIR_NUM 8
#define P_DIR_NUM 4
#define MAX_DECAY 2

int n = 4;
int m, t;

int px, py;

int monster[MAX_T + 1][MAX_N][MAX_N][DIR_NUM];

int dead[MAX_N][MAX_N][MAX_DECAY + 1];

int dx[DIR_NUM] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[DIR_NUM] = {0, -1, -1, -1, 0, 1, 1, 1};

int p_dx[P_DIR_NUM] = {-1, 0, 1, 0};
int p_dy[P_DIR_NUM] = {0, -1, 0, 1};

int t_num = 1;

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool CanGo(int x, int y){
    return InRange(x , y) && dead[x][y][0] == 0 && dead[x][y][1] == 0 
        && make_pair(x, y) != make_pair(px, py);
}

void DoKill(tuple<int, int, int> best_route){
    int dir1, dir2, dir3;
    tie(dir1, dir2, dir3) = best_route;

    int dirs[] = {dir1, dir2, dir3};
    for(int i = 0; i < 3; i ++){
        int nx = px + p_dx[dirs[i]], ny = py + p_dx[dirs[i]];

        for(int j = 0; j < DIR_NUM; j++){
            dead[nx][ny][MAX_DECAY] += monster[t_num][nx][ny][j];
            monster[t_num][nx][ny][j] = 0;
        }

        px = nx ; py = py;
    }
}

void MoveP(){
    int max_cnt = -1;
    tuple<int, int, int> best_route;

    for(int i = 0; i < P_DIR_NUM; i++){
        for(int j = 0; j < P_DIR_NUM; j++){
            for(int k = 0; k < P_DIR_NUM; k++){
                int m_cnt = GetKilledNum(i, j, k);

                if(m_cnt > max_cnt){
                    max_cnt = m_cnt;
                    best_route = make_tuple(i, j, k);
                }
            }
        }
    }

    Dokill(best_route);
}

void DecayM(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < MAX_DECAY; k++){
                dead[i][j][k] = dead[i][j][k + 1];
            }
            dead[i][j][MAX_DECAY] = 0;
        }
    }
}

void AddM(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < DIR_NUM; k++){
                monster[t_num][i][j][k] += monster[t_num - 1][i][j][k];
            }
        }
    }
}

void Simulate(){

    MoveM();

    MoveP();

    DecayM();

    AddM();
}

int CountMonster(){
    int cnt = 0;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cnt += monster[t][i][j][k];
        }
    }
    return cnt;
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> m >> t;
    cin >> px >> py;

    px--; py--;

    for(int i = 0; i < m; i++){
        int mx, my, mdir;
        cin >> mx >> my >> mdir;

        monster[0][mx - 1][my - 1][mdir - 1]++;
    }

    while(t_num <= t){
        Simulate();
        t_num++;
    }

    cout << CountMonster();

    return 0;
}