// ���㷨4���жѵ� C ����ʵ��
#include <stdio.h>

// �����С���Ѵ�С��
const int N = 1e5;
// curr_idx �������浱ǰԪ���±꣬�� 1 ��ʼ����
int heap[N], curr_idx;

// �ȽϺ���
typedef int (*CMP_FUNC)(int a, int b);

// �����ںŸĳ�С�ںż���ʵ��С����
int cmp(int a, int b){
	return a > b;
}

// ������������
void exch(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

// �ѵ��ϸ�����
// �¼����Ԫ��Ĭ���ڶѵף�ͨ������Ԫ�رȽϴ�С��ʵ���ϸ�
void swim(int idx, CMP_FUNC cmp_func){
	while(idx > 1 && cmp_func(heap[idx], heap[idx>>1])){
		exch(&heap[idx], &heap[idx>>1]);
		idx >>= 1;
	}
}

// �³�����
// �Ƚ��Ѷ�Ԫ�أ����/СԪ�أ��Ͷ������һ��Ԫ�ؽ��������һ��Ԫ�ؾ����ǵ�һ/�ڶ�С��ֵ��
// Ȼ��ͨ��ֵ�ıȽϽ���Ԫ��ʵ���³ǡ���
void sink(int idx, CMP_FUNC cmp_func){
	while((idx << 1) <= curr_idx){ // ���������һ��
		int j = idx << 1;
		if(j < curr_idx && cmp_func(heap[j+1], heap[j])){ // j ʼ��Ϊ��һ�������/��С��Ԫ��
			j++;
		}
		
		if(!cmp_func(heap[j], heap[idx])){ // �����ǰԪ���Ѿ��ȸ���/С�ˣ��������Ѿ����򣬽���
			return ;
		}
		
		// ����
		exch(&heap[j], &heap[idx]);
		idx = j;
	}
}

// ����
// �ڶѵײ���Ԫ�أ�Ȼ��ʹ��Ԫ���ϸ�
void insert(int v){
	heap[++curr_idx] = v;
	swim(curr_idx, cmp);
}

// ȡ�Ѷ�Ԫ��
int pop(){
	int v = heap[1];
	exch(&heap[1], &heap[curr_idx--]); // �����Ѷ��Ͷѵ׵�Ԫ��
	heap[curr_idx + 1] = 0;
	sink(1, cmp); // �³�
	
	return v;
}

int main(){
	insert(0);
	insert(2);
	insert(1);
	insert(4);
	
	printf("%d\n", pop()); // 4
	printf("%d\n", pop()); // 2
	
	return 0;
}
