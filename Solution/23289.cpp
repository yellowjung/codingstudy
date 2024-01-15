#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAX 25

int r, c, k, w;
int map[MAX][MAX];
bool wallMap[MAX][MAX][4];

vector<pair<int,int>> searchPos;
vector<pair<pair<int,int>, int>> heater;
vector<pair<pair<int,int>, int>> wall;

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1 ,0};

int wdx[4][3] = {{-1, 0, 1}, {-1, 0, 1}, {1, 1, 1}, {-1, -1, -1}};
int wdy[4][3] = {{1, 1, 1}, {-1, -1, -1}, {-1, 0, 1}, {-1, 0, 1}};

void input(){
    cin >> r >> c >> k;
    for(int  i = 1; i <= r; i++){
        for(int j = 1; j <= c; j++){
            cin >> map[i][j];
            if(map[i][j] != 0 && map[i][j] != 5){
                heater.push_back({{i, j}, map[i][j]});
            }else if(map[i][j] == 5){
                
            }
        }
    }
}

void solution(){

}

void solve(){
    input();
    solution();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();

    return 0;
}