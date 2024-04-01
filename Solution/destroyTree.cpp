#include <iostream>

using namespace std;

#define MAX_N 20
#define DIR_NUM 4

int n, m, k, c;
int tree[MAX_N + 1][MAX_N + 1];
int add_tree[MAX_N + 1][MAX_N + 1];
int herb[MAX_N + 1][MAX_N + 1];



int ans;

bool IsOutRange(int x, int y){
    return !(1 <= x && x <= n && 1 <= y && y <= n);
}

void Init(){
    cin >> n >> m >> k >> c;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cin >> tree[i][j];
        }
    }
}

void StepOne(){
    int dx[DIR_NUM] = {-1, 0, 1, 0};
    int dy[DIR_NUM] = {0, -1, 0, 1};

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(tree[i][j] <= 0) continue;

            int cnt = 0;
            for(int dir = 0; dir < 4; dir++){
                int nx = i + dx[dir];
                int ny = j + dy[dir];
                if(IsOutRange(nx, ny)) continue;
                if(tree[nx][ny] > 0) cnt++;
            }
            tree[i][j] += cnt;
        }
    }
}

void StepTwo(){
    int dx[DIR_NUM] = {-1, 0, 1, 0};
    int dy[DIR_NUM] = {0, -1, 0, 1};

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            add_tree[i][j] = 0;
        }
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(tree[i][j] <= 0) continue;

            int cnt = 0;
            for(int dir = 0; dir < 4; dir++){
                int nx = i + dx[dir];
                int ny = j + dy[dir];
                if(IsOutRange(nx, ny)) continue;
                if(herb[nx][ny]) continue;
                if(tree[nx][ny] == 0) cnt++;
            }

            for(int dir = 0; dir < 4; dir++){
                int nx = i + dx[dir];
                int ny = j + dy[dir];
                if(IsOutRange(nx, ny)) continue;
                if(herb[nx][ny]) continue;
                if(tree[nx][ny] == 0){
                    add_tree[nx][ny] += tree[i][j] / cnt;
                } 
            }
        }
    }

    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++){
            tree[i][j] += add_tree[i][j];
        }
    }
}

void DeleteHerb(){
    for(int i = 1; i <=n; i++){
        for(int j = 1; j<= n; j++){
            if(herb[i][j] > 0){
                herb[i][j] -= 1;
            }
        }
    }
}

void StepThree(){
    int dx[DIR_NUM] = {-1,  1, 1, -1};
    int dy[DIR_NUM] = {-1, -1, 1,  1};

    int max_del = 0;
    int max_x = 1;
    int max_y = 1;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(tree[i][j] <= 0) continue;

            int cnt = tree[i][j];
            for(int dir = 0; dir < 4; dir++){
                int nx = i;
                int ny = j;
                for(int x = 1; x <= k; x++){
                    nx = nx + dx[dir];
                    ny = ny + dy[dir];
                    if(IsOutRange(nx, ny)) break;
                    if(tree[nx][ny] <= 0) break;
                    cnt += tree[nx][ny];
                }
            }

            if(max_del < cnt){
                max_del = cnt;
                max_x = i;
                max_y = j;
            }
        }
    }
    

    ans += max_del;

    if(tree[max_x][max_y] > 0){
        tree[max_x][max_y] = 0;
        herb[max_x][max_y] = c;
        for(int dir = 0; dir < 4; dir++){
            int nx = max_x;
            int ny = max_y;
            for(int x = 1; x <= k; x++){
                nx = nx + dx[dir];
                ny = ny + dy[dir];
                if(IsOutRange(nx, ny)) break;
                if(tree[nx][ny] < 0) break;
                if(tree[nx][ny] == 0){
                    herb[nx][ny] = c;
                    break;
                }

                tree[nx][ny] = 0;
                herb[nx][ny] = c;
            }
        }
    }
}


int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Init();

    for(int i = 1; i <= m; i++){
        StepOne();

        StepTwo();

        DeleteHerb();

        StepThree();
    }

    cout<<ans<<"\n";

    return 0;
}