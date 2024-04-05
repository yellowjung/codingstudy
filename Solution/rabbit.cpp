#include <iostream>
#include <queue>
#include <map>

using namespace std;

#define MAX_N 2000

int n, m, p;

int id[MAX_N + 1];

int pw[MAX_N + 1];

int jump_cnt[MAX_N + 1];

long long result[MAX_N + 1];

pair<int, int> point[MAX_N + 1];

map<int, int> id_to_idx;

bool is_runned[MAX_N + 1];

long long total_sum;

struct Rabbit{
    int x, y, j, id;

    bool operator<(const Rabbit &b) const{
        if(j != b.j) return j >b.j;
        if(x + y != b.x + b.y) return x + y > b.x + b.y;
        if(x != b.x) return x > b.x;
        if(y != b.y) return y > b.y;
        return id > b.id;
    }
};

bool Cmp(Rabbit a, Rabbit b){
    if(a.x + a.y != b.x + b.y) return a.x + a.y < b.x + b.y;
    if(a.x != b.x) return a.x < b.x;
    if(a.y != b.y) return a.y < b.y;
    return a.id < b.id;
}

void init(){
    cin >> n >> m >> p;
    for(int i = 1; i <= p; i++){
        cin >> id[i] >> pw[i];
        id_to_idx[id[i]] = i;
        point[i] = make_pair(1, 1);
    }
}

Rabbit GetUpRabbit(Rabbit cur_rabbit, int dis){
    Rabbit up_rabbit = cur_rabbit;
    dis %= 2 * (n - 1);

    if(dis >= up_rabbit.x - 1){
        dis -= (up_rabbit.x - 1);
        up_rabbit.x = 1;
    }else{
        up_rabbit.x -= dis;
        dis = 0;
    }

    if(dis >= n - up_rabbit.x){
        dis -= (n - up_rabbit.x);
        up_rabbit.x = n;
    }else{
        up_rabbit.x += dis;
        dis = 0;
    }

    up_rabbit.x -= dis;

    return up_rabbit;
}

Rabbit GetDownRabbit(Rabbit cur_rabbit, int dis){
    Rabbit down_rabbit = cur_rabbit;
    dis %= 2 * (n - 1);

    
}

void start_round(){
    int k, bonus;
    cin >> k >> bonus;
    priority_queue <Rabbit> rabbit_pq;

    for(int i = 1; i <= p; i++){
        is_runned[i] = false;
    }

    for(int i = 1; i<= p; i++){
        Rabbit new_rabbit;
        new_rabbit.x = point[i].first;
        new_rabbit.y = point[i].second;
        new_rabbit.j = jump_cnt[i];
        new_rabbit.id = id[i];

        rabbit_pq.push(new_rabbit);
    }


    while(k--){
        Rabbit cur_rabbit = rabbit_pq.top(); rabbit_pq.pop();

        int dis = pw[id_to_idx[cur_rabbit.id]];
        Rabbit next_rabbit = cur_rabbit;
        next_rabbit.x = 0;
        next_rabbit.y = 0;

        Rabbit up_rabbit = GetUpRabbit(cur_rabbit, dis);

        if(Cmp(next_rabbit, up_rabbit)) next_rabbit = up_rabbit;

        Rabbit down_rabbit = GetDownRabbit(cur_rabbit, dis);



    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int q;
    cin >> q;

    while(q--){
        int query;
        cin >> query;

        if(query == 100){
            init();
        }

        if(query == 200){
            start_round();
        }

        if(query == 300){

        }

        if(query == 400){

        }
    }

    return 0;
}