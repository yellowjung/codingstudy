#include <iostream>
#include <stdio.h> 
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

int isused1[50];
int isused2[50];
int map[50][50];
int ans[2];
int n, s;

void func(int row, int col, int count, int color) {
	if (col >= n) {
		row++;
		if (col % 2 == 0) col = 1;
		else col = 0;
	}
	if (row >= n) {
		ans[color] = max(ans[color], count);
		return;
	}
	if (map[row][col] && !isused1[col - row + n - 1] && !isused2[row + col]) {
		isused1[col - row + n - 1] = isused2[row + col] = 1;
		func(row, col + 2, count + 1, color);
		isused1[col - row + n - 1] = isused2[row + col] = 0;
	}
	func(row, col + 2, count, color);
}

int main() {
	cin >> n;
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			scanf("%d", &map[x][y]);
		}
	}

	func(0, 0, 0, 0);
	func(0, 1, 0, 1);
	cout << ans[0] + ans[1];
	return 0;
}