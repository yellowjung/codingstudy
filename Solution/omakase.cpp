#include <iostream>
#include <vector>
#include <set>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

int L, Q;

struct Query{
    int cmd;
    int t, x;
    string name;
    int n;
};

bool cmp(Query A1, Query B1){
    if(A1.t != B1.t){
        return A1.t < B1.t;
    }
    return A1.cmd < B1.cmd;
}

vector<Query> queries;

set<string> names;

map<string, vector<Query>> p_queries;

map<string ,int> entry_time;
map<string, int> position;
map<string, int> exit_time;

int main(){

    cin >> L >> Q;
    for(int i = 0; i < Q; i++){
        int cmd = -1;
        int t = -1, x = -1, n = -1;
        string name;
        cin >> cmd;
        if(cmd == 100){
            cin >> t >> x >> name;
        }else if(cmd == 200){
            cin >> t >> x >> name >> n;
        }else{
            cin >> t;
        }

        queries.push_back(Query{cmd, t, x, name, n});

        if(cmd == 100){
            p_queries[name].push_back(Query{cmd, t, x, name, n});
        }else if(cmd == 200){
            names.insert(name);
            entry_time[name] = t;
            position[name] = x; 
        }
    }

    for(string name : names){
        exit_time[name] = 0; 

        for(Query q: p_queries[name]){
            int time_to_remove = 0;
            if(q.t < entry_time[name]){
                int t_sushi_x = (q.x + (entry_time[name] - q.t)) % L;
                int additional_time = (position[name] - t_sushi_x + L) % L;

                time_to_remove = entry_time[name] + additional_time;
            }else{
                int additional_time = (position[name] - q.x + L) % L;
                time_to_remove = q.t + additional_time;
            }
            exit_time[name] = max(exit_time[name], time_to_remove);
            queries.push_back(Query{111, time_to_remove, -1, name, -1});
        }
    }

    for(string name: names){
        queries.push_back(Query{222, exit_time[name], -1, name, -1});
    }

    sort(queries.begin(), queries.end(), cmp);

    int people_num = 0, sushi_num = 0;

    for(int i = 0; i < (int) queries.size(); i++){
        if(queries[i].cmd == 100){
            sushi_num++;
        }else if(queries[i].cmd == 111){
            sushi_num--;
        }else if(queries[i].cmd == 200){
            people_num++;
        }else if(queries[i].cmd == 222){
            people_num--;
        }else{
            cout << people_num << " "<< sushi_num <<"\n";
        }
    }
    return 0;
}