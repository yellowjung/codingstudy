#include <iostream>
#include <unordered_map>

using namespace std;

struct BOX{
    int id;
    int weight;
    int belt_num;

    BOX* prev;
    BOX* next;

    BOX(){
        id = -1;
        weight = -1;
        belt_num = -1;
        prev = NULL;
        next = NULL;
    }
};

struct BELT{
    BOX* head;
    BOX* tail;
    bool is_broken;

    BELT(){
        head = new BOX;
        tail = new BOX;

        head->next = tail;
        tail->prev = head;

        is_broken = false;

        head->prev = NULL;
        tail->next = NULL;
    }
};

int q, n, m;
unordered_map<int, BOX*> box_map;
BOX box[100000];
BELT belt[100000];

bool empty(int belt_num){
    return (belt[belt_num].head->next == belt[belt_num].tail);
}

void push_back(int belt_num, BOX* box){
    box_map[box->id] = box;

    BOX* prev = belt[belt_num].tail -> prev;
    BOX* next = belt[belt_num].tail;

    box->prev = prev;
    box->next = next;

    prev->next = box;
    next->prev = box;
}

void q_100(){
    int id[1000000];
    int weight[1000000];
    int pos = 0;
    cin >> n >> m;

    for(int i = 0; i < n; i++){
        cin>>id[i];
    }

    for(int i = 0; i < n; i++){
        cin>>weight[i];
    }

    for(int belt_num = 0; belt_num < m; belt_num++){
        for(int j = 0; j < n/m; j++){
            box[pos].belt_num = belt_num;
            box[pos].weight = weight[pos];
            box[pos].id = id[pos];
            push_back(belt_num, &box[pos]);
            pos++;
        }
    }
}

void pop_front(int belt_num){
    if(empty(belt_num)){
        return;
    }

    BOX* item = belt[belt_num].head->next;
    BOX* next = item->next;
    BOX* head = belt[belt_num].head;

    head->next = next;
    next->prev = head;

    item->next = NULL;
    item->prev = NULL;

    box_map.erase(item->id);
}

int q_200(){
    int ret = 0;
    int w_max = 0;
    cin >> w_max;

    for(int belt_num = 0; belt_num < m; belt_num++){
        if(empty(belt_num) || belt[belt_num].is_broken){
            continue;
        }

        BOX* front = belt[belt_num].head -> next;
        if(front->weight <= w_max){
            ret += front->weight;
            pop_front(belt_num);
        }else{
            pop_front(belt_num);
            push_back(belt_num, front);
        }
    }

    return ret;
}

int q_300(){
    int id = 0;
    cin >> id;
    if(box_map.find(id) == box_map.end()){
        return -1;
    }

    BOX* item = box_map[id];
    BOX* prev = item->prev;
    BOX* next = item->next;

    prev->next = next;
    next->prev = prev;

    item->next = NULL;
    item->prev = NULL;

    box_map.erase(id);

    return id;
}

int q_400(){
    int id = 0;
    cin >> id;
    if(box_map.find(id) == box_map.end()){
        return -1;
    }

    BOX* item = box_map[id];
    BOX* prev = item->prev;
    BOX* begin = belt[item->belt_num].head->next;
    BOX* end = belt[item->belt_num].tail->prev;

    if(item != begin){
        item -> prev = belt[item->belt_num].head;
        belt[item->belt_num].head -> next = item;

        begin -> prev = end;
        end -> next = begin;

        prev -> next = belt[item->belt_num].tail;
        belt[item->belt_num].tail -> prev = prev;
    }
    return item->belt_num + 1;
}

int q_500(){
    int belt_num = 0;
    cin >> belt_num;
    belt_num--;

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
            it->belt_num = target;
        }

        prev->next = begin;
        begin->prev = prev;

        end->next = belt[target].tail;
        belt[target].tail -> prev = end;

        belt[belt_num].head->next = belt[belt_num].tail;
        belt[belt_num].tail->prev = belt[belt_num].head;
    }



    return belt_num + 1;
}

void solution(){
    cin >> q;
    while(q--){
        int cmd;
        cin >> cmd;
        switch (cmd)
        {
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
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    solution();
    return 0;
}