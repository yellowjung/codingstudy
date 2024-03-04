#include <iostream>

using namespace std;

typedef unsigned long long int ull;

#define LEFT (0)
#define UP (1)
#define RIGHT (2)
#define DOWN (3)

#define MAP_SIZE (6)
#define PRIME (52967)

unsigned int MAP[10][10];

int hashMap[PRIME];

typedef struct st2{
    int r;
    int c;
    int dir;
    int length;
}CAR;

CAR car[11];
int ccnt;

void input(){
    for(int r = 0; r <= MAP_SIZE + 1; r++){
        for(int c = 0; c <= MAP_SIZE + 1; c++){
            MAP[r][c] = -1;
        }
    }

    for(int r = 1; r <= MAP_SIZE; r++){
        for(int c = 1; c <= MAP_SIZE; c++){
            cin >> MAP[r][c];
        }
    }

    for(int r = 1; r <= MAP_SIZE; r++){
        for(int c = 1; c <= MAP_SIZE; c++){
            if(MAP[r][c]){
                int carNum = MAP[r][c];

                MAP[r][c] = 1;

                if(car[carNum].length != 0) continue;

                ccnt++;
                if(MAP[r][c+1] == carNum){
                    car[carNum].r = r;
                    car[carNum].c = c;
                    car[carNum].dir = LEFT;

                    if(MAP[r][c + 2] == carNum) car[carNum].length = 3;
                    else car[carNum].length = 2;
                }else{
                    car[carNum].r = r;
                    car[carNum].c = c;
                    car[carNum].dir = UP;

                    if(MAP[r+2][c] == carNum) car[carNum].length = 3;
                    else car[carNum].length = 2;
                }
            }
        }
    }
}

ull getHash(unsigned int MAP[10][10]){
    ull hash = 0;
    ull count = 0;

    for(int r = 1; r <= MAP_SIZE; r++){
        for(int c = 1; c <= MAP_SIZE; c++){
            hash |= (((ull)MAP[r][c]) << count++);
        }
    }

    return hash;
}

int dr[] = {0, -1, 0, 1};
int dc[] = {-1, 0, 1, 0};

int isMoveRight(CAR car, unsigned MAP[][10]){
    if(MAP[car.r + dr[RIGHT]][car.c + car.length - 1 + dc[RIGHT]] != 0) return 0;

    int length = car.length;

    for(int i = length - 1; i >= 0; i--){
        int nr, nc;

        nr = car.r + dr[RIGHT];
        nc = car.c + i + dc[RIGHT];

        MAP[car.r][car.c + i] = 0;
        MAP[nr][nc] = 1;
   }

    return 1;
}

int isMoveLeft(CAR car, unsigned MAP[][10])
{
	if (MAP[car.r + dr[LEFT]][car.c + dc[LEFT]] != 0) return 0;

	int length = car.length;

	for (int i = 0; i < length; i++)
	{
		int nr, nc;

		nr = car.r + dr[LEFT];
		nc = car.c + i + dc[LEFT];

		MAP[car.r][car.c + i] = 0;
		MAP[nr][nc] = 1;
	}

	return 1;
}

int isMoveUp(CAR car, unsigned MAP[][10])
{
	if (MAP[car.r + dr[UP]][car.c + dc[UP]] != 0) return 0;

	int length = car.length;

	for (int i = 0; i < length; i++)
	{
		int nr, nc;

		nr = car.r + i + dr[UP];
		nc = car.c + dc[UP];

		MAP[car.r + i][car.c] = 0;
		MAP[nr][nc] = 1;
	}

	return 1;
}

int isMoveDown(CAR car, unsigned MAP[][10])
{
	if (MAP[car.r + car.length - 1 + dr[DOWN]][car.c + dc[DOWN]] != 0) return 0;

	int length = car.length;

	for (int i = length - 1; i >= 0; i--)
	{
		int nr, nc;

		nr = car.r + i + dr[DOWN];
		nc = car.c + dc[DOWN];

		MAP[car.r + i][car.c] = 0;
		MAP[nr][nc] = 1;
	}

	return 1;
}

int MIN = 0x7fff0000;
void DFS(int L){
    if(MIN <= L) return;

    ull h = getHash(MAP);
    int p = h % PRIME;

    if(hashMap[p] > L){
        hashMap[p] = L;
    }else{
        return;
    }

    if(car[1].c == 5){
        if(L < MIN) MIN = L;
        return;
    }

    if(L > 7) return;

    for(int i = 1; i <= ccnt; i++){
        if(car[i].dir == LEFT){
            if (isMoveRight(car[i], MAP))
			{
				car[i].c++;
				DFS(L + 1);

				isMoveLeft(car[i], MAP);
				car[i].c--;
			}

			if (isMoveLeft(car[i], MAP))
			{
				car[i].c--;
				DFS(L + 1);

				isMoveRight(car[i], MAP);
				car[i].c++;
			}
        }else{
			if (isMoveUp(car[i], MAP))
			{
				car[i].r--;
				DFS(L + 1);

				isMoveDown(car[i], MAP);
				car[i].r++;
			}

			if (isMoveDown(car[i], MAP))
			{
				car[i].r++;
				DFS(L + 1);

				isMoveUp(car[i], MAP);
				car[i].r--;
			}
        }
    }
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    input();

    for(int i = 0; i < PRIME; i++){
        hashMap[i] = 0x7fff0000;
    }

    DFS(0);

    if(MIN == 0x7fff0000){
        cout<<"-1 \n";
    }else{
        cout<<MIN + 2<<"\n";
    }

    

    return 0;
}