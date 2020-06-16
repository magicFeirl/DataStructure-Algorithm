// 加权+路径压缩并查集
// 详见《算法4》
#include <stdio.h>

const int N = 1e5;
int id[N], sz[N];

void init(){
	for(int i=0; i<N; i++){
		id[i] = i;
		sz[i] = 0;
	}
}

int find(int p){
	if(id[p] != p){
		id[p] = find(id[p]);
	}
	
	return id[p];
}

void union_pq(int p, int q){
	int pRoot = find(p);
	int qRoot = find(q);
	
	// 之前这里写成 sz[p]... 了，非常谔谔的低级错误，我改悔
	if(p != q){
		if(sz[pRoot] > sz[qRoot]){
			id[qRoot] = id[pRoot];
			sz[pRoot] += sz[qRoot];
		}else{
			id[pRoot] = id[qRoot];
			sz[qRoot] += sz[pRoot];
		}
	}
}

int connected(int p, int q){
	return find(p) == find(q);
}

int main(){
	init();
	
	union_pq(1, 2);
	union_pq(2, 4);
	union_pq(4, 6);
	union_pq(6, 1);
	
	printf("%d %d\n", connected(1, 4), connected(0, 4)); // 1 0
	printf("%d %d\n", connected(6, 4), connected(2, 4)); // 1 1
	
	return 0;
}
