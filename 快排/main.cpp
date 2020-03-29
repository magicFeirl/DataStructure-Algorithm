#include <iostream>

using namespace std;

/*
    ���Ų��裺
    1. ѡ��һ����׼ֵ
    2. ���бȻ�׼ֵ��ģ�����׼ֵ�ұߣ����бȻ�׼ֵС�ģ������
    3. �ݹ�l �� j�� j+1 �� r��
*/

void quick_sort(int q[], int l, int r){
	// �ݹ���ڣ� ��l >= r ʱ������ָ���ײ������ʾ������ϣ��˳�ѭ��
	if(l >= r) return ;
	
	// ����l-1��r+1���Ա����������ѭ���������ٴν�������ֵ
	int x = q[l], i = l - 1, j = r + 1;
	
	while(i < j){
		// ����ɨ��˳��������ν��
		do j--; while(i < j && q[j] > x); // ��β����ʼ���ҵ�һ��С�ڵ���x��ֵ
		do i++; while(i < j && q[i] < x); // ��ͷ����ʼ���ҵ�һ�����ڵ���x��ֵ
		
		// ����ҵ��ˣ���������ֵ
		if(i < j) swap(q[i], q[j]);
	}
	
	// ����������С�ڵ���x��������x����ߣ����д��ڵ���x��������x���ұߣ�Ȼ��ݹ���������
	
	quick_sort(q, l, j);
	quick_sort(q, j+1, r);
}

void prt_array(int q[], int len){
	for(int i=0; i<len; i++){
		printf("%d ", q[i]);
	}
	printf("\n");
}

int main(){
	int q[] = {1, 2, 4, 0, 9, 10, -10};
	int len = sizeof(q)/sizeof(int);
	
	quick_sort(q, 0, len-1);
	prt_array(q, len);
	
	return 0;
}
