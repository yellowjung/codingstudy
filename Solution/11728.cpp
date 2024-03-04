#include <iostream>

using namespace std;

int a[1000100];
int b[1000100];

int N, M;

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;

    for(int i = 0; i < N; i ++){
        cin >> a[i];
    }

    for(int i = 0; i < M; i++){
        cin >> b[i];
    }

    int i = 0, j = 0;

    while(i < N && j < M){
        if(a[i] <= b[j]){
            cout << a[i++]<<" ";
        }else{
            cout << b[j++]<<" ";
        }
    }

    while(i < N){
        cout<<a[i++]<<" ";
    }

    while(j < M){
        cout<<b[j++]<<" ";
    }

    return 0;
}