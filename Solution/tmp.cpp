#include <iostream>
#include <queue>

using namespace std;

#define MAX_N 31
#define MAX_L 41

int l, n, q;
int info[MAX_L][MAX_L];
int bef_k[MAX_N];
int r[MAX_N], c[MAX_N], h[MAX_N], w[MAX_N], k[MAX_N];
int nr[MAX_N], nc[MAX_N];
int dmg[MAX_N];
bool is_moved[MAX_N];

int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

// 움직임을 시도해봅니다.
bool TryMovement(int idx, int dir) {
    // 초기화 작업입니다.
    for(int i = 1; i <= n; i++) {
        dmg[i] = 0;
        is_moved[i] = false;
        nr[i] = r[i];
        nc[i] = c[i];
    }

    queue<int> q;

    q.push(idx);
    is_moved[idx] = true;

    while(!q.empty()) {
        int x = q.front(); q.pop();

        nr[x] += dx[dir];
        nc[x] += dy[dir];

        // 경계를 벗어나는지 체크합니다.
        if(nr[x] < 1 || nc[x] < 1 || nr[x] + h[x] - 1 > l || nc[x] + w[x] - 1 > l)
            return false;

        // 대상 조각이 다른 조각이나 장애물과 충돌하는지 검사합니다.
        for(int i = nr[x]; i <= nr[x] + h[x] - 1; i++) {
            for(int j = nc[x]; j <= nc[x] + w[x] - 1; j++) {
                if(info[i][j] == 1) 
                    dmg[x]++;
                if(info[i][j] == 2)
                    return false;
            }
        }

        // 다른 조각과 충돌하는 경우, 해당 조각도 같이 이동합니다.
        for(int i = 1; i <= n; i++) {
            if(is_moved[i] || k[i] <= 0) 
                continue;
            if(r[i] > nr[x] + h[x] - 1 || nr[x] > r[i] + h[i] - 1) 
                continue;
            if(c[i] > nc[x] + w[x] - 1 || nc[x] > c[i] + w[i] - 1) 
                continue;

            is_moved[i] = true;
            q.push(i);
        }
    }

    dmg[idx] = 0;
    return true;
}

// 특정 조각을 지정된 방향으로 이동시키는 함수입니다.
void MovePiece(int idx, int dir) {
    if(k[idx] <= 0) 
        return;

    // 이동이 가능한 경우, 실제 위치와 체력을 업데이트합니다.
    if(TryMovement(idx, dir)) {
        for(int i = 1; i <= n; i++) {
            r[i] = nr[i];
            c[i] = nc[i];
            k[i] -= dmg[i];
        }
    }
}

int main() {
    // 입력값을 받습니다.
    cin >> l >> n >> q;
    for(int i = 1; i <= l; i++)
        for(int j = 1; j <= l; j++)
            cin >> info[i][j];
    for(int i = 1; i <= n; i++) {
        cin >> r[i] >> c[i] >> h[i] >> w[i] >> k[i];
        bef_k[i] = k[i];
    }
    for(int i = 1; i <= q; i++) {
        int idx, dir;
        cin >> idx >> dir;
        MovePiece(idx, dir);
    }

    // 결과를 계산하고 출력합니다.
    long long ans = 0;
    for(int i = 1; i <= n; i++) {
        if(k[i] > 0) {
            ans += bef_k[i] - k[i];
        }
    }

    cout << ans;
    return 0;
}