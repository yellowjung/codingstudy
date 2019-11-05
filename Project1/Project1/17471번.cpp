//17471��
//https://yabmoons.tistory.com/291
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>

#define endl "\n"
#define MAX 10 + 1
using namespace std;

int N, Answer = 987654321;
int Person[MAX];        // �α����� �����ϱ� ���� �迭
bool Connect[MAX][MAX];    // ������ ���� ������踦 �����ϱ� ���� �迭
bool Select[MAX];        // ���� ���� ��, ���� �����Ϳ� ���� üũ�� �����ϱ� ���� �迭
bool Visit[MAX];        // BFSŽ�� ��, �湮 Ž���� üũ�ϱ� ���� �迭

void Input()
{
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		int x; cin >> x;
		Person[i] = x;
	}
	for (int i = 1; i <= N; i++)
	{
		int Cnt; cin >> Cnt;
		for (int j = 0; j < Cnt; j++)
		{
			int a; cin >> a;
			Connect[i][a] = true;
			Connect[a][i] = true;
		}
	}
}

bool Check_Connection(vector<int> V, bool T)
{
	/* 2�� ���� : ���ű��� ���Ե� �����鳢�� ��� ����Ǿ� �ִ��� ?
	   �� üũ���ֱ� ���� BFS �Լ�.
	*/

	memset(Visit, false, sizeof(Visit));
	queue<int> Q;
	Q.push(V[0]);
	Visit[V[0]] = true;
	int Cnt = 1;

	while (Q.empty() == 0)
	{
		int x = Q.front();
		Q.pop();

		for (int i = 1; i <= N; i++)
		{
			/* BFS Ž�� ���� 3��
			   ���� 1 : ���� ������ Ž���Ϸ��� ������ ����Ǿ� �ִ��� ?
			   ���� 2 : Ž���Ϸ��� ������ ���ű��� �´� ������ ?
			   ���� 3 : ���� �湮���� ���� �������� ?
			*/
			if (Connect[x][i] == true && Select[i] == T && Visit[i] == false)
			{
				Visit[i] = true;
				Cnt++;        // ������ ����ؼ� Count
				Q.push(i);
			}
		}
	}

	/* 2�� ���ǿ� ���� ���� �ʴ´� = BFS���� Count�� ���� Vector�� Size�� ����. */
	if (V.size() == Cnt) return true;
	return false;
}

bool Check()
{
	/* ���ű��� ���� �� �ִ� ���ǵ鿡 ���ؼ� Check ���ִ� �Լ�.
	   ���� 1 : ���ű��� ���Ե� ������ ������ 1�� �̻����� ?
	   ���� 2 : ���ű��� ���Ե� ������ ���� ��� ����Ǿ� �ִ��� ?
	*/

	vector<int> A, B;
	for (int i = 1; i <= N; i++)
	{
		if (Select[i] == true) A.push_back(i); // 1���ű� = A Vector
		else B.push_back(i);                   // 2���ű� = B Vector
	}

	/* 1�� ���� Check */
	if (A.size() == 0 || B.size() == 0) return false;

	/* 2�� ���� Check */
	bool AState = Check_Connection(A, true);
	if (AState == false) return false;

	bool BState = Check_Connection(B, false);
	if (BState == false) return false;

	return true;
}

void Calculate()
{
	/* �α��� ���̸� ���ϱ� ���� �Լ� */
	int A_Num, B_Num, Diff;
	A_Num = B_Num = 0;

	for (int i = 1; i <= N; i++)
	{
		if (Select[i] == true) A_Num = A_Num + Person[i];
		else B_Num = B_Num + Person[i];
	}
	Diff = abs(A_Num - B_Num);
	if (Answer > Diff) Answer = Diff;
}

void DFS(int Idx, int Cnt)
{
	/* ���� ������ ���� DFS �Լ�. */
	if (Cnt >= 1)
	{
		/* �ּ� 1�� �̻��� ���Ҹ� ������ ��� ������� ���̹Ƿ� ���ǹ� : Cnt >= 1 */
		if (Check() == true)
		{
			Calculate();
		}
		// return�� ������ �������� ! 
	}

	for (int i = Idx; i <= N; i++)
	{
		if (Select[i] == true) continue;
		Select[i] = true;
		DFS(i, Cnt + 1);
		Select[i] = false;
	}
}

void Solution()
{
	DFS(1, 0);

	if (Answer == 987654321) cout << -1 << endl;
	else cout << Answer << endl;
}

void Solve()
{
	Input();
	Solution();
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//freopen("Input.txt", "r", stdin);
	Solve();

	return 0;
}