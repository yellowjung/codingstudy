#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

#define MAX 25
using namespace std;

int r, c, k, w;
int map[MAX][MAX];
bool wallMap[MAX][MAX][4];

vector<pair<int,int>> searchPos;
vector<pair<pair<int,int>, int>> heater;
vector<pair<pair<int,int>, int>> wall;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int wdx[4][3] = {{-1, 0, 1},{-1, 0, 1},{1, 1, 1},{-1, -1, -1}};
int wdy[4][3] = {{1, 1, 1},{-1, -1, -1},{-1, 0, 1}, {-1, 0, 1}};

void input(){
    cin >> r >> c >> k;
    for(int i = 1; i <= r; i++){
        for(int j = 1; j <= c; j++){
            cin >> map[i][j];
            if(map[i][j] != 0 && map[i][j] != 5){
                heater.push_back({{i, j}, map[i][j]});
            }else if(map[i][j] == 5){
                searchPos.push_back({i ,j});
            }
            map[i][j] = 0;
        }
    }
    cin >> w;
    for(int i = 0; i < w; i++){
        int a, b, c;
        cin >> a >> b >> c;
        wall.push_back({{a, b}, c});
    }

}

void settingWall(){
    for(int i = 0; i < w; i++){
        int x = wall[i].first.first;
        int y = wall[i].first.second;
        int t = wall[i].second;

        if(t == 0){
            wallMap[x][y][3] = true;
            wallMap[x - 1][y][2] = true;
        }else{
            wallMap[x][y][0] = true;
            wallMap[x][y + 1][1] = true;
        }
    }
}

int changeMydir(int d){
    switch (d)
    {
    case 1:
        return 0;
    case 2:
        return 1;
    case 3:
        return 3;
    case 4:
        return 2;    
    }
}

bool checkWall(int x, int y, int nx, int ny, int d, int dir){
    if(dir == 1){
        if(wallMap[x][y][d] == false) return true;
    }else if(dir == 0){
        if(d == 0){
            int upx = x - 1;
            int upy = y;
            if(wallMap[x][y][3] == false && wallMap[upx][upy][0] == false) return true;
        }else if(d == 1){
            int upx = x- 1;
            int upy = y;
            if(wallMap[x][y][3] == false && wallMap[upx][upy][1] == false) return true;
        }else if(d == 2){
            int dnx = x;
            int dny = y - 1;
            if(wallMap[x][y][1] == false && wallMap[dnx][dny][2] == false) return true;
        }else if(d == 3){
            int dnx = x;
            int dny = y - 1;
            if(wallMap[x][y][1] == false && wallMap[dnx][dny][3] == false) return true;
        }
    }else if(dir == 2){
        if(d == 0){
            int upx = x + 1;
            int upy = y;
            if(wallMap[x][y][2] == false && wallMap[upx][upy][0] == false) return true;
        }else if(d == 1){
            int upx = x + 1;
            int upy = y;
            if(wallMap[x][y][2] == false && wallMap[upx][upy][1] == false) return true;
        }else if(d == 2){
            int dnx = x;
            int dny = y + 1;
            if(wallMap[x][y][0] == false && wallMap[dnx][dny][2] == false) return true;
        }else if(d == 3){
            int dnx = x;
            int dny = y + 1;
            if(wallMap[x][y][0] == false && wallMap[dnx][dny][3] == false) return true;
        }
    }
}

void addMap(int A[][MAX], int B[][MAX]){
    for(int i = 1; i <= r; i++){
        for(int j = 1; j <= c; j++){
            A[i][j] += B[i][j];
        }
    }
}

void spread(int x, int y, int d){
    bool update[MAX][MAX] = {false, };
    //d = changeMydir(d);
    x += dx[d];
    y += dy[d];
    if(x < 1 || y < 1 || x > r || y > c) return;

    queue<pair<pair<int, int>, int>> q;
    q.push({{x, y}, 5});

    while(q.empty() == 0){
        int x = q.front().first.first;
        int y = q.front().first.second;
        int wind = q.front().second;
        q.pop();

        map[x][y] += wind;
        if(wind == 1) break;

        for(int i = 0; i < 3; i++){
            int nx = x + wdx[d][i];
            int ny = y + wdy[d][i];
            if (nx >= 1 && ny >= 1 && nx <= r && ny <= c){
                if(update[nx][ny] == false && checkWall(x, y, nx, ny, d, i) == true){
                    update[nx][ny] = true;
                    q.push({{nx, ny}, wind - 1});
                }
            }
        }
    }   
}

void spreadWind(){
    for(int i = 0; i < heater.size(); i++){
        int x = heater[i].first.first;
        int y = heater[i].first.second;
        int d = heater[i].second;
        spread(x, y, d);
    }
}

void controlTemperature(){
    int tempMap[MAX][MAX] = {0, };
    for(int x = 1; x <= r; x++){
        for(int y = 1; y <= c; y++){
            for(int i = 0; i < 2; i++){
                int dir = i == 0 ? 0 : 2;
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                if (nx >= 1 && ny >= 1 && nx <= r && ny <= c){
                    if(wallMap[x][y][dir] == false){
                        pair<int, int> maxCoord, minCoord;
                        if(map[x][y] > map[nx][ny]){
                            maxCoord = {x, y};
                            minCoord = {nx, ny};
                        }else{
                            maxCoord = {nx, ny};
                            minCoord = {x, y};
                        }

                        int diff = abs(map[x][y] - map[nx][ny]);
                        diff /= 4;
                        tempMap[maxCoord.first][maxCoord.second] -= diff;
                        tempMap[minCoord.first][minCoord.second] += diff;
                    }
                }
            }
        }
    }
    addMap(map,tempMap);
}

void decreaseTemperature(){
    for(int i = 1; i <= c; i++){
        if(map[1][i] > 0) map[1][i]--;
        if(map[r][i] > 0) map[r][i]--;
    }
    for(int i = 2; i < r; i++){
        if(map[i][1] > 0) map[i][1]--;
        if(map[i][c] > 0) map[i][c]--;
    }
}

bool check(){
    for(int i = 0; i < searchPos.size(); i++){
        int x = searchPos[i].first;
        int y = searchPos[i].second;
        if(map[x][y] < k ) return false;
    }

    return true;
}

void solution(){
    settingWall();
    int chocolate = 0;
    while(1){
        if(chocolate > 100){
            break;
        }

        spreadWind();
        controlTemperature();
        decreaseTemperature();
        chocolate++;

        if(check() == true){
            break;
        }
    }

    cout << chocolate << "\n";
}

void solve(){
    input();
    solution();
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();

    return 0;
}