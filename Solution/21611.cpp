#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define MAX 55
using namespace std;

struct COORD{
    int x;
    int y;
};

int N, M, Answer, Marble[4];
int MAP[MAX][MAX];
int N_MAP[MAX][MAX];
bool Delete[MAX * MAX];
COORD Shark;
COORD Coord[MAX * MAX];
vector<pair<int,int>> Cmd;

int dx[] = {0, -1, 1, 0, 0};
int dy[] = {0, 0, 0, -1, 1};

void input(){
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> MAP[i][j];
        }
    }
    for(int i = 0; i < M; i++){
        int a, b;
        cin >> a >> b;
        Cmd.push_back({a,b});
    }
}

int Change_Dir(int Dir){
    if(Dir == 1) return 3;
    if(Dir == 2) return 4;
    if(Dir == 3) return 2;
    if(Dir == 4) return 1;
}

void Make_MAP(){
    int x = N / 2;
    int y = N / 2;
    int Move_Cnt = 1;
    int Num = 0;
    int Dir = 3;

    Shark = {x,y};
    N_MAP[x][y] = Num;
    Coord[Num++] = {x, y};
    while(1){
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < Move_Cnt; j++){
                x += dx[Dir];
                y += dy[Dir];
                N_MAP[x][y] = Num;
                Coord[Num++] = {x,y};
            }
            Dir = Change_Dir(Dir);
        }
        Move_Cnt++;

        if(Move_Cnt == N){
            for(int j = 0; j < Move_Cnt; j++){
                x += dx[Dir];
                y += dy[Dir];
                N_MAP[x][y] = Num;
                Coord[Num++] = {x, y};
            }
            break;
        }
    }
}

void Blizzard_Magic(int Idx){
    memset(Delete, false, sizeof(Delete));
    int Dir = Cmd[Idx].first;
    int K = Cmd[Idx].second;

    int x = Shark.x;
    int y = Shark.y;
    for(int i = 0; i < K; i++){
        x += dx[Dir];
        y += dy[Dir];
        Delete[N_MAP[x][y]] = true;
    }
}

void Move_Marble(){
    bool Flag = false;
    int Cnt = 0;
    for(int i = 1; i < N*N; i++){
        if(Delete[i] == true){
            Flag = true;
            Cnt++;
        }else{
            if(MAP[Coord[i].x][Coord[i].y] == 0){
                for(int j = 1; j <= Cnt; j++){
                    MAP[Coord[i - j].x][Coord[i - j].y] = 0;
                }
                Flag = false;
                break;
            }
            else{
                MAP[Coord[i - Cnt].x][Coord[i - Cnt].y] = MAP[Coord[i].x][Coord[i].y];
            }
        }
    }
    if(Flag == true){
        int i = (N * N) -1;
        for(int j = 0; j < Cnt; j++, i--){
            MAP[Coord[i].x][Coord[i].y] = 0;
        }
    }
}

bool Destory_Sequence_Marble(){
    memset(Delete, false, sizeof(Delete));

    bool Flag = false;
    int Cur_Marble = MAP[Coord[1].x][Coord[1].y];
    int Sequence_Cnt = 1;
    int Start_Num = 1;
    int Num;

    for(int Num = 2; Num < N * N; Num++){
        int Next_Marble = MAP[Coord[Num].x][Coord[Num].y];
        if(Next_Marble == 0)break;

        if(Cur_Marble == Next_Marble) Sequence_Cnt++;
        else{
            if(Sequence_Cnt >= 4){
                Flag = true;
                for(int i = Start_Num; i < Num; i++){
                    Delete[i] = true;
                }
                Marble[Cur_Marble] += Sequence_Cnt;
            }

            Cur_Marble = Next_Marble;
            Sequence_Cnt = 1;
            Start_Num = Num;
        }
    }

    if(Sequence_Cnt >= 4){
        Flag = true;
        for(int i = Start_Num; i < Num; i++){
            Delete[i] = true;
        }
        Marble[Cur_Marble] += Sequence_Cnt;
    }
    return Flag;
}

void Remake_MAP(){
    int New_MAP[MAX][MAX] = {0, };
    int Cur_Marble = MAP[Coord[1].x][Coord[1].y];
    int Cnt = 1;
    int Pos_Num = 1;
    bool Flag = true;

    for(int Num = 2; Num < N * N; Num++){
        if(Pos_Num >= N * N){
            Flag = false;
            break;
        }

        int Next_Marble = MAP[Coord[Num].x][Coord[Num].y];
        if(Next_Marble == 0) break;
        if(Cur_Marble == Next_Marble){
            Cnt++;
        }else{
            New_MAP[Coord[Pos_Num].x][Coord[Pos_Num].y] = Cnt;
            New_MAP[Coord[Pos_Num + 1].x][Coord[Pos_Num + 1].y] = Cur_Marble;
            Cur_Marble = Next_Marble;
            Cnt = 1;
            Pos_Num += 2;
        }
    }

    if(Flag == true){
        if(Pos_Num != 1){
            New_MAP[Coord[Pos_Num].x][Coord[Pos_Num].y] = Cnt;
            New_MAP[Coord[Pos_Num + 1].x][Coord[Pos_Num + 1].y] = Cur_Marble;
        }
    }

    for(int i = 0; i < N; i++){
        for(int j = 0 ; j < N; j++){
            MAP[i][j] = New_MAP[i][j];
        }
    }
}

void Solution(){
    Make_MAP();
    for(int i = 0; i < M; i++){
        Blizzard_Magic(i);
        Move_Marble();

        while(1){
            if(Destory_Sequence_Marble() == false)break;
            Move_Marble();
        }
        Remake_MAP();
    }
    Answer = Marble[1] + (2 * Marble[2]) + (3 * Marble[3]);
    cout << Answer <<"\n";
}

void Solve(){
    input();
    Solution();
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Solve();

    return 0;
}