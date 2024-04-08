#include <iostream>
#include <unordered_map>

using namespace std;

struct BOX{
    int id;
    int weight;
    int belt_num;

    BOX* next;
    BOX* prev;

    BOX(){
        id = -1;
        weight = -1;
        belt_num = -1;
        next = NULL;
        prev = NULL;
    }
};

struct BELT{
    bool is_broken;
    BOX* head;
    BOX* tail;

    BELT(){
        head = new BOX();
        tail = new BOX();
        is_broken = false;
        head -> next = tail;
        tail -> prev = head;

        head -> prev = NULL;
        tail -> next = NULL;
    }
};

unordered_map<int, BOX*> box_map;
BOX box[1000000];
BELT belt[10];
int q, n, m;

bool empty(int belt_num){
    return (belt[belt_num].head->next == belt[belt_num].tail);
}

void push_back(int belt_num, BOX* item){
    box_map[item->id] = item;
    BOX* prev = belt[belt_num].tail->prev;
    BOX* next = belt[belt_num].tail;

    item->prev = prev;
    item->next = next;

    prev->next = item;
    next->prev = item;

}

void pop_front(int belt_num){
    if(empty(belt_num)){
        return;
    }

    BOX* item = belt[belt_num].head->next;
    box_map.erase(item->id);

    BOX* prev = belt[belt_num].head;
    BOX* next = belt[belt_num].head->next->next;

    prev->next = next;
    next->prev = prev;

    item->next = NULL;
    item->prev = NULL;
}

void q_100(){
    int pos = 0;
    int id[1000000];
    int weight[1000000];

    cin >> n >> m;
    for(int i = 0; i < n; i++){
        cin >> id[i];
    }

    for(int i = 0; i < n; i++){
        cin >> weight[i];
    }

    for(int belt_num = 0; belt_num < m; belt_num++){
        for(int i = 0; i < n / m; i++){
            box[pos].id = id[pos];
            box[pos].weight = weight[pos];
            box[pos].belt_num = belt_num;
            push_back(belt_num, &box[pos]);
            pos++;
        }
    }

}

void show_belt(){
    for(int belt_num = 0; belt_num < m; belt_num++){
        cout<<belt_num<<"\n";
        BOX* item = belt[belt_num].head -> next;
        while(item->next != NULL){
            cout<<item->id<<" ";
            item = item->next;
        }
        cout<<"\n";
    }
}

int q_200(){
    int w_max, answer = 0;
    cin>>w_max;
    for(int i = 0; i < m; i++){
        if(belt[i].is_broken || empty(i)) continue;
        BOX* front = belt[i].head->next;
        if(front -> weight <= w_max){
            answer += front -> weight;
            pop_front(i);
        }else{
            pop_front(i);
            push_back(i, front);
        }
    }
    return answer;
}

int q_300(){
    int r_id = 0;
    cin>>r_id;
    if(box_map.find(r_id) == box_map.end()){
        return -1;
    }

    BOX* item = box_map[r_id];
    int belt_num = item->belt_num;
    box_map.erase(r_id);

    BOX* prev = item->prev;
    BOX* next = item->next;

    prev->next = next;
    next->prev = prev;

    item->next = NULL;
    item->prev = NULL;

    return r_id;
}

int q_500(){
    int b_num;
    cin >> b_num;
    b_num--;
    if(belt[b_num].is_broken) return -1;

    belt[b_num].is_broken = true;
    if(!empty(b_num)){
        int target = (b_num + 1) % m;
        while(belt[target].is_broken){
            target = (target + 1) % m;
        }

        BOX* prev = belt[target].tail -> prev;
        BOX* begin = belt[b_num].head -> next;
        BOX* end = belt[b_num].tail -> prev;

        for(auto it = begin; it != belt[b_num].tail; it = it->next){
            it->belt_num = target;
        }

        begin -> prev = prev;
        prev -> next = begin;

        end -> next = belt[target].tail;
        belt[target].tail -> prev = end;

        belt[b_num].head -> next = belt[b_num].tail;
        belt[b_num].tail -> prev = belt[b_num].head;

    }
    return b_num + 1;
}

int q_400(){
    int f_id;
    cin >> f_id;
    if(box_map.find(f_id) == box_map.end()){
        return -1;
    }

    BOX* item = box_map[f_id];

    int belt_num = item->belt_num;

    BOX* prev = item->prev;
    BOX* begin = belt[item->belt_num].head -> next;
    BOX* end = belt[item->belt_num].tail -> prev;

    if (item != begin){
        item -> prev = belt[item->belt_num].head;
        belt[item->belt_num].head->next = item;

        begin->prev = end;
        end->next = begin;

        prev->next = belt[item->belt_num].tail;
        belt[item->belt_num].tail -> prev = prev;

    }

    return belt_num + 1;
}

void solve(){
    cin >> q;
    while(q--){
        int cmd;
        cin >> cmd;
        switch(cmd){
            case 100:
                q_100();
                break;
            case 200:
                cout << q_200() << "\n";
                break;
            case 300:
                cout << q_300() << "\n";
                break;
            case 400:
                cout << q_400() << "\n";
                break;
            case 500:
                cout << q_500() << "\n";
                break;
            // default:
            //     show_belt();
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();

    return 0;
}