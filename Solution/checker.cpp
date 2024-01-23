#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <string>
using namespace std;

#define INF 1987654321
#define MAX_N 50000
#define MAX_D 300

int q;
int n;
int cnt;
int ans;

int s[MAX_D + 1];
int g[MAX_D + 1];
int e[MAX_D + 1];
int judging_domain[MAX_N + 1];

struct Url{
    int tme, id;
    int num;

    bool operator <(const Url &b) const{
        if(id != b.id) return id > b.id;
        return tme > b.tme;
    }
};

priority_queue<int, vector<int>, greater<int>> rest_judger;
priority_queue<Url> url_pq[MAX_D + 1];
map<string, int> domainToIdx;
set<int> is_in_readyq[MAX_D + 1];

void input(){
    cin >> q;
}

void q_100(){
    string url;
    cin >> n >> url;

    for(int i = 1; i <= n; i++){
        rest_judger.push(i);
    }

    int idx = 0;
    for(int i = 0; i < url.length(); i++){
        if(url[i] == '/') {
            idx = i;
        }
    }

    string domain = url.substr(0, idx);
    int num = stoi(url.substr(idx + 1));

    if(!domainToIdx[domain]){
        cnt++;
        domainToIdx[domain] = cnt;
    }

    int domain_idx = domainToIdx[domain];

    is_in_readyq[domain_idx].insert(num);
    

    Url newUrl;
    newUrl.tme = 0;
    newUrl.id = 1;
    newUrl.num = num;
    url_pq[domain_idx].push(newUrl);

    ans++;
}

void q_200(){
    int tme, id;
    string url;
    cin >> tme >> id >> url;

    int idx = 0;
    for(int i = 0; i < url.length(); i++){
        if(url[i] == '/') idx = i;
    }

    string domain = url.substr(0, idx);
    int num = stoi(url.substr(idx + 1));

    if(!domainToIdx[domain]){
        cnt++;
        domainToIdx[domain] = cnt;
    }

    int domain_idx = domainToIdx[domain];

    if(is_in_readyq[domain_idx].find(num) != is_in_readyq[domain_idx].end()){
        return;
    }

    is_in_readyq[domain_idx].insert(num);

    Url newUrl;
    newUrl.tme = tme;
    newUrl.id = id;
    newUrl.num = num;
    url_pq[domain_idx].push(newUrl);

    ans++;    
}

void q_300(){
    int tme;
    cin >> tme;

    if(rest_judger.empty()) return;

    int min_domain = 0;
    Url minUrl;
    minUrl.id = INF;

    for(int i = 1; i <= cnt; i++){
        
        if(e[i] > tme) continue;

        if(!url_pq[i].empty()){
            Url curUrl = url_pq[i].top();

            if(minUrl < curUrl){
                minUrl = curUrl;
                min_domain = i;
            }
        }
    }

    if(min_domain){
        int juger_idx = rest_judger.top(); rest_judger.pop();

        url_pq[min_domain].pop();

        s[min_domain] = tme;
        e[min_domain] = INF;

        judging_domain[juger_idx] = min_domain;

        is_in_readyq[min_domain].erase(is_in_readyq[min_domain].find(minUrl.num));

        ans--;
    }

}

void q_400(){
    int tme, id;
    cin >> tme >> id;

    if(judging_domain[id] == 0) return;

    rest_judger.push(id);
    int domain_idx = judging_domain[id];
    judging_domain[id] = 0;

    g[domain_idx] = tme - s[domain_idx];
    e[domain_idx] = s[domain_idx] + 3 * g[domain_idx];
}

void q_500(){
    int tme;
    cin >> tme;

    cout << ans <<"\n";
}

void solve(){
    while(q--){
        int cmd;
        cin >> cmd;

        if(cmd == 100){
            q_100();
        }
        if(cmd == 200){
            q_200();
        }
        if(cmd == 300){
           q_300(); 
        }
        if(cmd == 400){
            q_400();
        }
        if(cmd == 500){
            q_500();
        }
    }
}

void solution(){
    input();
    solve();
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solution();

    return 0;
}