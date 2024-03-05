#include <iostream>

using namespace std;

#define MAX (1000000 + 10000)

int T;

typedef struct st1{
    int value; 
    int deleteFlag;
}DATA;

DATA dataA[MAX];
int dcnt;

typedef struct st2{
    int value;
    int dataIdx;
}HEAP;

HEAP minHeap[MAX];
int minHn;

HEAP maxHeap[MAX];
int maxHn;

HEAP maxPop(HEAP* heap, int& hn){
    HEAP tmp, ret;

    ret = heap[1];
    heap[1] = heap[hn];
    heap[hn--].value = 0x80000000;

    for(int i = 1; i * 2 <= hn;){
        if(heap[i].value > heap[i * 2].value && heap[i].value > heap[i * 2 + 1].value) break;
        else if(heap[i * 2].value > heap[i * 2 + 1].value){
            tmp = heap[i * 2];
            heap[i * 2] = heap[i];
            heap[i] = tmp;

            i = i * 2;
        }else{
            tmp = heap[i * 2 + 1];
            heap[i * 2 + 1] = heap[i];
            heap[i] = tmp;

            i = i * 2 + 1;
        }
    }
    return ret;
}

void maxPush(HEAP* heap, int& hn, HEAP x){
    HEAP tmp;

    heap[++hn] = x;

    for(int i = hn; i > 1; i /= 2){
        if(heap[i / 2].value > heap[i].value) break;

        tmp = heap[i / 2];
        heap[i / 2] = heap[i];
        heap[i] = tmp;
    }
}

HEAP minPop(HEAP* heap, int& hn){
    HEAP tmp, ret;

    ret = heap[1];
    heap[1] = heap[hn];
    heap[hn--].value = 0x7fffffff;

    for(int i = 1; i * 2 <= hn;){
        if(heap[i].value < heap[i * 2].value && heap[i].value < heap[i * 2 + 1].value) break;
        else if(heap[i * 2].value < heap[i * 2 + 1].value){
            tmp = heap[i * 2];
            heap[i * 2] = heap[i];
            heap[i] = tmp;

            i = i * 2;
        }else{
            tmp = heap[i * 2 + 1];
            heap[i * 2 + 1] = heap[i];
            heap[i] = tmp;

            i = i * 2 + 1;
        }
    }

    return ret;
}

void minPush(HEAP* heap, int& hn, HEAP x){
    HEAP tmp;

    heap[++hn] = x;

    for(int i = hn; i > 1; i /= 2){
        if(heap[i / 2].value < heap[i].value) break;

        tmp = heap[i / 2];
        heap[i / 2] = heap[i];
        heap[i] = tmp;
    }
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> T;

    for(int tc = 0; tc < T; tc++){
        int k, dataCount;

        cin >> k;

        dcnt = minHn = maxHn = dataCount = 0;

        for(int i = 0; i< k; i++){
            char command;
            int value;

            cin >> command >> value;

            if(command == 'I'){
                
                dataA[dcnt].value = value;
                dataA[dcnt].deleteFlag = 0;

                maxPush(maxHeap, maxHn, {value, dcnt});
                minPush(minHeap, minHn, {value, dcnt});

                dcnt++;
                dataCount++;

            }else{
                if(dataCount == 0){
                    maxHn = minHn = 0;
                    continue;
                }

                while(dataA[maxHeap[1].dataIdx].deleteFlag) maxPop(maxHeap, maxHn);
                while(dataA[minHeap[1].dataIdx].deleteFlag) minPop(minHeap, minHn);

                dataCount--;

                HEAP tmp;
                if(value == 1){
                    tmp = maxPop(maxHeap, maxHn);
                    dataA[tmp.dataIdx].deleteFlag = 1;
                }else{
                    tmp = minPop(minHeap, minHn);
                    dataA[tmp.dataIdx].deleteFlag = 1;
                }
            }
        }

        if(dataCount){
            while(dataA[maxHeap[1].dataIdx].deleteFlag) maxPop(maxHeap, maxHn);
            while(dataA[minHeap[1].dataIdx].deleteFlag) minPop(minHeap, minHn);

            HEAP maxValue = maxPop(maxHeap, maxHn);
            HEAP minValue = minPop(minHeap, minHn);

            cout<<maxValue.value<<" "<<minValue.value<<"\n";
        }else{
            cout<<"EMPTY\n";
        }
    }

    return 0;
}