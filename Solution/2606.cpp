#include <iostream>
using namespace std;

typedef struct st{
    int node;
    struct st *next;
}NODE;

int pcnt = 0;
NODE HEAD[10000];
NODE POOL[110 * 110];

int VISIT[110];
int ANSWER = 0, N, M;

void init(int n){
    pcnt = 0;
    for(int i = 1; i <= n; i++){
        HEAD[i].next = 0;
        VISIT[i] = 0;
    }
    ANSWER = 0;
}

void Make(int p, int c){
    NODE *nd = &POOL[pcnt++];

    nd->node = c;

    nd->next = HEAD[p].next;
    HEAD[p].next = nd;
}

int queue[110 * 110];
int wp,rp;

void BFS(){
    int out;
    wp = rp = 0;

    queue[wp++] = 1;
    VISIT[1] = 1;

    while(wp > rp){
        out = queue[rp++];

        for(NODE *p = HEAD[out].next; p; p = p ->next){
            if(VISIT[p->node] == 0){
                VISIT[p->node] = 1;
                ANSWER++;
                queue[wp++] = p->node;
            }
        }
    }
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;

    init(N);

    for(int i = 0; i < M; i++){
        int p, c;
        cin >> p >> c;

        Make(p, c);
        Make(c, p);
    }

    BFS();

    cout<<ANSWER<<"\n";

    return 0;
}