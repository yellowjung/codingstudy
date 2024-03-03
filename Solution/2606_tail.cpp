#include <iostream>

using namespace std;

int N, M, ANSWER;

typedef struct st{
    int node;
    struct st *next;
}NODE;

NODE HEAD[110];
NODE TAIL[100];
NODE POOL[110 * 110];
int pcnt;

int visit[110];

void init(int n){
    pcnt = 0;
    for(int i = 1; i <= N; i++) HEAD[i].next = 0;
    for(int i = 1; i <= N; i++) TAIL[i].next = 0;
    for(int i = 1; i <= N; i++) visit[i] = 0;

    ANSWER = 0;
}

void Make(int p, int c){
    NODE *nd = &POOL[pcnt++];
    nd -> node = c;

    if(HEAD[p].next == NULL && TAIL[p].next == NULL){
        HEAD[p].next = TAIL[p].next = nd;
    }else{
        TAIL[p].next -> next = nd;
        TAIL[p].next = nd;
    }
}

int queue[110 * 110];
int wp, rp;

void BFS(){
    int out;

    wp = rp = 0;

    queue[wp++] = 1;
    visit[1] = 1;

    while(wp > rp){
        out = queue[rp++];
        for(NODE *p = HEAD[out].next; p; p = p -> next){
            if(visit[p->node] == 0){
                visit[p->node] = 1;
                ANSWER++;
                queue[wp++] = p->node;
            }
        }

    }
}

int main(){

    	scanf("%d %d", &N, &M);

	init(N); /* B형 tc가 여러 개인 경우 대비 */

	for (int i = 0; i < M; i++)
	{
		int p, c;
		scanf("%d %d", &p, &c);

		Make(p, c);
		Make(c, p);
	}

	//for (int i = 1; i <= N; i++) outputHead(i);

	BFS();

	printf("%d\n", ANSWER);

	return 0;

    return 0;
}