#include <iostream>
#include <vector>
#include <cstring>

#define MAX 55

using namespace std;

struct COORD{
    int x,y;
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
        for(int j = 0; j < N ; j++){
            cin >> MAP[i][j];
        }
    }
}
void solve(){
    input();
    Solution();
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();

    return 0;
}