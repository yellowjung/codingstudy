#include <iostream>

using namespace std;

int N;
int heap[100100];
int hn;

void push(int* heap, int& hn, int x){
    register int tmp;

    heap[++hn] = x;
    for(register int i = hn; i > 1; i /= 2){
        if(heap[i / 2] <= heap[i]) break;

        tmp = heap[i / 2];
        heap[i / 2] = heap[i];
        heap[i] = tmp;
    }
}

int pop(int* heap, int& hn){
    register int tmp, ret;
    
    ret = heap[1];
    heap[1] = heap[hn];
    heap[hn--] = 0x7fff0000;

    for(register int i = 1; i * 2 <= hn;){
        if(heap[i] < heap[i * 2] && heap[i] < heap[i * 2 + 1]) break;
        else if(heap[i * 2] < heap[i * 2 + 1]){
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

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for(int i = 0; i < N; i++){
        int x; 

        cin >> x;
        if(x){
            push(heap, hn, x);
        }else{
            if(hn){
                cout << pop(heap, hn)<<"\n";
            }else{
                cout<<"0\n";
            }
        }
    }
    return 0;
}