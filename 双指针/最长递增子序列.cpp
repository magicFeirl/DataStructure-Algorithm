#include <iostream>

using namespace std;

/*
    双指针类的题目一般都可以先写出一个朴素的算法
    再根据实际情况进行优化
    
    模板:
    
    for(int i=0; i<size; i++){
		int j = i;
		// check 为检查区间值是否符合要求的函数
		while(j < i && check(i, j)) j++;
		
		// 根据题目的具体逻辑
		// ...
	}
*/

int main(){
	int arr[] = {1, 0, 1, 2, 3, 4, 0, 0, 0, 0, 0, 1};
	int size = sizeof(arr) / sizeof(arr[0]);
	int i, j, res = 0;

	// 朴素算法O(N^2)
	
	// 双指针（？）优化：每次将i更新为j，避免重复
	// 简单来说就是递增序列的子序列也必然是递增序列，那么可以直接跳到本次的序列尾进行计算
	
	// 不知道对不对ORZ
	for(i=0; i<size; i++){
		j = i;
		
		while(j + 1 < size && arr[j] <= arr[j+1]) j++;
		
		res = max(res, j - i + 1);
		
		i = j;
	}
	
	printf("%d", res);
	
	return 0;
}
