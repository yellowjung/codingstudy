#include <iostream>
#include <stdio.h>
#include <queue>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

//1941¹ø
//http://blog.naver.com/PostView.nhn?blogId=bjybaek&logNo=221074736412&parentCategoryNo=&categoryNo=6&viewDate=&isShowPopularPosts=false&from=postView

string map[5];
int checker[25];
int visited[5][5];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };
int ret;
queue<pair<int, int>>q;

void bfs() {
	int count = 0, i_x, i_y;
	for (int loop = 0; loop < 25; loop++) {
		if (checker[loop] == 1) {
			i_x = loop % 5;
			i_y = loop / 5;
			break;
		}
	}
	q.push({ i_x,i_y });
	visited[i_y][i_x] = 1;
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		count += 1;
		for (int dir = 0; dir < 4; dir++) {
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			if (nx < 0 || ny < 0 || nx >= 5 || ny >= 5)continue;
			if (visited[ny][nx] != 0)continue;
			if (checker[ny * 5 + nx] == 0) continue;
			q.push({ nx,ny });
			visited[ny][nx] = 1;

		}
	}
	//cout << "count : " << count << "\n";
	if (count == 7) {
		ret += 1;
	}
}

void func() {
	do {
		int som = 0, yeon = 0;
		for (int loop = 0; loop < 25; loop++) {
			if (checker[loop] == 1) {
				int x = loop % 5;
				int y = loop / 5;
				if (map[y][x] == 'Y') {
					yeon += 1;
				}
				else {
					som += 1;
				}
			}
		}
		if (som < 4) continue;
		memset(visited, 0, sizeof(visited));
		bfs();


	} while (next_permutation(checker, checker + 25));
}


int main() {
	std::ios_base::sync_with_stdio(0);
	for (int loop = 0; loop < 5; loop++) {
		cin >> map[loop];
	}
	for (int loop = 0; loop < 7; loop++) {
		checker[24 - loop] = 1;
	}
	func();
	cout << ret << "\n";
	return 0;
}