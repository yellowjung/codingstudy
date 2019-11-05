#include <stdio.h>
#include <iostream>
#include <queue>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

string map[21];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };

int dist[22][22][22];
bool chk[22][22][22];

vector<pair<pair<int, int>, int>> trash;
int sx, sy;

int w, h;

void bfs(int x, int y, int pos) {
	queue<pair<int, int>> q;
	q.push({ x,y });
	chk[y][x][pos] = true;
	dist[y][x][pos] = 0;
	while (!q.empty()) {
		int cx = q.front().first;
		int cy = q.front().second;
		q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int nx = cx + dx[dir];
			int ny = cy + dy[dir];
			if (nx < 0 || ny < 0 || nx >= w || ny >= h) continue;
			if (chk[ny][nx][pos] == true || map[ny][nx] == 'x') continue;
			chk[ny][nx][pos] = true;
			dist[ny][nx][pos] = dist[cy][cx][pos] + 1;
			q.push({ nx,ny });
		}
	}
}

int main() {
	while (1) {
		scanf("%d %d", &w, &h);
		if (w == 0 && h == 0) {
			break;
		}
		for (int i = 0; i < 22; i++) {
			for (int j = 0; j < 22; j++) {
				for (int k = 0; k < 22; k++) {
					dist[i][j][k] = 1000000;
					chk[i][j][k] = 0;
				}
			}
		}
		
		//memset(map, 0, sizeof(map));
		trash.clear();
		sx = sy = 0;
		int tcnt = 1;
		for (int y = 0; y < h; y++) {
			cin >> map[y];
			for (int x = 0; x < w; x++) {
				if (map[y][x] == '*')trash.push_back({ {x,y}, tcnt++ });
				if (map[y][x] == 'o') sx = x, sy = y;
			}
		}
		int ans = 1000000;
		int cnt = trash.size();
		if (cnt == 0) {
			cout << "0\n";
			continue;
		}
		bfs(sx, sy, 0);
		
		sort(trash.begin(), trash.end());
		for (int i = 0; i < cnt; i++) {
			bfs(trash[i].first.first, trash[i].first.second, trash[i].second);
		}
		do {
			int temp = dist[trash[0].first.second][trash[0].first.first][0];
			for (int i = 0; i < cnt - 1; i++) {
				temp += dist[trash[i + 1].first.second][trash[i + 1].first.first][trash[i].second];
			}
			ans = min(ans, temp);
		} while (next_permutation(trash.begin(), trash.end()));
		printf("%d\n", ans == 1000000 ? -1 : ans);
	}
}