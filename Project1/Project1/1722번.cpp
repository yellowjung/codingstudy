#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

long long int factorial[21];
vector<int> permutation;
vector<int> visited;
void Nth_Permutation(int n, long long int k) {

	if (n == 1)
	{
		for (int i = 1; i <= visited.size(); i++)
		{
			if (!visited[i]) {
				printf("%d\n", i);
				return;
			}
		}
	}
	else {

		for (int i = 1; i <= visited.size(); i++)
		{
			if (visited[i]) continue;
			if (k <= factorial[n - 1]) {

				printf("%d ", i);
				visited[i] = 1;
				Nth_Permutation(n - 1, k);
				return;
			}

			k -= factorial[n - 1];
		}
	}
}

long long int Nth(long long int k, int n) {

	long long int m = 0;

	if (k == visited.size() - 2)
	{
		return 1;
	}

	for (int i = 1; i <= visited.size(); i++)
	{
		if (visited[i]) continue;
		if (i == permutation[k])
		{
			visited[i] = 1;
			return Nth(k + 1, n - 1) + m;
		}

		m += factorial[n - 1];
	}
}

int main()
{
	int n, p;
	long long int k;

	cin >> n >> p;
	visited.resize(n + 1);
	factorial[0] = 1;
	for (int i = 1; i <= 20; i++)
	{
		factorial[i] = factorial[i - 1] * i;
	}

	if (p == 1)
	{
		cin >> k;
		Nth_Permutation(n, k);


	}
	else if (p == 2)
	{
		permutation.resize(n);
		for (int i = 0; i < n; i++)
			scanf("%d", &permutation[i]);

		cout << Nth(0, n) << endl;

	}



	return 0;
}
