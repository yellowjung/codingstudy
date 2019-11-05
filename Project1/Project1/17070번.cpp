//https://jaimemin.tistory.com/1245
//https://www.crocus.co.kr/1454
#include <iostream>
#include <stdio.h>
#include <queue>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

int map[16][16];
int result;
int n;

struct Dir{
	int y, x;
};

Dir moveDir[3] = { {0,1},{1,0},{1,1} };

void func(int y, int x, int pipe) {
	if (y == n - 1 && x == n - 1) {
		result++;
		return;
	}

	for (int i = 0; i < 3; i++) {
		if ((i == 0 && pipe == 1) || (i == 1 && pipe == 0)) {
			continue;
		}
		int nextY = y + moveDir[i].y;
		int nextX = x + moveDir[i].x;
		if (nextY >= n || nextX >= n || map[nextY][nextX] == 1) {
			continue;
		}
		if (i == 2 && (map[y][x + 1] == 1 || map[y + 1][x] == 1)) {
			continue;
		}
		func(nextY, nextX, i);
	}

}

int main() {
	scanf("%d", &n);
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			scanf("%d", &map[y][x]);
		}
	}
	func(0, 1, 0);

	cout << result << "\n";

	return 0;
}

//=====================================================================
//#include <iostream>
//#include <stdio.h>
//#include <queue>
//#include <algorithm>
//using namespace std;
//
//int map[16][16];
//int visited[16][16];
////0 : 가로
////1 : 대각선
////2 : 세로
//int dx[3] = { 1,1,0 };
//int dy[3] = { 0,1,1 };
//int n, ret;
//
//void func() {
//	queue<pair<pair<int, int>, int>> q;
//	q.push({ {1,0},0 });
//	visited[0][0] = 1;
//	visited[0][1] = 1;
//	while (!q.empty()) {
//		int x = q.front().first.first;
//		int y = q.front().first.second;
//		int d = q.front().second;
//		q.pop();
//		if (x == n - 1 && y == n - 1) {
//			ret++;
//		}
//		if (d == 0) {
//			//가로 : 대각선이랑 가로 갈 수 있음
//			for (int loop = 0; loop < 2; loop++) {
//				int nx = x + dx[loop];
//				int ny = y + dy[loop];
//				if (loop == 1) {
//					if (map[ny - 1][nx] == 1 || map[ny][nx - 1] == 1) continue;
//				}
//				if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
//				if (map[ny][nx] == 1) continue;
//				q.push({ {nx,ny},loop });
//			}
//		}
//		else if (d == 1) {
//			//대각선 : 가 세 대 3개 다 됨
//			for (int loop = 0; loop < 3; loop++) {
//				int nx = x + dx[loop];
//				int ny = y + dy[loop];
//				if (loop == 1) {
//					if (map[ny - 1][nx] == 1 || map[ny][nx - 1] == 1) continue;
//				}
//				if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
//				if (map[ny][nx] == 1) continue;
//				q.push({ {nx,ny},loop });
//			}
//
//		}
//		else if (d == 2) {
//			//세로 : 세로랑 대각선 갈 수 있음
//			for (int loop = 1; loop < 3; loop++) {
//				int nx = x + dx[loop];
//				int ny = y + dy[loop];
//				if (loop == 1) {
//					if (map[ny - 1][nx] == 1 || map[ny][nx - 1] == 1) continue;
//				}
//				if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
//				if (map[ny][nx] == 1) continue;
//				q.push({ {nx,ny},loop });
//			}
//		}
//	}
//}
//
//int main() {
//	scanf("%d", &n);
//	for (int y = 0; y < n; y++) {
//		for (int x = 0; x < n; x++) {
//			scanf("%d", &map[y][x]);
//		}
//	}
//
//	func();
//
//	cout << ret << "\n";
//
//	return 0;
//}