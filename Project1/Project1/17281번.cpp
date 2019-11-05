//https://artjjong.tistory.com/8
//17281¹ø
#include <stdio.h>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int n;
int player[51][10];
bool check[10];
int save_num[9];
int player_tmp[10];
int ret = -987654321;
int ans = 0;
int out_cnt;
bool nex;
int s[4];
void run() {
	int start = 1; ans = 0;
	for (int a = 1; a <= n; a++) {
		out_cnt = 0; nex = false;
		while (1) {
			for (int i = start; i <= 9; i++) {
				int ss = player[a][player_tmp[i]];
				if (ss == 0) {
					out_cnt++;
				}
				if (ss == 1) {
					if (s[3] == 1) {
						s[3] = 0;
						ans++;
					}
					for (int ss = 3; ss > 1; ss--) {
						if (s[ss - 1] != 0) {
							s[ss] = 1;
							s[ss - 1] = 0;
						}
					}
					s[1] = 1;
				}
				if (ss == 2) {
					if (s[3] == 1) {
						s[3] = 0;
						ans++;
					}
					if (s[2] == 1) {
						s[2] = 0;
						ans++;
					}
					if (s[1] == 1) {
						s[1] = 0;
						s[3] = 1;
					}
					s[2] = 1;
				}
				if (ss == 3) {
					for (int j = 1; j <= 3; j++) {
						if (s[j] == 1) {
							s[j] = 0;
							ans++;
						}
					}
					s[3] = 1;
				}
				if (ss == 4) {
					for (int j = 1; j <= 3; j++) {
						if (s[j] == 1) {
							s[j] = 0;
							ans++;
						}
					}
					ans++;
				}
				if (out_cnt == 3) {
					if (i + 1 == 10) {
						start = 1;
					}
					else {
						start = i + 1;
					}
					for (int j = 1; j <= 3; j++) {
						s[j] = 0;
					}
					nex = true;
					break;
				}
			}
			if (nex) break;
			start = 1;
		}
	}
	
}


void func() {
	do {
		/*for (int loop = 0; loop < 8; loop++) {
			cout << save_num[loop]<<" ";
		}
		cout<<"\n";*/
		int cnt = 1;
		for (int loop = 0; loop < 8; loop++) {
			if (cnt != 4) {
				player_tmp[cnt] = save_num[loop];
			}
			else {
				cnt++;
				player_tmp[cnt] = save_num[loop];
			}
			cnt++;
		}
		run();
		ret = max(ret, ans);
	} while (next_permutation(save_num, save_num + 8));
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= 9; j++) {
			scanf("%d", &player[i][j]);
		}
	}
	
	for (int i = 0; i < 8; i++) {
		save_num[i] = i + 2;
	}

	player_tmp[4] = 1;
	func();
	cout << ret << "\n";
}