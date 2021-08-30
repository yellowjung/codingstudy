#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

#define MAX 1501

int visited[MAX][MAX];
string MAP[MAX];
int R, C;

vector<pair<int,int>> ice;
pair<int,int> SWAN1;
pair<int,int> SWAN2;

int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

void print_map(){
    cout<<"======================"<<"\n";
    for(int y = 0; y < R; y++){
        for(int x = 0; x < C; x++){
            cout<<MAP[y][x]<<" ";
        }
        cout<<"\n";
    }
    cout<<"======================"<<"\n";
}

void init_map(){
    for(int y = 0; y < R; y++){
        for(int x = 0; x < C; x++){
            MAP[y][x] = '.';
        }
    }
}

void init_visited(){
    for(int y = 0; y < R; y++){
        for(int x = 0; x < C; x++){
            visited[y][x] = 0;
        }
    }
}

bool Find_Swan(){
    bool is_check = false;
    queue<pair<int,int>> q;
    init_visited();

    q.push(SWAN1);
    visited[SWAN1.first][SWAN1.second] = 1;

    while(!q.empty()){
        auto cur = q.front();
        q.pop();
        if(cur.first == SWAN2.first &&
                cur.second == SWAN2.second){
            is_check = true;
            break;
        }

        for(int dir = 0; dir < 4; dir++){
            int nx = cur.second + dx[dir];
            int ny = cur.first + dy[dir];
            
            if(nx < 0 || ny < 0 || nx >= C || ny >= R){
                continue;
            }
            if(MAP[ny][nx] == 'X' || visited[ny][nx] == 1){
                continue;
            }
            visited[ny][nx] = 1;
            q.push({ny,nx});

        }
    }

    return is_check;
}

void melting(){
    vector<pair<int,int>> tmp_ice;
    for(int i = 0; i < ice.size(); i++){
        auto cur = ice[i];
        bool is_check = false;
        for(int dir = 0; dir < 4; dir++){
            int nx = cur.second + dx[dir];
            int ny = cur.first + dy[dir];
            if(nx < 0 || ny < 0 || nx >= C || ny >= R)continue;
            if(MAP[ny][nx] == '.'){
                is_check = true;
                continue;
            }
        }
        if(is_check == false){
            tmp_ice.push_back(cur);
        }
    }
    ice.clear();
    ice = tmp_ice;
    init_map();
    for(int i = 0; i < ice.size(); i++){
        MAP[ice[i].first][ice[i].second] = 'X';
    }
}

void solving(){
    int day = 0;
    //1.Find Swan 2
    while(true){
        bool checker = Find_Swan();
        //2.Melting ice
        if(checker){
            cout<<day<<"\n";
            break;
        }else{
            melting();
        }
        day++;
    }
//    print_map();
}

void input(){
    cin>>R>>C;
    bool checker = false;
    for(int y = 0; y < R; y++){
        cin>>MAP[y];
        for(int x = 0; x < C; x++){
            if(MAP[y][x] == 'L'){
                if(checker == false){
                    SWAN1 = {y,x};
                    checker = true;
                }else{
                    SWAN2 = {y,x};
                }
                MAP[y][x] = '.';
            }else if(MAP[y][x] == 'X'){
                ice.push_back({y,x});
            }
        }
    }
}

void solution(){
    input();
    solving();
}

int main(){
   solution(); 
    return 0;
}
