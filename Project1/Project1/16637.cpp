//https://yabmoons.tistory.com/201
//https://s0j0s.tistory.com/2
#include <stdio.h>
#include <queue>
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

int d;
string s;
int A[10], B[10], chk[10], MAX = -123456789, a;

void func(int cnt) {
	int sum = 0;
	for (int i = 0; i < a; i++) {
		int x = i, tmp = A[i];
		if (chk[i]) {
			if (B[i] == '+') {
				tmp += A[i + 1];
			}
			else if (B[i] == '-') {
				tmp -= A[i + 1];
			}
			else if (B[i] == '*') {
				tmp *= A[i + 1];
			}
			i++;
		}
		if (!x) { 
			sum = tmp; 
		}else {
			if (B[x - 1] == '+') { 
				sum += tmp; 
			}
			else if (B[x - 1] == '-') {
				sum -= tmp;
			}
			else if (B[x - 1] == '*') {
				sum *= tmp;
			}
		}
	}
	MAX = max(sum, MAX);

	for (int i = 0; i < a - 1; i++) {
		if (chk[i] || chk[i + 1]) continue;
		chk[i] = chk[i + 1] = 1;
		func(cnt + 2);
		chk[i] = chk[i + 1] = 0;
	}
}


int main() {
	scanf("%d", &d);
	cin >> s;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] >= '0' && s[i] <= '9') {
			A[a++] = s[i] - '0';
		}
		else {
			B[a - 1] = s[i];
		}
	}

	func(0);
	printf("%d\n", MAX);
	return 0;
}