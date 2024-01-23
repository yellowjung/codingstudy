#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

int N, M, K;
int Ex, Ey;
int Map[11][11];

int Ans = 0;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

struct Person{
    int x;
    int y;
};

struct Position{
    int x; 
    int y;
    int Size;
};

vector<Person> Vector;
vector<Position> Data;


void input(){
    cin >> N >> M >> K;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            cin >> Map[i][j];
        }
    }

    int X;
    int Y;
    for(int i = 1; i <= M; i++){
        cin >> X >> Y;
        Vector.push_back({X, Y});
    }

    cin >> Ex >> Ey;
}

int Dist_Exit(int x, int y){
    return abs(x - Ex) + abs(y - Ey);
}

void Exit(Person& P){
    int Curr = Dist_Exit(P.x, P.y);

    for(int i = 0; i < 4; i++){
        int nx = P.x + dx[i];
        int ny = P.y + dy[i];
        int Next = Dist_Exit(nx, ny);

        if(nx < 1 || ny < 1 || nx > N || ny > N) continue;
        if(Curr <= Next) continue;
        if(Map[nx][ny] > 0) continue;

        Ans++;
        P.x = nx;
        P.y = ny;
        break;
    }
}

void Square_Data(int x , int y){
    int x_Gap = abs(x - Ex);
    int y_Gap = abs(y - Ey);

    int Size = max(x_Gap, y_Gap);

    int mx = max(Ex, x) - Size;
    if(mx < 1) mx = 1;

    int my = max(Ey, y) - Size;
    if(my < 1) my = 1;

    Data.push_back({mx ,my, Size});

}

bool Cmp(Position& A, Position& B){
    if(A.Size == B.Size){
        if(A.x == B.x){
            return A.y < B.y;
        }
        return A.x < B.x;
    }
    return A.Size < B.Size;
}

void Rotation(int x, int y, int Size){
    vector<pair<pair<int, int>, int>> Pair;
    bool Flag = true;

    for(int i = 0; i <= Size; i++){
        for(int j = 0; j <= Size; j++){
            int px = x + i;
            int py = y + j;

            int nx = x + j;
            int ny = y + Size - i;

            if(px == Ex && py == Ey && Flag == true){
                Flag = false;
                Ex = nx;
                Ey = ny;
            }
            
            Pair.push_back({{nx, ny}, Map[px][py]});
        }
    }

    for( auto E : Pair){
        int x = E.first.first;
        int y = E.first.second;
        int m = E.second;
        if(m == 0){
            Map[x][y] = 0;
        }else if(m > 0){
            Map[x][y] = m - 1;
        }
    }

    for( auto& E : Vector){
        if(E.x >= x && E.x <= x + Size){
            if(E.y >= y && E.y <= y + Size){
                int i = E.x - x;
                int j = E.y - y;

                E.x = x + j;
                E.y = y + Size -i;
            }
        }
    }
}

void solve(){
    while(K--){
        for(int i = 0; i < Vector.size(); i++){
            Exit(Vector[i]);

            if((Vector[i].x == Ex) && (Vector[i].y == Ey)){
                Vector.erase(Vector.begin() + i);
                i--;
                continue;
            }

            Square_Data(Vector[i].x, Vector[i].y);
        }

        if(Vector.size() == 0) break;

        sort(Data.begin(), Data.end(), Cmp);
        Rotation(Data[0].x, Data[0].y, Data[0].Size);
        Data.clear();
    }
}

void solution(){
    input();
    solve();
    cout << Ans <<"\n";
    cout<< Ex << ' '<< Ey <<"\n";
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solution();

    return 0;
}