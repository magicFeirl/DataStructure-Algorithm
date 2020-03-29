#include <iostream>

using namespace std;

/*
    快排步骤：
    1. 选定一个基准值
    2. 所有比基准值大的，到基准值右边，所有比基准值小的，到左边
    3. 递归l 到 j； j+1 到 r；
*/

void quick_sort(int q[], int l, int r){
	// 递归出口： 当l >= r 时（左右指针对撞），表示排序完毕，退出循环
	if(l >= r) return ;
	
	// 这里l-1和r+1可以避免在最外层循环结束后再次交换数组值
	int x = q[l], i = l - 1, j = r + 1;
	
	while(i < j){
		// 这里扫描顺序是无所谓的
		do j--; while(i < j && q[j] > x); // 从尾部开始，找到一个小于等于x的值
		do i++; while(i < j && q[i] < x); // 从头部开始，找到一个大于等于x的值
		
		// 如果找到了，交换两个值
		if(i < j) swap(q[i], q[j]);
	}
	
	// 结束后所有小于等于x的数都在x的左边，所有大于等于x的数都在x的右边，然后递归排序左右
	
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
