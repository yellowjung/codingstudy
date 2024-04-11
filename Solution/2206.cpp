#include <iostream>
#include <string>
#include <queue>

using namespace std;

#define MAX 1000

int N, M;
int MAP[MAX][MAX];
bool Visit[MAX][MAX][2];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void input(){
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        string Inp;
        cin >> Inp;
        for(int j = 0; j < M; j++){
            int Tmp = Inp[j] - '0';
            MAP[i][j] = Tmp;
        }
    }
}

int BFS(){
    queue<pair<pair<int, int>, pair<int, int>>> Q;
    Q.push({{0, 0},{0, 1}});
    Visit[0][0][0] = true;

    while(Q.empty() == 0){
        int x = Q.front().first.first;
        int y = Q.front().first.second;
        int B = Q.front().second.first;
        int Cnt = Q.front().second.second;
        Q.pop();

        if(x == N - 1 && y == M - 1){
            return Cnt;
        }
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx >= 0 && ny >= 0 && nx < N && ny < M){
                if(MAP[nx][ny] == 1 && B == 0){
                    Visit[nx][ny][B+1] = true;
                    Q.push({{nx, ny},{B + 1, Cnt + 1}});
                }else if(MAP[nx][ny] == 0 && Visit[nx][ny][B] == false){
                    Visit[nx][ny][B] = true;
                    Q.push({{nx, ny},{B, Cnt + 1}});
                }
            }
        }
    }
    return -1;
}

void Solution(){
    int R = BFS();
    cout << R << "\n";
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