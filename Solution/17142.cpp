#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

#define MAX 50

using namespace std;

int N, M, Empty_Place, Answer = 987654321;
int MAP[MAX][MAX];
int Time[MAX][MAX];
bool Select[10];

vector<pair<int,int>> Virus;

int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1 ,0};

int Min(int A, int B){if (A < B) return A; return B;}


void Input(){
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> MAP[i][j];
            if(MAP[i][j] == 0) Empty_Place++;
            else if(MAP[i][j] == 2) Virus.push_back(make_pair(i, j));
        }
    }
}

void Spread_Virus(queue<pair<int,int>> Q){
    int Infect_Place = 0;
    int Total_Time = 0;
    while(Q.empty() == 0){
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();

        for(int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < N && ny < N){
                if(MAP[nx][ny] != 1 && Time[nx][ny] == -1){
                    Time[nx][ny] = Time[x][y] + 1;
                    if(MAP[nx][ny] == 0){
                        Infect_Place++;
                        Total_Time = Time[nx][ny];
                    }
                    Q.push({nx,ny});
                }
            }
        }
    }

    if (Infect_Place == Empty_Place){
        Answer = Min(Answer, Total_Time);
    }
}

void Select_Virus(int Idx, int Cnt){
    if (Cnt == M){
        queue<pair<int,int>> Q;
        memset(Time, -1, sizeof(Time));
        for(int i = 0; i < Virus.size(); i++){
            if(Select[i] == true){
                Q.push({Virus[i].first, Virus[i].second});
                Time[Virus[i].first][Virus[i].second] = 0;
            }
        }

        Spread_Virus(Q);
        return;
    }

    for(int i = Idx; i < Virus.size(); i++){
        if(Select[i] == true) continue;
        Select[i] = true;
        Select_Virus(i + 1, Cnt + 1);
        Select[i] = false;
    }
}

void Solution(){
    Select_Virus(0, 0);
    if(Answer == 987654321) cout<< -1 <<"\n";
    else cout<< Answer <<"\n";
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