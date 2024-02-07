#include <iostream>
#include <vector>
using namespace std;

#define MAX 55

struct FIREBALL{
    int x;
    int y;
    int Massive;
    int Speed;
    int Dir;
};

int dx[] = {-1 ,-1 , 0, 1, 1, 1, 0, -1};
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
int T_Dir[] = {0, 2, 4, 6};
int F_Dir[] = {1, 3, 5, 7};

int N, M, K;
vector<FIREBALL> MAP[MAX][MAX];
vector<FIREBALL> FireBall;

void Input(){
    int Num = 0;
    cin >> N >> M >> K;
    for(int i = 0; i < M; i++){
        int r, c, m, s, d;
        cin >> r >> c >> m >> s >> d;
        FireBall.push_back({r, c, m, s, d});
        MAP[r][c].push_back({r, c, m, s, d});
    }
    
}

void Move_FireBall(){
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            MAP[i][j].clear();
        }
    }

    for(int i = 0; i < FireBall.size(); i++){
        int x = FireBall[i].x;
        int y = FireBall[i].y;
        int Mass = FireBall[i].Massive;
        int Speed = FireBall[i].Speed;
        int Dir = FireBall[i].Dir;

        int Move = Speed % N;
        int nx = x + dx[Dir] * Move;
        int ny = y + dy[Dir] * Move;
        if(nx > N) nx -= N;
        if(ny > N) ny -= N;
        if(nx < 1) nx += N;
        if(ny < 1) ny += N;
        MAP[nx][ny].push_back({nx, ny, Mass, Speed, Dir});
        FireBall[i].x = nx;
        FireBall[i].y = ny;
    }
}

void Sum_FireBall(){
    vector<FIREBALL> Temp;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            if(MAP[i][j].size() == 0) continue;
            if(MAP[i][j].size() == 1){
                Temp.push_back(MAP[i][j][0]);
                continue;
            }

            int Massive_Sum = 0;
            int Speed_Sum = 0;
            int Cnt = MAP[i][j].size();

            bool Even = true;
            bool Odd = true;
            for(int k = 0; k < MAP[i][j].size(); k++){
                Massive_Sum += MAP[i][j][k].Massive;
                Speed_Sum += MAP[i][j][k].Speed;
                if(MAP[i][j][k].Dir % 2 == 0) Odd = false;
                else Even = false;
            }

            int Mass = Massive_Sum / 5;
            int Speed = Speed_Sum / Cnt;
            if(Mass == 0) continue;
            if(Even == true || Odd == true){
                for(int k = 0; k < 4; k++){
                    Temp.push_back({i, j, Mass, Speed, T_Dir[k]});
                }
            }else{
                for(int k = 0; k < 4; k++){
                    Temp.push_back({i, j, Mass, Speed, F_Dir[k]});
                }
            }

        }
    }
    FireBall = Temp;
}

void Solution(){
    for(int i = 0; i < K; i++){
        Move_FireBall();
        Sum_FireBall();
    }

    int Answer = 0;
    for(int i = 0; i < FireBall.size(); i++){
        Answer += FireBall[i].Massive;
    }

    cout << Answer <<"\n";
}

void Solve(){
    Input();
    Solution();
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Solve();

    return 0;
}