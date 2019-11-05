#include <stdio.h>
#include <string>
#include <iostream>
#include <queue>
using namespace std;

int n;
int map[100][100];
int land_map[100][100];
int visited[100][100];

int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };

queue<pair<pair<int, int>,int>> land_q;
queue<pair<pair<int, int>, int>> q;


void init_visited() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			visited[x][y] = 0;
		}
	}
}

void init() {
	int size = q.size();
	for (int a = 0; a < size; a++) {
		q.pop();
	}
	init_visited();
}

void land_bfs() {
	while (!land_q.empty()) {
		int x = land_q.front().first.first;
		int y = land_q.front().first.second;
		int num = land_q.front().second;
		land_q.pop();
		land_map[x][y] = num;
		for (int dir = 0; dir < 4; dir++) {
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
			if (visited[nx][ny] != 0 || map[nx][ny] == 0) continue;
			visited[nx][ny] = 1;
			land_q.push({ { nx,ny }, num });
		}
	}
}

void check_land() {
	int land_num = 1;
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (map[x][y] == 1 && visited[x][y] == 0) {
				visited[x][y] = 1;
				land_q.push({ { x,y },land_num });
				land_bfs();
				land_num++;
			}
		}
	}
}



int near(int x , int y, int check) {
	if (check == -1) {
		for (int dir = 0; dir < 4; dir++) {
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
			if (land_map[nx][ny] != 0) {
				return land_map[nx][ny];
			}
		}
	}
	else {
		for (int dir = 0; dir < 4; dir++) {
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
			if (land_map[nx][ny] != 0 && check != land_map[nx][ny]) {
				return land_map[nx][ny];
			}
		}
	}
	return 0;
}



int MAX = 999999999;
void bridge_bfs(int start) {
	while (!q.empty()) {
		int x = q.front().first.first;
		int y = q.front().first.second;
		int dis = q.front().second;
		int land = near(x, y, start);
		q.pop();
		if (land != 0 && land != start) {
			if (dis == 0) continue;
			if (MAX > dis) {
			/*	printf("dis : %d\n",dis);
				for (int x = 0; x < n; x++) {
					for (int y = 0; y < n; y++) {
						printf("%d ", visited[x][y]);
					}
					printf("\n");
				}*/
				MAX = dis;
			}
			break;
		}
		for (int dir = 0; dir < 4; dir++) {
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
			if (visited[nx][ny] != 0)continue;
			if (land_map[nx][ny] != 0)continue;
			visited[nx][ny] = dis + 1;
			q.push({ {nx,ny},dis + 1 });
			
		}
	}
}

void bridge() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			int check = 0;
			check = near(x,y,-1);
			if (land_map[x][y] == 0 && visited[x][y] == 0 && check != 0) {
				visited[x][y] = 1;
				q.push({ { x,y }, 1 });
				bridge_bfs(check);
				init();
			}
		}
	}
}

int main(){
	scanf("%d", &n);
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			scanf("%d", &map[x][y]);
		}
	}

	check_land();
	init_visited();
	bridge();
	printf("%d\n", MAX);




	/*printf("\n");
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			printf("%d ", land_map[x][y]);
		}
		printf("\n");
	}*/

	return 0;
}