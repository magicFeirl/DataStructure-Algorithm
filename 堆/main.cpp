// 《算法4》中堆的 C 语言实现
#include <stdio.h>

// 数组大小（堆大小）
const int N = 1e5;
// curr_idx 用来保存当前元素下标，从 1 开始计数
int heap[N], curr_idx;

// 比较函数
typedef int (*CMP_FUNC)(int a, int b);

// 将大于号改成小于号即可实现小根堆
int cmp(int a, int b){
	return a > b;
}

// 交换两个整型
void exch(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

// 堆的上浮操作
// 新加入的元素默认在堆底，通过跟根元素比较大小来实现上浮
void swim(int idx, CMP_FUNC cmp_func){
	while(idx > 1 && cmp_func(heap[idx], heap[idx>>1])){
		exch(&heap[idx], &heap[idx>>1]);
		idx >>= 1;
	}
}

// 下沉操作
// 先将堆顶元素（最大/小元素）和堆中最后一个元素交换（最后一个元素绝对是第一/第二小的值）
// 然后通过值的比较交换元素实现下城、沉
void sink(int idx, CMP_FUNC cmp_func){
	while((idx << 1) <= curr_idx){ // 如果还有下一层
		int j = idx << 1;
		if(j < curr_idx && cmp_func(heap[j+1], heap[j])){ // j 始终为下一层中最大/最小的元素
			j++;
		}
		
		if(!cmp_func(heap[j], heap[idx])){ // 如果当前元素已经比根大/小了，表明堆已经有序，结束
			return ;
		}
		
		// 交换
		exch(&heap[j], &heap[idx]);
		idx = j;
	}
}

// 插入
// 在堆底插入元素，然后使该元素上浮
void insert(int v){
	heap[++curr_idx] = v;
	swim(curr_idx, cmp);
}

// 取堆顶元素
int pop(){
	int v = heap[1];
	exch(&heap[1], &heap[curr_idx--]); // 交换堆顶和堆底的元素
	heap[curr_idx + 1] = 0;
	sink(1, cmp); // 下沉
	
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
