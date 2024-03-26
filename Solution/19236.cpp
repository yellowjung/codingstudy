#include <iostream>
#include <algorithm>
#include <queue>

#define MAX 4

using namespace std;

struct FISH{
    int x;
    int y;
    int Dir;
    bool Live;
};

int Answer;
int MAP[MAX][MAX];
FISH Fish[20];

int dx[] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
int dy[] = {0, 0, -1, -1 ,-1 ,0, 1, 1, 1};

int Max(int A, int B) {if (A > B) return A; return B;}

void Input(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            int a, b;
            cin >> a >> b;
            MAP[i][j] = a;
            Fish[a] = { i ,j ,b, true};
        }
    }
}

void Copy_State(int A[][4], int B[][4], FISH C[], FISH D[]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            A[i][j] = B[i][j];
        }
    }

    for(int i = 1; i <= 16; i++){
        C[i] = D[i];
    }
}

void Swap_Fish(int Idx, int IIdx){
    FISH temp = Fish[Idx];
    Fish[Idx].x = Fish[IIdx].x;
    Fish[Idx].y = Fish[IIdx].y;
    Fish[IIdx].x = temp.x;
    Fish[IIdx].x = temp.x;
}

void Move_Fish(){
    for(int i = 1; i <= 16; i++){

        if(Fish[i].Live == false) continue;

        int x = Fish[i].x;
        int y = Fish[i].y;
        int Dir = Fish[i].Dir;

        int nx = x + dx[Dir];
        int ny = y + dy[Dir];
        bool Flag = false;

        if(nx >= 0 && ny >= 0 && nx < 4 && ny < 4){
            if(MAP[nx][ny] == 0){
                Flag = true;
                Fish[i].x = nx;
                Fish[i].y = ny;
                MAP[nx][ny] = i;
                MAP[x][y] = 0;
            }else if(MAP[nx][ny] != -1){
                Flag = true;
                Swap_Fish(i, MAP[nx][ny]);
                swap(MAP[x][y], MAP[nx][ny]);
            }
        }

        if(Flag == false){
            int nDir = Dir + 1;
            if(nDir == 9) nDir = 1;
            int nx = x + dx[nDir];
            int ny = y + dy[nDir];

            while(nDir != Dir){
                if(nx >= 0 && ny >= 0 && nx < 4 && ny < 4){
                    if(MAP[nx][ny] == 0){
                        Fish[i].x = nx;
                        Fish[i].y = ny;
                        MAP[nx][ny] = i;
                        MAP[x][y] = 0;
                        Fish[i].Dir = nDir;
                        break;
                    }else if(MAP[nx][ny] != -1){
                        Swap_Fish(i, MAP[nx][ny]);
                        swap(MAP[x][y], MAP[nx][ny]);
                        Fish[i].Dir = nDir;
                        break;
                    }
                }
                nDir++;
                if(nDir == 9) nDir = 1;
                nx = x + dx[nDir];
                ny = y + dy[nDir];
            }
        }
    }
}

void Make_State(int x, int y, int nx, int ny, int Fish_Num, bool T){
    if(T == true){
        MAP[x][y] = 0;
        MAP[nx][ny] = -1;
        Fish[Fish_Num].Live = false;
    }else{
        MAP[x][y] = -1;
        MAP[nx][ny] = Fish_Num;
        Fish[Fish_Num].Live = true;
    }
}

void DFS(int x, int y, int Dir, int Sum){
    Answer = Max(Answer, Sum);

    int C_MAP[4][4];
    FISH C_Fish[20];
    Copy_State(C_MAP, MAP, C_Fish, Fish);

    Move_Fish();

    for(int i = 1; i <= 3; i++){
        int nx = x + dx[Dir] * i;
        int ny = y + dy[Dir] * i;
        if(nx >= 0 && ny >= 0 && nx < 4 && ny < 4){
            if(MAP[nx][ny] == 0) continue;

            int Fish_Num = MAP[nx][ny];
            int nDir = Fish[Fish_Num].Dir;

            Make_State(x, y, nx, ny, Fish_Num, true);
            DFS(nx, ny , nDir, Sum + Fish_Num);
            Make_State(nx, ny, x, y, Fish_Num, false);
        }else{
            break;
        }
    }

    Copy_State(MAP, C_MAP, Fish, C_Fish);
}

void Solution(){
    int F_Num = MAP[0][0];
    int Dir = Fish[F_Num].Dir;
    Fish[F_Num].Live = false;
    MAP[0][0] = -1;

    DFS(0, 0, Dir, F_Num);
    cout<< Answer <<"\n";

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