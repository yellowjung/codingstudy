//https://jaimemin.tistory.com/1204
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX = 100 + 1;

typedef struct
{
	int y, x;
}Dir;

Dir moveDir[4] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} }; //N S E W

int R, C, M;
int arr[MAX][MAX];
vector<pair<int, pair<int, int>>> shark[MAX][MAX];

int main(void)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> R >> C >> M;

	for (int i = 0; i < M; i++)
	{
		int r, c, s, d, z;
		cin >> r >> c >> s >> d >> z;

		shark[r][c].push_back({ z, {s, d - 1} });
	}

	int cur = 0;
	int result = 0;
	for (int c = 0; c < C; c++)
	{
		cur++;
		//땅에 제일 가까운 상어 먹고
		for (int i = 1; i <= R; i++)
			if (shark[i][cur].size())
			{
				result += shark[i][cur][0].first;
				shark[i][cur].clear();
				break;
			}

		//r, c, z, s, d
		queue<pair<pair<int, int>, pair<int, pair<int, int>>>> q;
		for (int i = 1; i <= R; i++)
			for (int j = 1; j <= C; j++)
				if (shark[i][j].size())
				{
					q.push({ {i, j}, {shark[i][j][0]} });
					shark[i][j].clear();
				}

		//상어가 움직인다
		while (!q.empty())
		{
			int y = q.front().first.first;
			int x = q.front().first.second;
			int size = q.front().second.first;
			int speed = q.front().second.second.first;
			int dir = q.front().second.second.second;
			q.pop();

			for (int i = 0; i < speed; i++)
			{
				//위 아래
				if (dir == 0 || dir == 1)
				{
					int next = y + moveDir[dir].y;
					if (!(1 <= next && next <= R))
						dir = 1 - dir;
					y += moveDir[dir].y;
				}
				//왼쪽 오른쪽ㄴ
				else
				{
					int next = x + moveDir[dir].x;
					if (!(1 <= next && next <= C))
						dir = 5 - dir;
					x += moveDir[dir].x;
				}
			}

			//이미 해당 칸에 상어가 있을 경우
			if (shark[y][x].size())
			{
				//해당 칸에 있는 상어 크기보다 자기가 더 클 경우에만 대체
				if (shark[y][x][0].first < size)
				{
					shark[y][x].clear();
					shark[y][x].push_back({ size,{ speed, dir } });
				}
			}
			//해당 칸에 상어가 없는 경우 바로 추가
			else
				shark[y][x].push_back({ size,{ speed, dir } });
		}
	}
	cout << result << "\n";
	return 0;
}