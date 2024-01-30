#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

int student[401][4];
int map[21][21];
int N;
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};
vector<int> order;

struct Info{
    int x;
    int y;
    int empty;
    int match;
};

bool compare(Info a, Info b){
    if(a.match == b.match){
        if(a.empty == b.empty){
            if(a.x == b.x){
                return a.y < b.y;
            }
            return a.x < b.x;
        }
        return a.empty > b.empty;
    }
    return a.match > b.match;
}

void input(){
    cin >> N;
    for(int i = 1; i <= N*N; i++){
        int key;
        cin >> key;
        order.push_back(key);
        for(int j = 0; j < 4; j++){
            int num;
            cin >> num;
            student[key][j] = num;
        }
    }
}

Info bfs(int key, int x, int y){
    Info tmp = {x, y, 0, 0};
    for(int i = 0; i < 4; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 1 || ny < 1 || nx > N || ny > N) continue;

        if(map[nx][ny] == 0){
            tmp.empty++;
            continue;
        }

        for(int j = 0; j < 4; j ++){
            if(student[key][j] == map[nx][ny]) tmp.match++;
        }
    }

    return tmp;
}

void matching(int key){
    vector<Info> list;

    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            if(map[i][j] == 0) list.push_back(bfs(key, i, j));
        }
    }

    sort(list.begin(), list.end(), compare);
    map[list[0].x][list[0].y] = key;
}

int getScore(){
    int sum = 0;
    for(int k = 1; k <= N * N; k++){
        for(int i = 1; i <= N; i++){
            bool endFlag = false;
            for(int j = 1; j <= N; j++){
                if(map[i][j] == k){
                    Info tmp = bfs(k, i, j);
                    sum += pow(10, tmp.match - 1);
                    endFlag = true;
                    break;
                }
            }
            if(endFlag) break;
        }
    }
    return sum;
}

void Solve(){
    for(int i = 0; i < order.size(); i++){
        matching(order[i]);
    }

    cout << getScore() <<"\n";
}

void Solution(){
    input();
    Solve();
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Solution();
    return 0;
}