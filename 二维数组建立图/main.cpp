#include <cstdio>

using namespace std;

const int N = 5;

int e[N][N], visited[N], count; // 二维数组存图

void DFS(int cur, int size){
	count++;
	printf("%d ", cur+1);
	if(count == size){
		return ;
	}else{
		for(int i=0; i<size; i++){
			if(e[cur][i] == 1 && !visited[i]){
				visited[i] = 1;
				DFS(i, size);
			}
		}
	}
}

int main(){
	int i, j, n, m;
	
	
	scanf("%d %d", &n, &m); // 输入结点数和边数
	
	/*
		初始化二维数组
		当前节点到当前节点为0（不管）
        剩余全部为-1表示无边，等待输入
	 */
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			if(i == j){
				e[i][j] = 0;
			}else{
				e[i][j] = -1; // 用-1表示无边
			}
		}
	}
	
	/* 输入边 */
	for(i=0; i<m; i++){
		int a, b;
		scanf("%d %d", &a, &b); // 输入两个结点
		e[a-1][b-1] = e[b-1][a-1] = 1; // 用1表示有边
	}
	
	putchar('\n');
	
	visited[0] = 1;
	DFS(0, N);
	
	return 0;
}
