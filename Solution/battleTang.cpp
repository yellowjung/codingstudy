#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef struct _player{
    int x;
    int y ;
     int stat;
     int gun;
     int dir;
     int score;
}Player;

int N, m, k, r = 0;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
vector<int> gun[21][21];
Player player[31];
int playerLoc[21][21];

bool cmp(int a, int b){
    return a > b;
}

void input(){
    int a, x, y, d, s;
     
    cin >> N >> m >> k;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> a;
            gun[i][j].push_back(a);
        }
    }

    for(int i = 1; i <= m; i++){
        cin >> x >> y >> d >> s;
        player[i].x = x - 1;
        player[i].y = y - 1;
        player[i].dir = d;
        player[i].stat = s;
        player[i].gun = 0;
        player[i].score = 0;
        playerLoc[x - 1][y - 1] = i;
    }
}

void changeGun(int idx, int x, int y){
    if(gun[x][y][0] > player[idx].gun){
        int temp = gun[x][y][0];
        gun[x][y][0] = player[idx].gun;
        player[idx].gun = temp;
        sort(gun[x][y].begin(), gun[x][y].end(), cmp);
    }
}

void moveLoser(int idx, int x, int y){
    for(int k = 0; k < 4; k++){
        int nx, ny;
        nx = x + dx[(player[idx].dir + k) % 4];
        ny = y + dy[(player[idx].dir + k) % 4];
        if(nx < 0 || ny < 0 || nx >= N || ny >= N || playerLoc[nx][ny]) continue;
        player[idx].x = nx;
        player[idx].y = ny;
        player[idx].dir = (player[idx].dir + k) % 4;
        playerLoc[nx][ny] = idx;
        changeGun(idx, nx, ny);
        break;
    }
}

void fight(int a, int b, int x, int y){
    int win, lose, score = 0;
    int scoreA = player[a].stat + player[a].gun;
    int scoreB = player[b].stat + player[b].gun;
    if(scoreA == scoreB){
        if(player[a].stat > player[b].stat){
            win = a;
            lose = b;
            score = scoreA - scoreB;
        }else{
            win = b;
            lose = a;
            score = scoreB - scoreA;
        }
    }else if(scoreA > scoreB){
        win = a;
        lose = b;
        score = scoreA - scoreB;
    }else{
        win = b;
        lose = a;
        score = scoreB - scoreA;
    }
    gun[x][y].push_back(player[lose].gun);
    sort(gun[x][y].begin(), gun[x][y].end(), cmp);
    player[lose].gun = 0;
    moveLoser(lose, x, y);

    playerLoc[x][y] = win;
    player[win].x = x; player[win].y = y;
    changeGun(win, x, y);
    player[win].score += score;
}

void solve(){
    while(++r <= k){
        for(int i = 1; i <= m; i++){
            int nx, ny;
            nx = player[i].x + dx[player[i].dir];
            ny = player[i].y + dy[player[i].dir];
            if(nx < 0 || ny < 0 || nx >= N || ny >= N){
                player[i].dir = (player[i].dir + 2) % 4;
                nx = player[i].x + dx[player[i].dir];
                ny = player[i].y + dy[player[i].dir];
            }
            if(playerLoc[nx][ny]){
                playerLoc[player[i].x][player[i].y] = 0;
                fight(i, playerLoc[nx][ny], nx, ny);
            }else{
                playerLoc[player[i].x][player[i].y] = 0;
                playerLoc[nx][ny] = i;
                player[i].x = nx; player[i].y = ny;
                changeGun(i, nx, ny);
            }

        }
    }
}

void answer(){
    for(int i = 1; i <= m; i++){
        cout<<player[i].score<<" ";
    }
    cout<<"\n";
}

void solution(){
    input();
    solve();
    answer();
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solution();

    return 0;
}