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
    for(int i = 0; i < m; i++){
        head[i] = ids[i * size];
        tail[i] = ids[(i + 1) * size -1];
        for(int j = i * size; j < (i + 1) * size; j++){
            belt_num[ids[j]] = i + 1;

            if(j < (i + 1) * size - 1){
                nxt[ids[j]] = ids[j + 1];
                prv[ids[j + 1]] = ids[j];
            }
        }
    }
}

void RemoveId(int id, bool remove_belt){
    int b_num = belt_num[id] - 1;

    if(remove_belt){
        belt_num[id] = 0;
    }

    if(head[b_num] == tail[b_num]){
        head[b_num] = tail[b_num] = 0;
    }else if(id == head[b_num]){
        int nid = nxt[id];
        head[b_num] = nid;
        prv[nid] = 0;
    }else if(id == tail[b_num]){
        int pid = prv[id];
        tail[b_num] = pid;
        nxt[pid] = 0;
    }else{
        int pid = prv[id], nid = nxt[id];
        nxt[pid] = nid;
        prv[nid] = pid;
    }

    nxt[id] = prv[id] = 0;
}

void PushId(int target_id, int id){
    nxt[target_id] = id;
    prv[id] = target_id;

    int b_num = belt_num[target_id] - 1;
    if(tail[b_num] == target_id){
        tail[b_num] = id;
    }
}

void DropOff(){
    int w_max;
    cin >> w_max;

    int w_sum = 0;
    for(int i = 0; i < m; i++){
        if(broken[i]){
            continue;
        }

        if(head[i] != 0){
            int id = head[i];
            int w= weight[id];

            if(w <= w_max){
                w_sum += w;

                RemoveId(id, true);
            }else if(nxt[id] != 0){
                RemoveId(id, false);

                PushId(tail[i], id);
            }
        }
    }
    cout << w_sum <<"\n";
}

void Remove(){
    int r_id;
    cin >> r_id;

    if(belt_num[r_id] == 0){
        cout << -1 << "\n";
        return;
    }

    RemoveId(r_id, true);
    cout<< r_id <<"\n";
}

void Find(){
    int f_id;
    cin >> f_id;

    if(belt_num[f_id] == 0){
        cout << -1 << "\n";
        return;
    }

    int b_num = belt_num[f_id] - 1;
    if(head[b_num != f_id]){
        int orig_tail = tail[b_num];
        int orig_head = head[b_num];

        int now_tail = prv[f_id];
        tail[b_num] = now_tail;
        nxt[now_tail] = 0;

        nxt[orig_tail] = orig_head;
        prv[orig_head] = orig_tail;

        head[b_num] = f_id;
    }

    cout << b_num + 1 << "\n";
}

void BrokenBelt(){
    int b_num;
    cin >> b_num;

    b_num--;

    if(broken[b_num]){
        cout << -1 <<"\n";
        return;
    }

    broken[b_num] = 1;

    if(head[b_num] == 0){
        cout << b_num + 1<<"\n";
        return;
    }

    int nxt_num = b_num;
    while(true){
        nxt_num = (nxt_num + 1) % m;
        if(!broken[nxt_num]){
            if(tail[nxt_num] == 0){
                head[nxt_num] = head[b_num];
                tail[nxt_num] = tail[b_num];
            }else{
                PushId(tail[nxt_num], head[b_num]);
                tail[nxt_num] = tail[b_num];
            } 

            int id = head[b_num];
            while(id != 0){
                belt_num[id] = nxt_num + 1;
                id = nxt[id];
            }

            head[b_num] = tail[b_num] = 0;
            break;
        }
    }
    cout<< b_num + 1<< "\n";
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
        }else if(q_type == 200){
            DropOff();
        }else if(q_type == 300){
            Remove();
        }else if(q_type == 400){
            Find();
        }else{
            BrokenBelt();
        }
    }


    return 0;
}