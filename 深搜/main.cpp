// DFS
// 光打版子没意思，这里做个题
// 给一个数组 A，求 A 中元素的和能组成 target 的总数，A中每个元素可以重复使用
// 例子 A=[1, 2, 3] target = 7
// 输出 44
// 非常简单的一道题，水了（划掉）
#include <cstdio>
#include <vector>

using namespace std;

long long count;

const int N = 1e3;
int res[N], idx = 0;

// A数组 数组长度 目标值 当前总和
void dfs(int *A, int length, int target, int sum){
	if(sum > target){
		return ;
	}else if(sum == target){
		count++;
		
		for(int i=0; i<idx; i++){
			printf("%d ", res[i]);
		}

		printf("\n");
	}else{
		// 枚举可能
		for(int i=0; i<length; i++){
			// 加入一个可能解
			res[idx++] = A[i];
			// 可以看到这里只有sum的值在变
			dfs(A, length, target, sum + A[i]);
			// 结束尝试后删除最后一个解
			idx--;
		}
	}
}

int main(){
	int A[] = {1, 2, 3},
	length = sizeof(A) / sizeof(A[0]), target = 7;
	
	printf("%d\n", length);
	dfs(A, length, target, 0);
	
	printf("count: %lld\n", count);
	
	return 0;
}
