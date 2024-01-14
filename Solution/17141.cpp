#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

#define MAX 50

int N, M, Answer = 987654321;
int MAP[MAX][MAX];
bool visited[MAX][MAX];
bool select_position[10];
vector<pair<int, int>> v;
vector<pair<int, int>> selected_virus;

int dx[] = {0, 0, 1, -1};
int dy[] = {-1, 1, 0, 0};

int min(int a, int b) { if ( a < b) return a; return b;}

void solve();
void input();
void solution();
void selected_virus_pos(int idx, int cnt);
void spread_virus();
bool check();

int main(){
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();

    return 0;
}

bool check(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(MAP[i][j] == 1) continue;
            if(visited[i][j] == false) return false;
        }
    }
    return true;
}

void spread_virus(){
    queue<pair<int, int>> q;
    for(int i = 0; i < selected_virus.size(); i++){
        int x = selected_virus[i].first;
        int y = selected_virus[i].second;
        q.push(make_pair(x,y));
        visited[x][y] = true;
    }

    int cnt = 0;
    while(q.empty() == 0){
        int s = q.size();
        for(int qs = 0; qs < s; qs++){
            int x = q.front().first;
            int y = q.front().second;
            q.pop();

            for(int  i = 0; i < 4; i++){
                int nx = x + dx[i];
                int ny = y + dy[i];

                if( nx >= 0 && ny >= 0 && nx < N && ny < N){
                    if(visited[nx][ny] == false && MAP[nx][ny] != 1){
                        visited[nx][ny] = true;
                        q.push(make_pair(nx, ny));
                    }
                }
            }
        }
        if(q.size() != 0) cnt++;
    }
    if(check() == true) Answer = min(Answer, cnt);
}

void selected_virus_pos(int idx, int cnt){
    if(cnt == M){
        memset(visited, false, sizeof(visited));
        spread_virus();
        return;
    }

    for(int i = idx; i < v.size(); i++){
        if(select_position[i] == true) continue;
        select_position[i] = true;
        selected_virus.push_back(v[i]);
        selected_virus_pos(i, cnt+1);
        selected_virus.pop_back();
        select_position[i] = false;
    }
}

void solve(){
    input();
    solution();
}

void input(){
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> MAP[i][j];
            if(MAP[i][j] == 2) v.push_back(make_pair(i, j));
        }
    }
}

void solution(){
    selected_virus_pos(0, 0);
    if(Answer == 987654321) Answer = -1;
    cout<< Answer <<"\n";
}