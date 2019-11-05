#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <stdio.h>
using namespace std;

int map[51][51];
int visited[51][51] = { -1, };
bool p_check[50];
int dx[] = { -1,0,1,0 };
int dy[] = { 0,-1,0,1 };
pair<int, int> p_virus[11];
vector<int> pick;
queue<pair<int, int>> q;
int p_count = 0;
int n, d, ans = 987654321;

void init_visit() {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			visited[y][x] = -1;
		}
	}
}

void bfs() {
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int nx = dx[dir] + x;
			int ny = dy[dir] + y;
			if (ny < 0 || nx < 0 || nx >= n || ny >= n)continue;
			if (visited[ny][nx] != -1) continue;
			if (map[ny][nx] == 1) continue;
			q.push({ nx,ny });
			visited[ny][nx] = visited[y][x] + 1;
		}
	}
}

int check_map() {
	int min_time = -1;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			if (visited[y][x] == -1 && map[y][x] == 0) return -1;
			if (min_time < visited[y][x]) {
				min_time = visited[y][x];
			}
		}
	}
	return min_time;
}

void dfs(int idx) {
	if (pick.size() == d) {
		int p_size = pick.size();
		init_visit();
		for (int loop = 0; loop < p_size; loop++) {
			//int tmp = pick[loop];
			//cout << tmp << " ";
			int x = p_virus[pick[loop]].first;
			int y = p_virus[pick[loop]].second;
			visited[y][x] = 0;
			q.push({ x,y });
		}
		//cout << "\n";
		
		bfs();
		int min_time = check_map();
		if (min_time != -1) {
			ans = min(ans, min_time);
		}
		return;
	}

	for (int loop = idx; loop < p_count; loop++) {
		if (!p_check[loop]) {
			p_check[loop] = true;
			pick.push_back(loop);
			dfs(idx + 1);
			pick.pop_back();
			p_check[loop] = false;
		}
	}
}


int main() {
	scanf("%d %d", &n, &d);
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			scanf("%d", &map[y][x]);
			if (map[y][x] == 2) {
				p_virus[p_count].first = x;
				p_virus[p_count].second = y;
				p_count++;
			}
		}
	}

	dfs(0);
	if (ans == 987654321) cout << -1;
	else cout << ans;
	return 0;
}