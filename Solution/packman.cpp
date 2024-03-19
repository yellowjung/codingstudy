#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_T 25
#define MAX_N 4
#define DIR_NUM 8
#define P_DIR_NUM 4
#define MAX_DECAY 2

int n = 4;
int m, t;

int px, py;

int monster[MAX_T + 1][MAX_N][DIR_NUM];

int dead[MAX_N][MAX_N][MAX_DECAY + 1];

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> m >> t;
    cin >> px >> py;

    px--; py--;

    return 0;
}