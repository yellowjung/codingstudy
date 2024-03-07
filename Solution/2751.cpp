#include <iostream>

using namespace std;

int N;

int a[1000000 + 500000];
int b[1000000 + 500000];

void merge(int start, int end){
    int mid, i, j, k;

    mid = (start + end) >> 1;
    i = start;
    j = mid + 1;
    k = 0;

    while(i <= mid && j <= end){
        if(a[i] <= a[j]){
            b[k++] = a[i++];
        }else{
            b[k++] = a[j++];
        }
    }

    while(i <= mid) b[k++] = a[i++];
    while(j <= end) b[k++] = a[j++];

    for(int i = start; i <= end; i++){
        a[i] = b[i - start];
    }
}

void sort(int start, int end){
    int mid;
    if(start >= end) return;

    mid = (start + end) >> 1;

    sort(start, mid);
    sort(mid + 1, end);
    merge(start, end);
}

int main(){

    cin >> N;

    for(int i = 0; i < N; i++){
        cin >> a[i];
    }

    sort(0, N - 1);

    for(int i = 0; i < N; i++){
        cout << a[i] <<"\n";
    }

    return 0;
}