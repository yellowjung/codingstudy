//17471번
//https://yabmoons.tistory.com/291
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>

#define endl "\n"
#define MAX 10 + 1
using namespace std;

int N, Answer = 987654321;
int Person[MAX];        // 인구수를 저장하기 위한 배열
bool Connect[MAX][MAX];    // 구역들 간의 연결관계를 저장하기 위한 배열
bool Select[MAX];        // 조합 구현 시, 뽑은 데이터에 대한 체크를 저장하기 위한 배열
bool Visit[MAX];        // BFS탐색 시, 방문 탐색을 체크하기 위한 배열

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
	/* 2번 조건 : 선거구에 포함된 구역들끼리 모두 연결되어 있는지 ?
	   를 체크해주기 위한 BFS 함수.
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
			/* BFS 탐색 조건 3개
			   조건 1 : 현재 구역과 탐색하려는 구역이 연결되어 있는지 ?
			   조건 2 : 탐색하려는 구역이 선거구에 맞는 놈인지 ?
			   조건 3 : 아직 방문하지 않은 구역인지 ?
			*/
			if (Connect[x][i] == true && Select[i] == T && Visit[i] == false)
			{
				Visit[i] = true;
				Cnt++;        // 갯수를 계속해서 Count
				Q.push(i);
			}
		}
	}

	/* 2번 조건에 위배 되지 않는다 = BFS에서 Count한 값과 Vector의 Size가 같다. */
	if (V.size() == Cnt) return true;
	return false;
}

bool Check()
{
	/* 선거구가 가질 수 있는 조건들에 대해서 Check 해주는 함수.
	   조건 1 : 선거구에 포함된 구역의 갯수가 1개 이상인지 ?
	   조건 2 : 선거구에 포함된 구역들 끼리 모두 연결되어 있는지 ?
	*/

	vector<int> A, B;
	for (int i = 1; i <= N; i++)
	{
		if (Select[i] == true) A.push_back(i); // 1선거구 = A Vector
		else B.push_back(i);                   // 2선거구 = B Vector
	}

	/* 1번 조건 Check */
	if (A.size() == 0 || B.size() == 0) return false;

	/* 2번 조건 Check */
	bool AState = Check_Connection(A, true);
	if (AState == false) return false;

	bool BState = Check_Connection(B, false);
	if (BState == false) return false;

	return true;
}

void Calculate()
{
	/* 인구수 차이를 구하기 위한 함수 */
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
	/* 조합 구현을 위한 DFS 함수. */
	if (Cnt >= 1)
	{
		/* 최소 1개 이상의 원소만 뽑으면 모두 계산해줄 것이므로 조건문 : Cnt >= 1 */
		if (Check() == true)
		{
			Calculate();
		}
		// return이 없으니 조심하자 ! 
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