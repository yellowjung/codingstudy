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
		//���� ���� ����� ��� �԰�
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

		//�� �����δ�
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
				//�� �Ʒ�
				if (dir == 0 || dir == 1)
				{
					int next = y + moveDir[dir].y;
					if (!(1 <= next && next <= R))
						dir = 1 - dir;
					y += moveDir[dir].y;
				}
				//���� �����ʤ�
				else
				{
					int next = x + moveDir[dir].x;
					if (!(1 <= next && next <= C))
						dir = 5 - dir;
					x += moveDir[dir].x;
				}
			}

			//�̹� �ش� ĭ�� �� ���� ���
			if (shark[y][x].size())
			{
				//�ش� ĭ�� �ִ� ��� ũ�⺸�� �ڱⰡ �� Ŭ ��쿡�� ��ü
				if (shark[y][x][0].first < size)
				{
					shark[y][x].clear();
					shark[y][x].push_back({ size,{ speed, dir } });
				}
			}
			//�ش� ĭ�� �� ���� ��� �ٷ� �߰�
			else
				shark[y][x].push_back({ size,{ speed, dir } });
		}
	}
	cout << result << "\n";
	return 0;
}