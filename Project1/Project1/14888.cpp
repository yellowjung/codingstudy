#include <stdio.h>
#include <iostream>
#include <queue>
#include <deque>
#include <algorithm>
using namespace std;

int n;
int number[100];
int cal[4];
int cal_count = 0;
int save[100];
int max_ans = -987654321;
int min_ans = 987654321;

void func(int num, int cnt) {
	if (cnt == n - 1) {
		max_ans = max(max_ans, num);
		min_ans = min(min_ans, num);

		return;
	}



	for (int loop = 0; loop < 4; loop++) {
		if (cal[loop] != 0) {
			cal[loop]--;
			if (loop == 0) {
				func(num + number[cnt + 1], cnt + 1);
			}
			else if(loop == 1){
				func(num - number[cnt + 1], cnt + 1);
			}
			else if (loop == 2) {
				func(num * number[cnt + 1], cnt + 1);
			}
			else if (loop == 3) {
				func(num / number[cnt + 1], cnt + 1);
			}
			cal[loop]++;
		}
	}
}


int main() {
	scanf("%d", &n);
	for (int loop = 0; loop < n; loop++) {
		scanf("%d", &number[loop]);
	}
	for (int loop = 0; loop < 4; loop++) {
		scanf("%d", &cal[loop]);
	}

	func(number[0], 0);
	cout << max_ans << "\n" << min_ans << "\n";
	return 0;
}