#define N 4

typedef struct {
    int strike;
    int ball;
} Result;

// API
extern Result query(int guess[]);

typedef struct st{
    int g[4];
    struct st *next;
}NODE;

NODE HEAD;
NODE POOL[10000];
int pcnt;

int visit[10];
int list[4];

void DFS(int L){
    if(L > 3){

        NODE *nd = &POOL[pcnt++];

        for(int k = 0; k < 4; k++){
            nd->g[k] = list[k];
        }

        nd->next = HEAD.next;
        HEAD.next = nd;

        return;
    }

    for(int i = 0; i < 10; i++){
        if(visit[i]) continue;

        list[L] = i;
        
        visit[i] = 1;
        DFS(L + 1);
        visit[i] = 0;
    }
}

Result query2(int guess[], int nd[]){
    Result result;
    int check[10] = {0};

    result.strike = 0;
    result.ball = 0;

    for(int i = 0; i < 4; i++) check[guess[i]]++;

    for(int idx = 0; idx < N; idx++){
        if(guess[idx] == nd[idx]){
            result.strike++;
        }else if(check[nd[idx]] > 0){
            result.ball++;
        }
    }
    return result;
}

void deleteNode(int stk, int ball, int guess[]){
    NODE *nd = &HEAD;

    while(nd -> next){
        Result result;
        int tmpstk, tmpball;

        result = query2(guess, nd->next->g);
        tmpstk = result.strike;
        tmpball = result.ball;

        if(!(tmpstk == stk && tmpball == ball)){
            nd -> next = nd -> next -> next;
        }else{
            nd = nd -> next;
        }
    }
}

void doUserImplementation(int guess[]) {
    Result result;

    pcnt = 0;
    HEAD.next = 0;
    DFS(0);

    while(1){
        int stk, ball;

        for(int i = 0; i < 4; i ++){
            guess[i] = HEAD.next -> g[i];
        }

        HEAD.next = HEAD.next->next;

        result = query(guess);
        stk = result.strike;
        ball = result.ball;

        if(stk == 4) break;

        deleteNode(stk, ball, guess);
    }
}
