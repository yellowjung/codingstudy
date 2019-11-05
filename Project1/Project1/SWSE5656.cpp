//https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRQm6qfL0DFAUo&
#include <stdio.h>
#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include <queue>
using namespace std;

int test_case;
int n, w, h;
int map[17][17];
int c_map[17][17];
int selected[16];
int position[5];
int ret = 987654321;
void print_map() {
	cout << "\n";
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			cout << c_map[y][x] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void map_copy() {
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			c_map[y][x] = map[y][x];
		}
	}
}

void shoot(int idx) {
	queue<pair<pair<int, int>, int>> q;
	for (int y = 0; y < h; y++) {
		if (c_map[y][idx] != 0) {
			q.push({ {idx,y},c_map[y][idx] });
			//cout << "count : " << c_map[y][idx] << "\n";
			break;
		}
	}
	while (!q.empty()) {
		int x = q.front().first.first;
		int y = q.front().first.second;
		int c = q.front().second;
		q.pop();
		//기준 점에서 아래로
		if (c == 1) {
			c_map[y][x] = 0;
			continue;
		}
		for (int loop = 0; loop < c; loop++) {
			if (y + loop >= h) break;
			if (c_map[y + loop][x] != 0) {
				q.push({ {x,y + loop}, c_map[y + loop][x] });
				c_map[y + loop][x] = 0;
			}
		}
		//기준점에서 위로
		for (int loop = 0; loop < c; loop++) {
			if (y - loop < 0) break;
			if (c_map[y - loop][x] != 0) {
				q.push({ {x,y - loop}, c_map[y - loop][x] });
				c_map[y - loop][x] = 0;
			}
		}
		//기준점에서 왼쪽으로
		for (int loop = 0; loop < c; loop++) {
			if (x - loop < 0)break;
			if (c_map[y][x - loop] != 0) {
				q.push({ {x - loop,y},c_map[y][x - loop] });
				c_map[y][x - loop] = 0;
			}
		}
		//기준점에서 오른쪽으로
		for (int loop = 0; loop < c; loop++) {
			if (x + loop >= w)break;
			if (c_map[y][x + loop] != 0) {
				q.push({ {x + loop,y},c_map[y][x + loop] });
				c_map[y][x + loop] = 0;
			}
		}
	}
}

void down() {
	for (int x = 0; x < w; x++) {
		int start = h - 1;
		int count = 0;
		for (int y = start; y >= 0; y--) {
			if (c_map[y][x] == 0) {
				count++;
			}
			else {
				if (count != 0) {
					for (int loop = y; loop >= 0; loop--) {
						c_map[loop + count][x] = c_map[loop][x];
						c_map[loop][x] = 0;
					}
					y = y + count;
					count = 0;
				}
			}
		}
	}
}

void check() {
	int tmp_ret = 0;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (c_map[y][x] != 0) {
				tmp_ret++;
			}
		}
	}
	ret = min(tmp_ret, ret);
}

void func(int idx) {
	if (idx == n) {
		map_copy();
		for (int loop = 0; loop < n; loop++) {
			//cout << position[loop] << " ";
			shoot(position[loop]);
			down();
		}
		check();
		//cout << "\n";
		return;
	}

	for (int loop = 0; loop < w; loop++) {
		//if (selected[loop] == 0) {
		//	selected[loop] = 1;
		position[idx] = loop;
		func(idx + 1);
		//	selected[loop] = 0;
	}
}



int main() {
	scanf("%d", &test_case);
	for (int loop = 1; loop <= test_case; loop++) {
		scanf("%d %d %d", &n, &w, &h);
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				scanf("%d", &map[y][x]);
			}
		}

		func(0);
		cout << "#" << loop << " " << ret << "\n";
		ret = 987654321;
	}
	/*map_copy();
	cout << "Shoot 2\n";
	shoot(2);
	print_map();
	cout << "down\n";
	down();
	print_map();
	cout << "shoot 2\n";
	shoot(2);
	print_map();
	cout << "down\n";
	down();
	print_map();
	cout << "shoot 6\n";
	shoot(6);
	print_map();
	cout << "down\n";
	down();
	print_map();*/
	return 0;
}