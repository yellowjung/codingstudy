#include <iostream>

#define MAX_TABLE (1000003)
using namespace std;

typedef unsigned long long int ull;

int N;

typedef struct st{
    char name[6];
    int in;
}DB;

DB dbList[1001000];
DB enterList[1001000];

typedef struct st2{
    DB *db;
    struct st2 *next;
}HASH;

HASH Hash[MAX_TABLE];
HASH POOL[MAX_TABLE];
int pcnt;

ull HAsh(const char *str){
    ull HAsh = 5381;
    int c;

    while(c = *str++){
        HAsh = (((HAsh << 5) + HAsh) + c ) % MAX_TABLE;
    }

    return HAsh % MAX_TABLE;
}

void mystrcpy(char *a, char *b){
    while(*a++ = *b++);
}

int mystrcmp(const char *a, const char *b){
    while(*a && *a == *b) ++a, ++b;
    return *a - *b;
}

DB b[1000100];

void merge(int start, int end){
    int mid, i, j, k;

    mid = (start + end) >> 1;
    i = start;
    j = mid + 1;
    k = 0;

    while(i <= mid && j <= end){
        if(mystrcmp(enterList[i].name, enterList[j].name) > 0){
            b[k++] = enterList[i++];
        }else{
            b[k++] = enterList[j++];
        }
    }
    while (i <= mid) b[k++] = enterList[i++];
	while (j <= end) b[k++] = enterList[j++];
	for (i = start; i <= end; i++)
		enterList[i] = b[i - start];
}

void sort(int start, int end){
    int mid;
    if(start == end) return;

    mid = (start + end) >> 1;
    sort(start, mid);
    sort(mid + 1, end);
    merge(start, end);
}

int main(){

    int count, inCnt;
    char name[6], cmd[6];

    cin >> N;

    count = 0;

    for(int i = 0; i < N; i++){
        cin >> name >> cmd;
        if(!mystrcmp(cmd, (char*)"enter")){
            mystrcpy(dbList[count].name, name);
            dbList[count].in = 1;

            ull h = HAsh(name);

            HASH *nd = &POOL[pcnt++];
            nd->db = &dbList[count];

            nd->next = Hash[h].next;
            Hash[h].next = nd;

            count++;
        }else{
            ull h = HAsh(name);

            HASH *nd = Hash[h].next;

            while(nd){
                if(!mystrcmp(nd->db->name, name) && nd->db->in){
                    nd->db->in = 0;
                    break;
                }
                nd = nd->next;
            }
        }
    }

    inCnt = 0;
    for(int i = 0; i < pcnt; i++){
        if(dbList[i].in) enterList[inCnt++] = dbList[i];
    }

    sort(0, inCnt);

    for(int i =0; i < inCnt; i++){
        cout << enterList[i].name <<"\n";
    }

    return 0;
}