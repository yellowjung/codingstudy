#include <iostream>
#include <unordered_map>

using namespace std;

struct BOX{
    int idx;
    int weight;
    int belt;
    
    BOX* prev;
    BOX* next;

    BOX(){
        idx = -1;
        weight = -1;
        belt = -1;
        prev = NULL;
        next = NULL;
    }
};

struct BELT{
    BOX* head;
    BOX* tail;
    bool is_broken;
    BELT() {
        is_broken = false;
        head = new BOX();
        tail = new BOX();

        head->next = tail;
        tail->prev = head;

        head->prev = NULL;
        tail->next = NULL;
    }
};

int q, cmd, n, m;
unordered_map<int, BOX*> box_map;
BOX box[100000];
BELT belt[10];

bool empty(int belt_num){
    return (belt[belt_num].head -> next == belt[belt_num].tail);
}

void push_back(int belt_num, BOX* _box){
    box_map[_box->idx] = _box;

    BOX* prev = belt[belt_num].tail -> prev;
    BOX* next = belt[belt_num].tail;

    _box->prev = prev;
    _box->next = next;

    prev->next = _box;
    next->prev = _box;
}

void pop_front(int belt_num){
    if(empty(belt_num)){
        return;
    }

    BOX* item = belt[belt_num].head -> next;
    box_map.erase(item -> idx);
    BOX* prev = belt[belt_num].head;
    BOX* next = belt[belt_num].head -> next -> next;

    prev->next = next;
    next->prev = prev;

    item->prev = NULL;
    item->next = NULL;
}


void q_100(){
    cin >> n;
    cin >> m;

    int id[100000], w[100000];
    for(int i = 0; i < n; i++){
        cin >> id[i];
    }
    for(int i = 0 ; i < n; i++){
        cin >> w[i];
    }

    int pos = 0;
    for(int belt_num = 0; belt_num < m; belt_num++){
        for(int i = 0; i < n / m; i++){
            box[pos].idx = id[pos];
            box[pos].weight = w[pos];
            box[pos].belt = belt_num;
            push_back(belt_num, &box[pos]);
            pos++;
        }
    }
}

int q_200(){
    int ret = 0;
    int w;
    cin >> w;

    for(int i = 0; i < m; i++){
        if(empty(i) || belt[i].is_broken){
            continue;
        }

        BOX* front = belt[i].head -> next;
        if(front->weight <= w){
            ret += front->weight;
            pop_front(i);
        }else{
            pop_front(i);
            push_back(i, front);
        }
    }
    return ret;
}

int q_300(){
    int id;
    cin >> id;
    if(box_map.find(id) == box_map.end()){
        return -1;
    }

    BOX* item = box_map[id];
    BOX* prev = item->prev;
    BOX* next = item->next;

    prev->next = next;
    next->prev = prev;

    item->prev = NULL;
    item->next = NULL;

    box_map.erase(id);
    return id;
}

int q_400(){
    int id;
    cin >> id;
    if(box_map.find(id) == box_map.end()){
        return -1;
    }

    BOX* item = box_map[id];
    BOX* prev = item->prev;
    BOX* begin = belt[item->belt].head->next;
    BOX* end = belt[item->belt].tail->prev;

    if(item != begin){
        item->prev = belt[item->belt].head;
        belt[item->belt].head->next = item;

        begin->prev = end;
        end->next = begin;

        prev->next = belt[item->belt].tail;
        belt[item->belt].tail->prev = prev;
    }
    return item->belt + 1;
}

int q_500(){
    int belt_num;
    cin >> belt_num;
    --belt_num;

    if(belt[belt_num].is_broken){
        return -1;
    }

    belt[belt_num].is_broken = true;
    if(!empty(belt_num)){
        int target = (belt_num + 1) % m;
        while(belt[target].is_broken){
            target = (target + 1) % m;
        }

        BOX* prev = belt[target].tail->prev;
        BOX* begin = belt[belt_num].head->next;
        BOX* end = belt[belt_num].tail->prev;

        for(auto it = begin; it != belt[belt_num].tail; it = it->next){
            it->belt = target;
        }

        prev->next = begin;
        begin->prev = prev;

        end->next = belt[target].tail;
        belt[target].tail->prev = end;

        belt[belt_num].head->next = belt[belt_num].tail;
        belt[belt_num].tail->prev = belt[belt_num].head;
    }

    return belt_num + 1;
}

int main() {
    // 여기에 코드를 작성해주세요.

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> q;
    while(q--){
        cin >> cmd;
        switch(cmd){
            case 100:
                q_100();
                break;
            case 200:
                cout<<q_200()<<"\n";
                break;
            case 300:
                cout<<q_300()<<"\n";
                break;
            case 400:
                cout<<q_400()<<"\n";
                break;
            case 500:
                cout<<q_500()<<"\n";
                break;
        }
    }

    return 0;
}