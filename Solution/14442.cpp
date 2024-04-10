#include <iostream>
#include <string>
#include <queue>

using namespace std;

#define MAX 1000

int N, M, K;
int MAP[MAX][MAX];
bool Visit[MAX][MAX][10];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void Input(){
    cin >> N >> M >> K;
    for(int i = 0; i < N; i++){
        string Inp;
        cin >> Inp;
        for(int j = 0; j < Inp.size(); j++){
            int I_Inp = Inp[j] - '0';
            MAP[i][j] = I_Inp;
        }
    }
}

void Solution(){
    bool Can_Go = false;
    queue<pair<pair<int, int>, pair<int, int>>> Q;
    Q.push({{0, 0},{1, 0}});
    Visit[0][0][0] = true;

    while(Q.empty() == 0){
        int x = Q.front().first.first;
        int y = Q.front().first.second;
        int Cnt = Q.front().second.first;
        int Wall = Q.front().second.second;
        Q.pop();

        if(x == N - 1 && y == M - 1){
            cout << Cnt<<"\n";
            return;
        }

        for(int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx >= 0 && ny >= 0 && nx < N && ny < M){
                if(Visit[nx][ny][Wall] == false){
                    if(MAP[nx][ny] == 0){
                        Visit[nx][ny][Wall] = true;
                        Q.push({{nx, ny},{Cnt + 1, Wall}});
                    }else if(MAP[nx][ny] == 1){
                        if(Wall < K){
                            Visit[nx][ny][Wall + 1] = true;
                            Q.push({{nx, ny},{Cnt + 1, Wall + 1}});
                        }
                    }
                }
            }
        }
    }
    cout << -1 <<"\n";
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