//https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV597vbqAH0DFAVl&
#include <stdio.h>
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <deque>
using namespace std;

struct BUG {
	int x, y, dir, size;
};

deque<BUG> map[2][100][100];
//1 위 2아래 3왼쪽 4오른쪽
int dx[5] = { 0, 0,0,-1,1 };
int dy[5] = { 0, -1,1,0,0 };

//n 셀의 개수 m 격리시간, k미생물의 군집 개수
int t_case, n, m, k;

void print_map(int idx) {
	//print
	cout << "\n";
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			if (!map[idx][y][x].empty()) {
				cout << map[idx][y][x][0].size << " ";
			}
			else {
				cout << "0 ";
			}
		}
		cout << "\n";
	}
	cout << "\n";
}

void move(int turn, int n_turn, int y, int x) {
	//cout << "===================================\n";
	//cout << "turn : " << turn<<"\n";
	//cout << "n_turn : " << n_turn << "\n";
	//cout << "x : " << x << " y : " << y << "\n";
	//cout << "===================================\n";
	BUG tmp = map[turn][y][x][0];
	map[turn][y][x].pop_back();
	int nx, ny;
	if (map[turn][y][x].size() != 0) {
		cout << "x : " << x << "y : " << y << "\n";
		cout << "size : " << map[turn][y][x].size() << "\n";
		return;
	}
	switch (tmp.dir)
	{
	case 1:
		//위
		ny = tmp.y + dy[1];
		if (ny <= 0) {
			ny = 0;
			tmp.dir = 2;
			tmp.size /= 2;

		}
		tmp.y = ny;
		break;
	case 2:
		//아래
		ny = tmp.y + dy[2];
		if (ny >= n - 1) {
			ny = n - 1;
			tmp.dir = 1;
			tmp.size /= 2;
		}
		tmp.y = ny;
		break;
	case 3:
		//좌
		nx = tmp.x + dx[3];
		if (nx <= 0) {
			nx = 0;
			tmp.dir = 4;
			tmp.size /= 2;
		}
		tmp.x = nx;
		break;
	case 4:
		//우
		nx = tmp.x + dx[4];
		if (nx >= n - 1) {
			nx = n - 1;
			tmp.dir = 3;
			tmp.size /= 2;
		}
		tmp.x = nx;
		break;
	default:
		break;
	}

	map[n_turn][tmp.y][tmp.x].push_back(tmp);
	/*if (!map[n_turn][tmp.y][tmp.x].empty() && tmp.size != 0) {
		BUG one = map[n_turn][tmp.y][tmp.x][0];
		map[n_turn][tmp.y][tmp.x].pop_back();
		if (one.size > tmp.size) {
			one.size += tmp.size;
			map[n_turn][one.y][one.x].push_back(one);
		}
		else {
			tmp.size += one.size;
			map[n_turn][tmp.y][tmp.x].push_back(tmp);
		}
	}
	else if(tmp.size != 0){
		map[n_turn][tmp.y][tmp.x].push_back(tmp);
	}*/
	//print_map(n_turn);
}

bool compare(BUG a, BUG b) {
	if (a.size > b.size) {
		return true;
	}
	else {
		return false;
	}
}

void arrange(int turn, int y, int x) {
	int count = map[turn][y][x].size();
	sort(map[turn][y][x].begin(), map[turn][y][x].end(), compare);
	BUG big = map[turn][y][x][0];
	int tmp = 0;
	for (int loop = 0; loop < count; loop++) {
		tmp += map[turn][y][x][loop].size;
	}
	map[turn][y][x].clear();
	big.size = tmp;
	map[turn][y][x].push_back(big);
}

void init() {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			if (!map[0][y][x].empty() || !map[1][y][x].empty()) {
				map[0][y][x].clear();
				map[1][y][x].clear();
			}
		}
	}
}

int main() {
	scanf("%d", &t_case);
	for (int loop = 1; loop <= t_case; loop++) {
		scanf("%d %d %d", &n, &m, &k);
		
		init();

		for (int loop = 0; loop < k; loop++) {
			int x, y, dir, size;
			scanf("%d %d %d %d", &y, &x, &size, &dir);
			map[0][y][x].push_back({ x,y,dir,size });
		}
		int turn = 0, n_turn = 0;
		for (int loop = 0; loop < m; loop++) {
			turn = loop % 2;
			n_turn = (loop + 1) % 2;
			//print_map(turn);
			//for (int y = 0; y < n; y++) {
			//	for (int x = 0; x < n; x++) {
			//		map[n_turn][y][x].clear();
			//	}
			//}


			for (int y = 0; y < n; y++) {
				for (int x = 0; x < n; x++) {
					if (!map[turn][y][x].empty()) {
						move(turn, n_turn, y, x);
					}
				}
			}

			//여기서 맵 정리 한번 들어가야함
			for (int y = 0; y < n; y++) {
				for (int x = 0; x < n; x++) {
					if (!map[n_turn][y][x].empty()) {
						arrange(n_turn, y, x);
					}
				}
			}
			//print_map(n_turn);
		}

		int tmp = 0;
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				if (!map[n_turn][y][x].empty()) {
					tmp += map[n_turn][y][x][0].size;
				}
			}
		}
		cout << "#" << loop << " " << tmp << "\n";
	}
	return 0;
}