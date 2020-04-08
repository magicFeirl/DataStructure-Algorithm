#include <stdio.h>

const int H = 5;
const int W = 5;

// 地图
int map[H][W] = {
	{1, 1, 1, 0, 1},
	{1, 0, 1, 1, 1},
	{1, 1, 1, 0, 1},
	{1, 0, 0, 1, 1},
	{1, 0, 1, 0, 1}
};

int visited[H][W];

// 方向矩阵
int next[4][2] = {
	{-1, 0},
	{1, 0} ,
	{0, -1},
	{0, 1} ,
};

// 检查下表是否越界
int check_range(int x, int y){
	return (x >= 0 && x < W && y >= 0 && y < H);
}

void DFS(int x, int y, int color){
	
	map[y][x] = color;
	
	for(int i=0; i<4; i++){
		int nx = x + next[i][1];
		int ny = y + next[i][0];
		
		if(check_range(nx, ny) && map[ny][nx] == 0 && !visited[ny][nx]){
			visited[ny][nx] = 1;
			DFS(nx, ny, color);
		}
	}
}

int main(){
	
	int color = -1;
	
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			if(map[i][j] == 0){
				visited[i][j] = 1;
				DFS(j, i, color--);
			}
		}
	}
	
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){

			printf("%-5d", map[i][j]);
		}
		
		printf("\n");
	}
	
	return 0;
}
