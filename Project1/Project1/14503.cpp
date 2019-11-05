#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <stdio.h>
using namespace std;
//0 ºÏ, 1 µ¿, 2³², 3¼­
int dx[4] = {0,1,0,-1};
int dy[4] = {-1,0,1,0};

int map[51][51];
int visited[51][51];
queue <pair<pair<int, int>,int>> q;
int n, m, r, c, po;
int main() {
	scanf("%d %d", &n, &m);
	scanf("%d %d %d", &r, &c, &po);
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			scanf("%d", &map[y][x]);
		}
	}

	q.push({ {c,r}, po });

	int ret = 0;
	while (!q.empty()) {
		int cx = q.front().first.first;
		int cy = q.front().first.second;
		int cd = q.front().second;
		q.pop();
		if (visited[cy][cx] == 0) {
			visited[cy][cx] = 1;
			ret++;
		}
		for (int dir = 0; dir < 4; dir++) {
			int nd = (cd + 3 - dir) % 4;
			int nx = cx + dx[nd];
			int ny = cy + dy[nd];
			if (nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
			if (visited[ny][nx] != 0) continue;
			if (map[ny][nx] != 0)continue;
			q.push({ {nx,ny}, nd });
			break;
		}
		if (q.empty()) {
			int nd = cd;
			int nx = cx + dx[(nd + 2) % 4];
			int ny = cy + dy[(nd + 2) % 4];
			if (nx < 0 || ny < 0 || nx >= m || ny >= n) break;
			if (map[ny][nx] == 1) break;
			q.push({ {nx,ny},nd });
		}

	}
	cout << ret <<"\n";
	return 0;
}