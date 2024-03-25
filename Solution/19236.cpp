#include <iostream>

using namespace std;

int MAP[6][6];

typedef struct st2{
    int r; 
    int c;
    int dir;
    int dead;
}FISH;

FISH Fish[17];

void input(){
    for(int r = 0; r <= 5; r++){
        for(int c = 0; c <= 5; c++){
            MAP[r][c] = -1;
        }
    }

    for(int r = 1; r <= 4; r++){
        for(int c = 1; c <= 4; c++){
            int number, dir;

            cin >> number >> dir;

            MAP[r][c] = number;

            Fish[number].r = r;
            Fish[number].c = c;
            Fish[number].dir = dir;
        }
    }
}

int dr[] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
int dc[] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
int changeDir[] = {0, 2, 3, 4, 5, 6, 7, 8, 1};

void DFS(int sr, int sc, int dir, int score, int map[6][6], FISH fish[]){
    int tmpMAP[6][6];
    FISH shark = {0};
    FISH tmpFish[17] = {0};

    for(int r = 0; r <= 5; r++){
        for(int c = 0; c <= 5; c++){
            tmpMAP[r][c] = map[r][c];
        }
    }

    for(int i = 1; i <= 16; i ++){
        tmpFish[i] = fish[i];
    }

    if(tmpFish[tmpMAP[sr][sc]].dead == 1) return;

    shark.r = sr;
    shark.c = sc;

    int deadFishNUmber = tmpMAP[sr][sc];

    shark.dir = tmpFish[deadFishNUmber].dir;

    score += deadFishNUmber;
    tmpFish[deadFishNUmber].dead = 1;

    for(int number = 1; number <= 16; number++){
        FISH f = tmpFish[number];

        if(f.dead) continue;

        while(1){
            int nr, nc;

            nr = f.r + dr[f.dir];
            nc = f.c + dc[f.dir];

            if(tmpMAP[nr][nc] == -1 || (nr == shark.r && nc == shark.c)){
                tmpFish[number].dir = f.dir = changeDir[f.dir];
                continue;
            }else{
                int changeFishNumber = tmpMAP[nr][nc];

                int tmpR, tmpC;
            }
        }
    }


}

int main(){

    return 0;
}