#include <stdio.h>
#include <queue>
#include <vector>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int map[51][51];
int visited[51][51];
int dx[] = { -1,0,1,0 };
int dy[] = { 0,-1,0,1 };
vector<pair<int, int>> virus;
vector<pair<int, int>> pick_v;
int v_check[51];
int n, m, k = 0, ans = 1000000000;
queue<pair<int, int>> q;
int v_size = 0;
void print_map() {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			cout << map[y][x] << " ";
		}
		cout << "\n";
	}
}

void print_visited() {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			cout << visited[y][x] << " ";
		}
		cout << "\n";
	}
}

void bfs() {
	int infect = 0, times = 0;
	while (!q.empty()) {
		int x = q.front().first, y = q.front().second; q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
			if (map[ny][nx] == 1 || visited[ny][nx] != -1) continue;
			visited[ny][nx] = visited[y][x] + 1;
			if (map[ny][nx] == 0) {
				infect += 1;
				times = visited[ny][nx];
			}
			q.push({ nx,ny });
		}
	}
	if (infect == k && ans > times) ans = times;
}

bool selec[51] = { false, };

void func(int idx,int cnt) {
	if (cnt == m) {
		memset(visited, -1, sizeof(visited));
		for (int loop = 0; loop < v_size; loop++) {
			if (selec[loop]) {
				q.push({ virus[loop].first, virus[loop].second });
				visited[virus[loop].second][virus[loop].first] = 0;
			}
		}
		bfs();
		return;
	}

	for (int loop = idx; loop < v_size; loop++) {
		if (!selec[loop]) {
			selec[loop] = true;
			func(loop + 1, cnt + 1);
			selec[loop] = false;
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			scanf("%d", &map[y][x]);
			if (map[y][x] == 2) {
				virus.push_back({ x,y });
			}
			else if(map[y][x] == 0){
				k += 1;
			}
		}
	}
	v_size = virus.size();
	func(0,0);
	if (ans == 1000000000) cout << "-1\n";
	else cout << ans << "\n";
	return 0;
}