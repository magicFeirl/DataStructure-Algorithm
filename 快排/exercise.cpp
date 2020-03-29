// ���¿��ŵ�ģ�� 2020��3��29��14:09:23
// 2020��3��29��14:14:49 ����5minߣ���ˣ������˵��﷨���󣬻�׼��һ��ʼҲû�Ҷԣ�����˳��

#include <stdio.h>

void qsort(int q[], int l, int r){
	if(l >= r) return ;
	
	int x = q[l];
	int i= l - 1, j = r + 1;
	
	while(i < j){
		do i++; while(q[i] < x);
		do j--; while(q[j] > x);
		
		if(i < j){
			int t = q[i];
			q[i] = q[j];
			q[j] = t;
		}
	}
	
	qsort(q, l, j);
	qsort(q, j+1, r);
}

void prt_array(int q[], int size){
	for(int i=0; i<size; i++){
		printf("%d ", q[i]);
	}
	
	printf("\n");
}

int main(){
	int array[] = {1, 1, 4, 5, 1, 4, 19, 19, 810};
	int size = sizeof(array) / sizeof(array[0]);
	
	qsort(array, 0, size-1);
	
	prt_array(array, size);
	
	return 0;
}
