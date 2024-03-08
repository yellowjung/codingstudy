#include <iostream>

using namespace std;

#define MAX (28 + 10)

int T, N, K;
int decimal[MAX];
int dcnt;

int makeDecimal(char* ptr, int size){
    int sum, mul;

    sum = 0; mul = 1;
    for(int i = size - 1; i >= 0; i--){
        if(ptr[i] >= 'A'){
            sum += (ptr[i] - 'A' + 10) * mul;
        }else{
            sum += (ptr[i] - '0') * mul;
        }

        mul *= 16;
    }

    return sum;
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> T;
    for(int tc = 1; tc <= T; tc++){
        dcnt = 0;
        
        char number[MAX];

        cin >> N >> K >> number;

        for(int i = 0; i < N / 4; i++){
            number[N + i] = number[i];
        }

        number[N + N / 4] = 0;

        for(int i = 0; i < N; i++){
            decimal[dcnt++] = makeDecimal(number + i, N / 4);
        }
        
        for(int i = 0; i < dcnt - 1; i++){
            for(int k = i + 1; k < dcnt; k++){
                if(decimal[i] < decimal[k]){
                    int tmp = decimal[i];
                    decimal[i] = decimal[k];
                    decimal[k] = tmp;
                }
            }
        }

        int uniqueList[MAX] = {0 };
        int ucnt = 0;

        uniqueList[ucnt++] = decimal[0];
        for(int i = 1; i < dcnt; i++){
            if(decimal[i] == uniqueList[ucnt - 1]){
                continue;
            }

            uniqueList[ucnt++] = decimal[i];
        }

        cout<<"#"<<tc<<" "<<uniqueList[K - 1]<<"\n";
    }
    
    return 0;

}