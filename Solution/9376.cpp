#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <queue>
#include <algorithm>
#include <deque>
using namespace std;

#define MAX 105

struct PRISON{
    int x, y;
};

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int w,h;
int visited[MAX][MAX][3];
PRISON prisoner[3];
char MAP[MAX][MAX];
string tmp_map[MAX];

void input(){
    cin>>h>>w;
    for(int y = 0; y < h; y++){
        cin>>tmp_map[y];
    }
//    for(int y = 0; y < h; y++){
//        for(int x = 0; x < w; x++){
//            cout<<tmp_map[y][x]<<" ";
//        }
//        cout<<"\n";
//    }cout<<"\n";
    memset(MAP,'.',sizeof(MAP));
    bool is_update = false;
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            MAP[y+1][x+1] = tmp_map[y][x];
            if(tmp_map[y][x] == '$'){
                if(!is_update){
                    prisoner[0].x = x+1;
                    prisoner[0].y = y+1;
                    is_update = true;
                }else{
                    prisoner[1].x = x+1;
                    prisoner[1].y = y+1;
                }
            } 
        }
    }
    prisoner[3].x = 0;
    prisoner[3].y = 0;
//    for(int y = 0; y < h + 2; y++){
//        for(int x = 0; x < w + 2; x++){
//            cout<<MAP[y][x]<<" ";
//        }
//        cout<<"\n";
//    }
}

void solution(){
    memset(visited,-1,sizeof(visited));
    for(int i = 0; i < 3; i++){
        queue<pair<int,int>> q;
        q.push({prisoner[i].y,prisoner[i].x});
        visited[prisoner[i].y][prisoner[i].x][i] = 0;
        while(!q.empty()){
            auto cur = q.front();
            q.pop();
            for(int dir = 0; dir < 4; dir++){
                int nx = cur.second + dx[dir];
                int ny = cur.first + dy[dir];
                if(nx < 0 || ny < 0 || nx >= w+2 || ny >= h+2)continue;
                if(MAP[ny][nx] == '*' || visited[ny][nx][i] != -1) continue;
                if(MAP[ny][nx] == '#'){
                    visited[ny][nx][i] = visited[cur.first][cur.second][i] + 1;
                }else{
                    visited[ny][nx][i] = visited[cur.first][cur.second][i];
                }
                q.push({ny,nx}); 
            }
        }
    }
}

void checker(){
    int sum = 987654321;
    for(int y = 0; y < h + 2; y++){
        for(int x = 0; x < w + 2; x++){
            int tmp = 0;
            for(int i = 0; i < 3; i++){
                tmp += visited[y][x][i];
            }
            if(MAP[y][x] == '*')continue;
            if(MAP[y][x] == '#'){
                tmp -= 2;
            }
            if(sum > tmp){
                sum = tmp;
            }
        }
    }
    cout<<sum<<"\n";
}

void run(){
    solution();
    checker();
}

int main(){
    int t = 0;
    cin>> t;
    while(t--){
        input();
        run();
    }    
    return 0;
}
