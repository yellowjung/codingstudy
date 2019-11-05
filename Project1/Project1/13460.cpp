#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;

char map[10][10];
int n, m, ret;

struct INFO {
	int rx, ry, bx, by, count;
};

INFO start;


int bfs() {
	const int dx[] = { -1,1,0,0 };
	const int dy[] = { 0,0,-1,1 };

	int visited[10][10][10][10] = { 0, };
	queue<INFO> q;
	q.push(start);
	visited[start.rx][start.ry][start.bx][start.by] = 1;

	int ret = -1;
	while (!q.empty()) {
		INFO cur = q.front(); q.pop();
		if (cur.count > 10) break;
		if (map[cur.rx][cur.ry] == '0' && map[cur.bx][cur.by] != '0') {
			ret = cur.count;
			break;
		}

		for (int dir = 0; dir < 4; dir++) {
			int next_rx = cur.rx;
			int next_ry = cur.ry;
			int next_bx = cur.bx;
			int next_by = cur.by;

			while (1) {
				if (map[next_rx][next_ry] != '#' && map[next_rx][next_ry] != 'O') {
					next_rx += dx[dir], next_ry += dy[dir];
				}
				else {
					if (map[next_rx][next_ry] == '#') {
						next_rx -= dx[dir], next_ry -= dy[dir];
					}
					break;
				}
			}

			while (1) {
				if (map[next_bx][next_by] != '#' && map[next_bx][next_by] != 'O') {
					next_bx += dx[dir], next_by += dy[dir];
				}
				else {
					if (map[next_bx][next_by] == '#') {
						next_bx -= dx[dir], next_by -= dy[dir];
					}
					break;
				}
			}

			if (next_rx == next_by && next_ry == next_by) {
				if (map[next_rx][next_ry] != 'O') {
					int red_dist = abs(next_rx - cur.rx) + abs(next_ry - cur.ry);
					int blue_dist = abs(next_bx - cur.bx) + abs(next_by - cur.by);
					if (red_dist > blue_dist) {
						next_rx -= dx[dir], next_ry -= dy[dir];
					}
					else {
						next_bx -= dx[dir], next_by -= dy[dir];
					}
				}
			}

			if (visited[next_rx][next_ry][next_bx][next_by] == 0) {
				visited[next_rx][next_ry][next_bx][next_by] = 1;
				INFO next;
				next.rx = next_rx;
				next.ry = next_ry;
				next.bx = next_bx;
				next.by = next_by;
				next.count = cur.count + 1;
				q.push(next);
			}
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%s", map[i]);
	}

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < m; y++) {
			if (map[x][y] == 'R') {
				start.rx = x, start.ry = y;
			}
			if (map[x][y] = 'B') {
				start.bx = x, start.by = y;
			}
		}
	}
	start.count = 0;

	ret = bfs();
	printf("%d\n", ret);


	return 0;
}