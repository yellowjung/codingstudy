#include <iostream>
#include <algorithm>
#define MAX 110

using namespace std;

int N, K;
int Weight[MAX];
int Value[MAX];
int DP[MAX][100010];

void Solution(){
	for(int i = 1; i <= N; i++){
		for(int j = 1; j <= K; j++){
			if(j >= Weight[i]){
				DP[i][j] = max(DP[i-1][j], DP[i-1][j-Weight[i]] + Value[i]);
			}else{
				DP[i][j] = DP[i - 1][j];
			}
		}
	}
	cout<<DP[N][K]<<endl;
}


void Input(){
	cin >> N >> K;
	for(int i = 1; i <= N; i++){
		cin >> Weight[i] >> Value[i];
	}
}

void Solve(){
	Input();
	Solution();
}


int main(){

	ios::sync_with_stdio(0);
	cin.tie(NULL);
	cout.tie(NULL);

	Solve();

	return 0;

}
