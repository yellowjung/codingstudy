//https://donggod.tistory.com/21
//#include<iostream>
//#include <stdio.h>
//#include <queue>
//#include <algorithm>
//using namespace std;
//
//int day[16];
//int pay[16];
//
//int n, ret = -987654321;
//
//void func(int now_day, int now_sum, int added_num) {
//	if (now_day == n + 1) {
//		cout << "now sum : " << now_sum << "\n";
//		ret = max(ret, now_sum);
//		return;
//	}
//	else if (now_day > n + 1) {
//		cout << "now_sum - added_num : " << now_sum - added_num << "\n";
//		ret = max(ret, now_sum - added_num);
//		return;
//	}
//	for (int i = now_day + day[now_day]; i <= n + day[now_day]; i++) {
//		func(i, now_sum + pay[now_day], pay[now_day]);
//	}
//	
//}
//
//int main() {
//	scanf("%d", &n);
//	for (int loop = 1; loop <= n; loop++) {
//		scanf("%d %d", &day[loop], &pay[loop]);
//	}
//
//	for (int loop = 1; loop <= n; loop++) {
//		func(loop, 0, 0);
//	}
//	cout << ret << "\n";
//	return 0;
//}
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <string.h>
#include <vector>
#include <functional>

#define MAX_SIZE 16
#define INF 0x7fffffff

using namespace std;
//input
int cost[MAX_SIZE];
int day[MAX_SIZE];
int n;

//process
int max_value;

void input() {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) scanf("%d %d", &day[i], &cost[i]);
}

void dfs(int d, int sum) {
	if (d == n + 1) {
		max_value = max(max_value, sum);
		return;
	}

	if (d + day[d] <= n + 1) dfs(d + day[d], sum + cost[d]);
	if (d + 1 <= n + 1) dfs(d + 1, sum);
}

void process() {
	dfs(1, 0);
	printf("%d\n", max_value);
}

int main() {
	input();
	process();

	return 0;
}
