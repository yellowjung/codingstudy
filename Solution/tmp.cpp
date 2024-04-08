#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

#define MAX_M 10

int n, m, q;

unordered_map<int, int> weight;

unordered_map<int, int> prv, nxt;

int head[MAX_M], tail[MAX_M];

bool broken[MAX_M];

unordered_map<int, int> belt_num;

void BuildFactory(){
    cin >> n >> m;
    vector<int> ids(n), ws(n);
    for(int i = 0; i < n; i++){
        cin >> ids[i];
    }

    for(int i = 0; i < n; i++){
        cin >> ws[i];
    }

    for(int i = 0; i < n; i++){
        weight[ids[i]] = ws[i];
    }

    int size = n / m;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> q;
    while(q--){
        int q_type;
        cin >> q_type;
        if(q_type == 100){
            BuildFactory();
        }
    }


    return 0;
}