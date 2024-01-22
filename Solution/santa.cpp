#include <iostream>
#include <vector>
#include <unordered_map>

#define MAX_BELT 15
#define MAX_BOX 100010

using namespace std;

struct BELT{
    int num;
    int front;
    int back;
    int state;
};

struct BOX{
    int weight;
    int belt_id;
    int prev;
    int next;
};

int n, m;
int input[MAX_BOX];
unordered_map<int, BOX> box;
unordered_map<int, BELT> belt;

void FUNC(int Q){
    if(Q == 100){
        cin >> n >> m;

        int cnt = 0;
        int belt_id = 1;
        int pivot = n / m;
        for(int i = 0; i < n; i++){
            int id;
            cin >> id;
            input[i] = id;
            if(cnt == 0){
                
            }
        }
    }
}

int main(){
    int Q;
    cin >> Q;
    for(int i = 0; i < Q; i++){
        int order;
        cin >> order;
        FUNC(order); 
    }
    return 0;
}