#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

#define MAX 10
#define ISLAND_MAX 6 + 1
#define INF 1000

int N, M, Area_Num, Answer = INF;
int MAP[MAX][MAX];
int Label[MAX][MAX];
int Dist[ISLAND_MAX][ISLAND_MAX];

bool Visit[MAX][MAX];
bool Connect[ISLAND_MAX][ISLAND_MAX];
bool ConnectIsland[ISLAND_MAX];
bool Select[ISLAND_MAX * ISLAND_MAX];

vector<pair<int, int>> V;
vector<pair<int, int>> Area_Pos[MAX + 1];
vector<pair<pair<int, int>, int>> BridgeList;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1 , 0, 0};

void Input(){
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            Dist[i][j] = INF;
        }
    }

    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> MAP[i][j];
            if(MAP[i][j] == 1){
                V.push_back({i, j});
            }
        }
    }
}

void BFS(int a, int b, int Num){
    queue<pair<int,int>> Q;
    Q.push({a, b});
    Visit[a][b] = true;
    Label[a][b] = Num;
    Area_Pos[Num].push_back({a , b});

    while(Q.empty() == 0){
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();

        for(int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx >= 0 && ny >= 0 && nx < N && ny < M){
                if(Visit[nx][ny] == false && MAP[nx][ny] == 1){
                    Visit[nx][ny] = true;
                    Label[nx][ny] = Num;
                    Q.push({nx, ny});
                    Area_Pos[Num].push_back({nx, ny});
                }
            }
        }
    }
}

void MakeLabel(){
    int LabelNum = 1;
    for(int i = 0; i < V.size(); i++){
        int x = V[i].first;
        int y = V[i].second;

        if(Visit[x][y] == false){
            BFS(x, y, LabelNum++);
        }
    }

    Area_Num = LabelNum;
}

int Reverse(int dir){
    if(dir == 0) return 1;
    else if(dir == 1) return 0;
    else if(dir == 2) return 3;
    else if(dir == 3) return 2;
}

void DFS(int x, int y, int dir, int B_Size, int Start, int End){
    int nx = x + dx[dir];
    int ny = y + dy[dir];
    if(nx < 0 || ny < 0 || nx >= N || ny >= M) return;

    if(MAP[nx][ny] == 0) DFS(nx, ny, dir, B_Size + 1, Start, End);
    else if(MAP[nx][ny] == 1){
        if(Label[nx][ny] == End){
            if(B_Size > 1){
                if(Dist[Start][End] > B_Size){
                    Dist[Start][End] = B_Size;
                    Dist[End][Start] = B_Size;
                }
                return;
            }
        }
        else return;
    }
}

void MakeBridge(int Start, int End){
    for(int i = 0; i < Area_Pos[Start].size(); i++){
        int x = Area_Pos[Start][i].first;
        int y = Area_Pos[Start][i].second;

        for(int j = 0; j < 4; j++){
            int nx = x + dx[j];
            int ny = y + dy[j];

            if(nx >= 0 && ny >= 0 && nx < N && ny < M){
                if(MAP[nx][ny] == 0){
                    DFS(x, y, j, 0, Start, End);
                }
            }
        }
    }
}

void FindDistance(){
    for(int i = 1; i < Area_Num; i++){
        for(int j = i + 1; j < Area_Num; j++){
            MakeBridge(i , j);
            if(Dist[i][j] == INF) continue;
            BridgeList.push_back({{i, j}, Dist[i][j]});
        }
    }
}

bool CheckState(){
    memset(Connect, false, sizeof(Connect));
    memset(ConnectIsland, false, sizeof(ConnectIsland));
    for(int i = 0; i < BridgeList.size(); i++){
        if(Select[i] == true){
            int x = BridgeList[i].first.first;
            int y = BridgeList[i].first.second;

            Connect[x][y] = true;
            Connect[y][x] = true;
        }
    }

    queue<int> Q;
    Q.push(1);
    ConnectIsland[1] = true;

    int IslandCnt = 1;
    bool Flag = false;
    while(Q.empty() == 0){
        int Cur = Q.front();
        Q.pop();

        if(IslandCnt == Area_Num - 1){
            Flag = true;
            break;
        }

        for(int i = 1; i < Area_Num; i++){
            if(Cur == i) continue;
            if(Connect[Cur][i] == true && ConnectIsland[i] == false){
                ConnectIsland[i] = true;
                Q.push(i);
                IslandCnt++;
            }
        }
    }

    return Flag;
}

void DistDFS(int Idx, int Cnt, int Sum){
    if(Cnt >= 1){
        if(CheckState() == true){
            if(Answer > Sum) Answer = Sum;
        }
    }

    for(int i = Idx; i < BridgeList.size(); i++){
        if(Select[i] = true) continue;
        DistDFS(i, Cnt + 1, Sum + BridgeList[i].second);
        Select[i] = false;
    }
}

void Solution(){
    MakeLabel();
    FindDistance();
    DistDFS(0, 0, 0);

    if(Answer == INF) cout << -1 <<"\n";
    else cout << Answer <<"\n";
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