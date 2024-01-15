#include <iostream>
#include <queue>
#include <vector>

#define MAX 110
using namespace std;

int n, k;
deque<int> bowl[MAX];

int dx[] = {0, -1};
int dy[] = {1, 0};

void input(){
    cin >> n >> k;
    for(int i = 0; i< n; i++){
        int a; cin >> a;
        bowl[0].push_back(a);
    }
}

bool check(){
    int minFish = 987654321;
    int maxFish = -987654321;
    for(int i = 0; i < bowl[0].size(); i++){
        minFish = min(minFish, bowl[0][i]);
        maxFish = max(maxFish, bowl[0][i]);
    }

    return maxFish - minFish <= k ? true : false;
}

void addFish(){
    int minFish = 987654321;
    vector<int> idxV;
    for(int i = 0; i < bowl[0].size(); i++){
        if(bowl[0][i] < minFish){
            minFish = bowl[0][i];
            idxV.clear();
            idxV.push_back(i);
        }else if(bowl[0][i] == minFish){
            idxV.push_back(i);
        }
    }

    for(auto idx : idxV){
        bowl[0][idx]++;
    }
}

bool canBuild(int w, int h){
    if(bowl[0].size() - w < h){
        return false;
    }
    return true;
}

int buildBowl(){
    int width = 1;
    int height = 1;
    bool flag = false;

    while(1){
        if (canBuild(width, height) == false){
            break;
        }

        int tmpWidth = width;

        for(int i = 0; i < width; i++, tmpWidth--){
            int idx = 0;
            for(int j  = 0; j < height; j++, idx++){
                bowl[tmpWidth].push_back(bowl[idx][i]);
            }
        }

        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                bowl[i].pop_front();
            }
        }

        if(flag == false){
            height++;
            flag = true;
        }else{
            width++;
            flag = false;
        }
    }
    return height;
}

void adjustFish(int height){
    deque<int> tmpbowl[MAX];
    for(int i = 0; i < height; i++){
        tmpbowl[i] = bowl[i];
    }

    for(int i = height - 1; i >= 0; i--){
        for(int j = 0; j < bowl[i].size(); j++){
            int x = i;
            int y = j;
            int num = bowl[x][y];
            for(int k = 0; k < 2; k++){
                int nx = x + dx[k];
                int ny = y + dy[k];
                if(nx >= 0 && ny < bowl[i].size()){
                    int num2 = bowl[nx][ny];
                    int diff = abs(num - num2) / 5;
                    if(diff > 0){
                        if(num > num2){
                            tmpbowl[x][y] -= diff;
                            tmpbowl[nx][ny] += diff;
                        }else{
                            tmpbowl[nx][ny] -= diff;
                            tmpbowl[x][y] += diff;
                        }
                    }
                }
            }
        }
    }

    for(int i = 0; i < height; i++){
        bowl[i] = tmpbowl[i];
    }
}

void spreadBowl(int height){
    int width = bowl[height - 1].size();
    int size = bowl[0].size();
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            bowl[0].push_back(bowl[j][i]);
        }
    }
    for(int i = 1; i < height; i++){
        bowl[i].clear();
    }
    for(int i = width; i < size; i++){
        bowl[0].push_back(bowl[0][i]);
    }
    for(int i = 0; i < size; i++){
        bowl[0].pop_front();
    }
}

void buildBowl2(){
    int n = bowl[0].size();
    for(int i = 0; i < n / 2; i++){
        bowl[1].push_front(bowl[0][i]);
    }
    for(int i = 0; i < n / 2; i++){
        bowl[0].pop_front();
    }
    for(int i = 0; i < n / 4; i++){
        bowl[2].push_front(bowl[1][i]);
        bowl[3].push_front(bowl[0][i]);
    }
    for(int i = 0; i < n / 4; i++){
        bowl[0].pop_front();
        bowl[1].pop_front();
    }
}

void solution(){
    int answer = 0;
    while(1){
        if(check() == true){
            cout<<answer<<"\n";
            break;
        }

        addFish();
        int height = buildBowl();
        adjustFish(height);
        spreadBowl(height);
        buildBowl2();
        adjustFish(4);
        spreadBowl(4);
        answer++;
    }
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