#include <stdio.h>
#include <iostream>
#include <queue>
#include <string>
using namespace std;

int l, r, c;
string map[30][30];
int visited[30][30][30];

int dx[6] = { -1,1,0,0,0,0 };
int dy[6] = { 0,0,-1,1,0,0 };
int df[6] = { 0,0,0,0,-1,1 };

queue<pair<pair<int, int>, pair<int, int>>> q;

void init() {
	for (int floor = 0; floor < l; floor++) {
		for (int y = 0; y < r; y++) {
			for (int x = 0; x < c; x++) {
				visited[floor][y][x] = 0;
			}
			map[floor][y] = "#";
		}
	}
	int count = q.size();
	for (int a = 0; a < count; a++) {
		q.pop();
	}
}
int start_x = 0, start_y = 0, start_floor = 0;
int end_x = 0, end_y = 0, end_floor = 0;
int main() {
	while (1) {
		scanf("%d %d %d", &l, &r, &c);
		if (l == 0 && r == 0 && c == 0) {
			break;
		}
		for (int floor = 0; floor < l; floor++) {
			for (int y = 0; y < r; y++) {
				cin >> map[floor][y];
				for (int x = 0; x < c; x++) {
					if (map[floor][y][x] == 'S') {
						start_x = x, start_y = y, start_floor = floor;
						q.push({ {x,y},{floor,1} });
						visited[floor][y][x] = 1;
					}
					else if (map[floor][y][x] == 'E') {
						end_x = x, end_y = y, end_floor = floor;
					}
				}
			}
		}
		int ret = -1;
		while (!q.empty()) {
			int x = q.front().first.first;
			int y = q.front().first.second;
			int floor = q.front().second.first;
			int dis = q.front().second.second;
			q.pop();
			if (x == end_x && y == end_y && floor == end_floor) {
				if (ret == -1 || ret > dis) {
					ret = dis;
				}
			}
			for (int dir = 0; dir < 6; dir++) {
				int nx = x + dx[dir];
				int ny = y + dy[dir];
				int nf = floor + df[dir];
				if (nx < 0 || ny < 0 || nf < 0 || nx >= c || ny >= r || nf >= l) continue;
				if (map[nf][ny][nx] == '#' || visited[nf][ny][nx] != 0) continue;
				q.push({ {nx,ny},{nf,dis + 1} });
				visited[nf][ny][nx] = 1;
			}

		}
		if (ret == -1) {
			cout << "Trapped!\n";
		}
		else {
			cout << "Escaped in " << ret << " minute(s).\n";
		}
		init();
	}
	return 0;
}