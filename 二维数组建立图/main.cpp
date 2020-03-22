#include <cstdio>

using namespace std;

const int N = 5;

int e[N][N], visited[N], count; // ��ά�����ͼ

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
	
	
	scanf("%d %d", &n, &m); // ���������ͱ���
	
	/*
		��ʼ����ά����
		��ǰ�ڵ㵽��ǰ�ڵ�Ϊ0�����ܣ�
        ʣ��ȫ��Ϊ-1��ʾ�ޱߣ��ȴ�����
	 */
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			if(i == j){
				e[i][j] = 0;
			}else{
				e[i][j] = -1; // ��-1��ʾ�ޱ�
			}
		}
	}
	
	/* ����� */
	for(i=0; i<m; i++){
		int a, b;
		scanf("%d %d", &a, &b); // �����������
		e[a-1][b-1] = e[b-1][a-1] = 1; // ��1��ʾ�б�
	}
	
	putchar('\n');
	
	visited[0] = 1;
	DFS(0, N);
	
	return 0;
}
